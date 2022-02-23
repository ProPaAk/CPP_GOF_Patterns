#pragma once

#include "HouseBuilder.h"

class HouseBuilderA : public HouseBuilder{
public:
    HouseBuilderA();
    ~HouseBuilderA(){};

    void createHouse() override;
    void buildHouse(const uint16_t& widthN,
        const double& nx, const double& ny) override;
};