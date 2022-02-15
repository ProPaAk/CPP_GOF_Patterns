
#include <conio.h>
#include <windows.h>

#include "MyTools.h"
#include "SBomber.h"
#include "Bomb.h"
#include "Ground.h"
#include "TankAdapter.h"
#include "Tank.h"
#include "House.h"

using namespace std;
using namespace MyTools;

void DropBombCommand::Execute(){
    if (bombsNumber > 0){
        FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

        double x = pPlane->GetX() + 4;
        double y = pPlane->GetY() + 2;

        Bomb* pBomb = new Bomb;
        pBomb->SetDirection(0.3, 1);
        pBomb->SetSpeed(2);        
        pBomb->SetPos(x, y);
        pBomb->SetWidth(SMALL_CRATER_SIZE);

        vecDynamicObj.push_back(pBomb);
        bombsNumber--;
        score -= Bomb::BombCost;
    }
}

void DropDecoratedBombCommand::Execute(){
    if (bombsNumber > 0){
        FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

        double x = pPlane->GetX() + 4;
        double y = pPlane->GetY() + 2;

        Bomb* pBomb = new Bomb;
        pBomb->SetDirection(0.3, 1);
        pBomb->SetPos(x, y);
        pBomb->SetWidth(SMALL_CRATER_SIZE);
        BombDecorator* bd = new BombDecorator(
            pBomb, speed);

        vecDynamicObj.push_back(bd);
        bombsNumber--;
        score -= Bomb::BombCost;
    }
}

void DeleteDynamicObjCommand::Execute(){
    auto it = vecDynamicObj.begin();
    for (; it != vecDynamicObj.end(); it++){
        if (*it == pObj){
            vecDynamicObj.erase(it);
            break;
        }
    }
}

void DeleteStaticObjCommand::Execute(){
    auto it = vecStaticObj.begin();
    for (; it != vecStaticObj.end(); it++){
        if (*it == pObj){
            vecStaticObj.erase(it);
            break;
        }
    }
}

//=========================================================================

SBomber::SBomber()
    : exitFlag(false),
    startTime(0),
    finishTime(0),
    deltaTime(0),
    passedTime(0),
    fps(0),
    bombsNumber(10),
    score(0)
{
    FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    Plane* p = new Plane;
    p->SetDirection(1, 0.1);
    p->SetSpeed(4);
    p->SetPos(5, 10);
    vecDynamicObj.push_back(p);

    LevelGUI* pGUI = new LevelGUI;
    pGUI->SetParam(passedTime, fps, bombsNumber, score);
    const uint16_t maxX = GetMaxX();
    const uint16_t maxY = GetMaxY(); 
    const uint16_t offset = 3;
    const uint16_t width = maxX - 7;
    pGUI->SetPos(offset, offset);
    pGUI->SetWidth(width);
    pGUI->SetHeight(maxY - 4);
    pGUI->SetFinishX(offset + width - 4);
    vecStaticObj.push_back(pGUI);

    Ground* pGr = new Ground;
    const uint16_t groundY = maxY - 5;
    pGr->SetPos(offset + 1, groundY);
    pGr->SetWidth(width - 2);
    vecStaticObj.push_back(pGr);

    Tank* pTank = new Tank();
    pTank->SetWidth(13);
    pTank->SetPos(30, groundY - 1);
    vecStaticObj.push_back(pTank);

    pTank = new Tank;
    pTank->SetWidth(13);
    pTank->SetPos(50, groundY - 1);
    vecStaticObj.push_back(pTank);

    TankAdapter* pTankAdapter = new TankAdapter();
    pTankAdapter->SetWidth(13);
    pTankAdapter->SetPos(10, groundY - 1);
    vecStaticObj.push_back(pTankAdapter);

    House * pHouse = new House;
    pHouse->SetWidth(13);
    pHouse->SetPos(80, groundY - 1);
    vecStaticObj.push_back(pHouse);
}

SBomber::~SBomber(){
    for (size_t i = 0; i < vecDynamicObj.size(); i++){
        if (vecDynamicObj[i] != nullptr){
            delete vecDynamicObj[i];
        }
    }

    for (size_t i = 0; i < vecStaticObj.size(); i++){
        if (vecStaticObj[i] != nullptr){
            delete vecStaticObj[i];
        }
    }
}

void SBomber::MoveObjects(){
    FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < vecDynamicObj.size(); i++){
        if (vecDynamicObj[i] != nullptr){
            vecDynamicObj[i]->Move(deltaTime);
        }
    }
};

void SBomber::CheckObjects(){
    FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    CheckPlaneAndLevelGUI();
    CheckBombsAndGround();
};

void SBomber::CheckPlaneAndLevelGUI(){
    if (FindPlane()->GetX() > FindLevelGUI()->GetFinishX()){
        exitFlag = true;
    }
}

void SBomber::CheckBombsAndGround(){
    std::vector<Bomb*> vecBombs = FindAllBombs();
    Ground* pGround = FindGround();
    const double y = pGround->GetY();
    for (size_t i = 0; i < vecBombs.size(); i++)
        if (vecBombs[i]->GetY() >= y) {
            pGround->AddCrater(vecBombs[i]->GetX());
            CheckDestoyableObjects(vecBombs[i]);
            
            CommandExecutor(
                new DeleteDynamicObjCommand(vecDynamicObj,vecBombs[i]));
        }
}

void SBomber::CheckDestoyableObjects(Bomb * pBomb){
    vector<DestroyableGroundObject*> vecDestoyableObjects = FindDestoyableGroundObjects();
    const double size = pBomb->GetWidth();
    const double size_2 = size / 2;
    for (size_t i = 0; i < vecDestoyableObjects.size(); i++){
        const double x1 = pBomb->GetX() - size_2;
        const double x2 = x1 + size;
        if (vecDestoyableObjects[i]->isInside(x1, x2)){
            score += vecDestoyableObjects[i]->GetScore();            
            CommandExecutor(new DeleteStaticObjCommand(                
                vecStaticObj,vecDestoyableObjects[i]));
        }
    }
}

void SBomber::ProcessKBHit(){
    int c = _getch();
    if (c == 224){
        c = _getch();
    }

    FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked. key = ", c);

    switch (c) {
    case 27:
        exitFlag = true;
        break;

    case 72: 
        FindPlane()->ChangePlaneY(-0.25);
        break;

    case 80:
        FindPlane()->ChangePlaneY(0.25);
        break;

    case 'b':
    case 'B':
        CommandExecutor(
            new DropBombCommand(bombsNumber,vecDynamicObj,score,FindPlane()));
        break;
    
    case 'c':
    case 'C':
        CommandExecutor(
            new DropDecoratedBombCommand(
                bombsNumber,vecDynamicObj,score,FindPlane(),7));
        break;

    default:
        break;
    }
}

void SBomber::DrawFrame(){
    FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < vecDynamicObj.size(); i++){
        if (vecDynamicObj[i] != nullptr){
            vecDynamicObj[i]->Draw();
        }
    }

    for (size_t i = 0; i < vecStaticObj.size(); i++){
        if (vecStaticObj[i] != nullptr){
            vecStaticObj[i]->Draw();
        }
    }

    GotoXY(0, 0);
    fps++;

    FindLevelGUI()->SetParam(passedTime, fps, bombsNumber, score);
}

void SBomber::TimeStart(){
    FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");
    startTime = GetTickCount64();
}

void SBomber::TimeFinish(){
    finishTime = GetTickCount64();
    deltaTime = uint16_t(finishTime - startTime);
    passedTime += deltaTime;

    FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " deltaTime = ", (int)deltaTime);
}

bool SBomber::GetExitFlag() const { 
    return exitFlag; 
}

vector<DestroyableGroundObject*> SBomber::FindDestoyableGroundObjects() const{
    vector<DestroyableGroundObject*> vec;
    Tank* pTank;
    TankAdapter* pTankAdapter;
    House* pHouse;
    for (size_t i = 0; i < vecStaticObj.size(); i++){
        pTank = dynamic_cast<Tank*>(vecStaticObj[i]);
        if (pTank != nullptr){
            vec.push_back(pTank);
            continue;
        }

    for (size_t i = 0; i < vecStaticObj.size(); i++){
        pTankAdapter = dynamic_cast<TankAdapter*>(vecStaticObj[i]);
        if (pTankAdapter != nullptr){
            vec.push_back(pTankAdapter);
            continue;
        }
    }

        pHouse = dynamic_cast<House*>(vecStaticObj[i]);
        if (pHouse != nullptr){
            vec.push_back(pHouse);
            continue;
        }
    }
    return vec;
}

Ground* SBomber::FindGround() const{
    Ground* pGround;

    for (size_t i = 0; i < vecStaticObj.size(); i++){
        pGround = dynamic_cast<Ground *>(vecStaticObj[i]);
        if (pGround != nullptr){
            return pGround;
        }
    }
    return nullptr;
}

vector<Bomb*> SBomber::FindAllBombs(){
    vector<Bomb*> vecBombs;
    
    for (Bomb* pBomb: *this)
        vecBombs.push_back(pBomb);
    
    return vecBombs;
}

Plane* SBomber::FindPlane() const{
    for (size_t i = 0; i < vecDynamicObj.size(); i++){
        Plane* p = dynamic_cast<Plane*>(vecDynamicObj[i]);
        if (p != nullptr){
            return p;
        }
    }
    return nullptr;
}

LevelGUI* SBomber::FindLevelGUI() const{
    for (size_t i = 0; i < vecStaticObj.size(); i++){
        LevelGUI* p = dynamic_cast<LevelGUI*>(vecStaticObj[i]);
        if (p != nullptr){
            return p;
        }
    }
    return nullptr;
}

void SBomber::CommandExecutor(CommandInterface* command){
    if(command){
        command->Execute();
        delete command;
    }
}

SBomber::BombIterator::BombIterator(
    std::vector<DynamicObject*>& vecDynamicObj,
    size_t index)
    :
    vecDynamicObj(vecDynamicObj),
    current(findNextBomb(index))
    {}

SBomber::BombIterator& SBomber::BombIterator::operator++ () {
	++current;
    current = findNextBomb();
    return *this;
}

SBomber::BombIterator SBomber::BombIterator::operator++ (int){
    BombIterator it = *this;
    current = findNextBomb();
    return it;

}

Bomb* SBomber::BombIterator::operator* () const {
    return getPtr();
}

bool SBomber::BombIterator::operator== (const BombIterator& other) const {
    return this->getPtr() == other.getPtr();
}

bool SBomber::BombIterator::operator!= (const BombIterator& other) const {
    return !(*this == other);
}

size_t SBomber::BombIterator::findNextBomb(size_t start) const {
    for (size_t i = start; i < vecDynamicObj.size(); ++i)
        if (dynamic_cast<Bomb*>(vecDynamicObj[i]))
            return i;
    return vecDynamicObj.size();
}

size_t SBomber::BombIterator::findNextBomb() const {
    return findNextBomb(current);
}

Bomb* SBomber::BombIterator::getPtr() const {
    if (current < vecDynamicObj.size())
        return dynamic_cast<Bomb*>(vecDynamicObj[current]);
    else
        return nullptr;
}

SBomber::BombIterator SBomber::begin(){
    return BombIterator(vecDynamicObj, 0);
}

SBomber::BombIterator SBomber::end(){
    return BombIterator(vecDynamicObj, vecDynamicObj.size());
}
