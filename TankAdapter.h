#pragma once

#include "DestroyableGroundObject.h"
#include "TankAdaptee.h"

class TankAdapter : public DestroyableGroundObject{
    TankAdaptee* tank;

public:
    TankAdapter();
    ~TankAdapter(){};

    void SetPos(double nx, double ny) override;
    double GetY() const override;
    double GetX() const override;
    void SetWidth(uint16_t widthN) override;
    uint16_t GetWidth() const override;
    void Draw() const override;
    bool __fastcall isInside(double x1, double x2) const override;
    inline uint16_t GetScore() const override;
};