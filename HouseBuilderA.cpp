
#include "HouseBuilderA.h"

HouseBuilderA::HouseBuilderA(){}

void HouseBuilderA::createHouse(){
    pHouse = new House;
}

void HouseBuilderA::buildHouse(const uint16_t& widthN,
    const double& nx, const double& ny){
    pHouse->SetPos(nx, ny);
    pHouse->SetWidth(widthN);
    
    pHouse->look.clear();
    pHouse->look.push_back("#########");
    pHouse->look.push_back("#       #");
    pHouse->look.push_back("#       #");
    pHouse->look.push_back("#       #");
    pHouse->look.push_back("#       #");
    pHouse->look.push_back("#       #");
    pHouse->look.push_back("#########");
    
}

