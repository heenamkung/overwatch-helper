#pragma once

#include <iostream>
#include <Windows.h>
#include "Screenshot.h"

using namespace std;

class Capture {
public:
	Capture();
	Capture(char*);

	void switchWindow();
	bool captureScreen(Screenshot&);





private:
	char* windowName;




};