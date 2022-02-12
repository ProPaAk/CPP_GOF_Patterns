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

public:
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
private:
    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;
    uint64_t startTime;
    uint64_t finishTime;
    uint64_t passedTime;
    uint16_t deltaTime;
    uint16_t fps;
    uint16_t bombsNumber;
    int16_t score;
    bool exitFlag;

public:
    SBomber();
    ~SBomber();
    
    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();
    void DrawFrame();
    void MoveObjects();
    void CheckObjects();
    bool GetExitFlag() const { return exitFlag; }

private:
    Ground * FindGround() const;
    LevelGUI * FindLevelGUI() const;
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    std::vector<Bomb*> FindAllBombs() const;
    Plane * FindPlane() const;

    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    void __fastcall CheckDestoyableObjects(Bomb* pBomb);
    void CommandExecutor(CommandInterface* command);    
};