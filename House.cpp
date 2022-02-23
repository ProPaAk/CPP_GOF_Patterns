#include <iostream>

#include "House.h"
#include "MyTools.h"

bool House::isInside(double x1, double x2) const{
	const double XBeg = x + 2;
	const double XEnd = x + width - 1;
	if (x1 < XBeg && x2 > XEnd){
		return true;
	}

	if (x1 > XBeg && x1 < XEnd){
		return true;
	}

	if (x2 > XBeg && x2 < XEnd){
		return true;
	}
	return false;
}

void House::Draw() const{
	MyTools::SetColor(MyTools::CC_Yellow);
	size_t i = 0;
	for(const auto& it : look){		
		MyTools::GotoXY(x, y - 5 + i);		
		std::cout << it;
		++i;
		std::cout << std::endl;
	}
}