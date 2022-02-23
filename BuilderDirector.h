#pragma once

#include "House.h"
#include "HouseBuilder.h"

class BuilderDirector{
public:
    House* createHouse(HouseBuilder& hB, const uint16_t& width,
        const double& nx, const double& ny){
        hB.createHouse();
        hB.buildHouse(width, nx, ny);
        return (hB.getHouse()); 
    }
};