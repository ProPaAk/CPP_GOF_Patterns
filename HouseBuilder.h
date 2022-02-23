#pragma once

#include "House.h"

class HouseBuilder{
protected:
    House* pHouse;
public:    
    HouseBuilder(){};
    virtual ~HouseBuilder(){};
    
    virtual void createHouse() = 0;
    virtual void buildHouse(const uint16_t& widthN,
        const double& nx, const double& ny) = 0;
    virtual House* getHouse(){return pHouse;}
};