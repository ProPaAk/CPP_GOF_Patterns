#pragma once

#include <vector>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"


class CommandInterface{
public:
    virtual void Execute() = 0;
    virtual ~CommandInterface() {}
};

class DropBombCommand : public CommandInterface{
private:
    uint16_t& bombsNumber;
    std::vector<DynamicObject*>& vecDynamicObj;
    int16_t& score;
    const Plane* pPlane;

public:
    DropBombCommand(uint16_t& bombsNumber,
    std::vector<DynamicObject*>& vecDynamicObj,
    int16_t& score, const Plane* pPlane)
    :
    bombsNumber(bombsNumber),
    vecDynamicObj(vecDynamicObj),
    score(score),
    pPlane(pPlane)
    {}

    void Execute() override;
    ~DropBombCommand() {}
};

class DropDecoratedBombCommand : public CommandInterface{
private:
    uint16_t& bombsNumber;
    std::vector<DynamicObject*>& vecDynamicObj;
    int16_t& score;
    const Plane* pPlane;
    const int speed;

public:
    DropDecoratedBombCommand(uint16_t& bombsNumber,
    std::vector<DynamicObject*>& vecDynamicObj,
    int16_t& score, const Plane* pPlane, const int speed)
    :
    bombsNumber(bombsNumber),
    vecDynamicObj(vecDynamicObj),
    score(score),
    pPlane(pPlane),
    speed(speed)
    {}

    void Execute() override;
    ~DropDecoratedBombCommand() {}
};

class DeleteDynamicObjCommand : public CommandInterface{
private:
    std::vector<DynamicObject*>& vecDynamicObj;
    DynamicObject* pObj;
public:
    DeleteDynamicObjCommand(std::vector<DynamicObject*>& vecDynamicObj,
    DynamicObject* pObj)
    :
    vecDynamicObj(vecDynamicObj),
    pObj(pObj)
    {}
    void Execute() override;
    ~DeleteDynamicObjCommand() {}
};

class DeleteStaticObjCommand : public CommandInterface{
private:
    std::vector<GameObject*>& vecStaticObj;
    GameObject* pObj;
public:
    DeleteStaticObjCommand(std::vector<GameObject*>& vecStaticObj,
    GameObject* pObj)
    :
    vecStaticObj(vecStaticObj),
    pObj(pObj)
    {}
    void Execute() override;
    ~DeleteStaticObjCommand() {}
};


//=========================================================================

class SBomber{
    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;
    bool exitFlag;
    uint64_t startTime;
    uint64_t finishTime;
    uint16_t deltaTime;
    uint64_t passedTime;
    uint16_t fps;
    uint16_t bombsNumber;
    int16_t score;

public:
    SBomber();
    ~SBomber();
    
    void MoveObjects();
    void CheckObjects();
    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    void CheckDestoyableObjects(Bomb* pBomb);
    void ProcessKBHit();
    void DrawFrame();
    void TimeStart();
    void TimeFinish();
    bool GetExitFlag() const;

private:
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    Ground * FindGround() const;
    std::vector<Bomb*> FindAllBombs();
    Plane * FindPlane() const;
    LevelGUI * FindLevelGUI() const;
    void CommandExecutor(CommandInterface* command); 
    
    class BombIterator {
        std::vector<DynamicObject*>& vecDynamicObj;
        size_t current;

    public:
        BombIterator(std::vector<DynamicObject*>& vecDynamicObj,
        size_t index);
        BombIterator& operator++ ();
        BombIterator operator++ (int);
		Bomb* operator* () const;
		bool operator== (const BombIterator& other) const;
		bool operator!= (const BombIterator& other) const;

    private:
        size_t findNextBomb(size_t start) const;
        size_t findNextBomb() const;
        Bomb* getPtr() const;
    };
    BombIterator begin();
    BombIterator end();
};