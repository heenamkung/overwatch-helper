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

//checks if pixel is bright red (enemy health left)
inline bool pureRed(int i, RGBQUAD* Data) {
	if (
		(244 < (int)Data[i].rgbRed) && ((int)Data[i].rgbRed < 255) &&
		(0 < (int)Data[i].rgbGreen) && ((int)Data[i].rgbGreen < 4) &&
		(15 < (int)Data[i].rgbBlue) && ((int)Data[i].rgbBlue < 25)
		)
	{
		return true;
	}
	else return false;
}


inline bool greyRed(int i, RGBQUAD* Data) {
	if ((int)Data[i].rgbRed >= (int)Data[i].rgbBlue && (int)Data[i].rgbRed >= (int)Data[i].rgbGreen) {
		return true;
	}
	else
		return false;
} 

inline bool check(int i, RGBQUAD* Data) {
	if (!pureRed(i+7,Data) && pureRed(i+10, Data) && !pureRed(i + 105, Data) && (pureRed(i + 100, Data) || greyRed(i+100, Data)))
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

	for (int i = 0; i < bmSize-130; ++i) {
		//temp = check(i + 1, Data) && check(i + 2, Data) && check(i + 2, Data) &&
		//	check(i + 1920, Data) && check(i + 1921, Data) && check(i + 1922, Data);
		
		if (check(i, Data) )
		{	
		//	cout << "pixel found"<<endl;
				SetCursorPos(i%screenWidth+50, (screenHeight - i / screenWidth)+60);
			//	mouse_event(MOUSEEVENTF_MOVE, i%screenWidth - 700 , (screenHeight - i / screenWidth) - 400, 0, 0);
				return true;
			
		}
	}
	

}