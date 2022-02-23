#pragma once

#include <stdint.h>
#include <vector>
#include <string>

#include "DestroyableGroundObject.h"
//#include "HouseBuilderA.h"

class House : public DestroyableGroundObject{
public:
	House(){};
	~House(){};
	bool __fastcall isInside(double x1, double x2) const override;
	inline uint16_t GetScore() const override { return score; }
	void Draw() const override;

private:
	std::vector<std::string> look{
		{"  ########  "},
		{"##        ##"},
		{"############"},
		{"#          #"},
		{"#          #"},
		{"#          #"},
		{"############"},
		};
	const uint16_t score = 40;
	friend class HouseBuilderA;
};

