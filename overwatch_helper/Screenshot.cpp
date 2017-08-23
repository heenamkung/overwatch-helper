#include "Screenshot.h"

inline bool operator==(RGBQUAD& a, RGBQUAD& b) {
	return a.rgbBlue == b.rgbBlue && a.rgbGreen == b.rgbGreen && a.rgbRed == b.rgbRed;
}

Screenshot::Screenshot() {
	Data=NULL;
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
}

int Screenshot::getWidth() {
	return screenWidth;
}

int Screenshot::getHeight() {
	return screenHeight;
}


inline bool check(int i, RGBQUAD* Data) {
	if (
		(244 < (int)Data[i].rgbRed) && ((int)Data[i].rgbRed < 255) &&
		(0 < (int)Data[i].rgbGreen) && ((int)Data[i].rgbGreen < 4) &&
		(15 < (int)Data[i].rgbBlue) && ((int)Data[i].rgbBlue < 25)
		)
	{
		cout << (int)Data[i].rgbRed << " " << (int)Data[i].rgbGreen << " " << (int)Data[i].rgbBlue << endl;
		return true;
	}
	else return false;
}

bool Screenshot::detectPixel(int bmSize) {
	//blue: 15 ~ 25
	//green: 0~4
	//red : 244~255

	bool temp;

	for (int i = 0; i < bmSize; ++i) {
		//temp = check(i + 1, Data) && check(i + 2, Data) && check(i + 2, Data) &&
		//	check(i + 1920, Data) && check(i + 1921, Data) && check(i + 1922, Data);

		if (check(i, Data) )
		{	
			
				SetCursorPos(i%screenWidth+50, (screenHeight - i / screenWidth)+55);
				return true;
			
		}
	}
	

}