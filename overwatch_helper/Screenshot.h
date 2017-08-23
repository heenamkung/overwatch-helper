#pragma once

#include <iostream>
#include <Windows.h>

using namespace std;

class Screenshot {
	friend class Capture;
private:
	RGBQUAD* Data;
	int screenWidth;
	int screenHeight;
	

public:
	Screenshot();
	int getWidth();
	int getHeight();
	bool detectPixel(int bmSize);


};