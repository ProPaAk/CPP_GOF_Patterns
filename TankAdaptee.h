#pragma once

class TankAdaptee {
protected:
	double x, y;
	uint16_t width;
	const uint16_t score = 30;

public:
	TankAdaptee() : x(0.0), y(0.0), width(0) { }
	void Paint();
	bool __fastcall isInRange(double x1, double x2) const;
	uint16_t GetScore() const;
	void SetPos(double nx, double ny);
	double GetY() const;
	double GetX() const;
	void SetWidth(uint16_t widthN);
	uint16_t GetWidth() const;
};