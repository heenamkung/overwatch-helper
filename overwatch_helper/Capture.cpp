#include "Capture.h"

Capture::Capture(): windowName(NULL) {
}

Capture::Capture(char* _windowName) : windowName(_windowName) {
}

void Capture::switchWindow() {
	HWND hwnd = FindWindowA(0, windowName);
	SwitchToThisWindow(hwnd, true);
}

bool Capture::captureScreen(Screenshot& screenshot) {

	//https://stackoverflow.com/questions/26233848/c-read-pixels-with-getdibits


	HDC hdc = GetDC(0); // 0 = entire screen
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hbm = CreateCompatibleBitmap(hdc, screenshot.getWidth(), screenshot.getHeight());
	HGDIOBJ old = SelectObject(hdcMem, hbm);

	if (!BitBlt(hdcMem, 0, 0, screenshot.getWidth(), screenshot.getHeight(), hdc, 0, 0, SRCCOPY | CAPTUREBLT))
	{
		cout << "ERROR: bit-block transfer failed!" << endl;
		return false;
	}
	

	SelectObject(hdcMem, old);
	DeleteDC(hdcMem);

	BITMAPINFO bmInfo = { 0 };
	bmInfo.bmiHeader.biSize = sizeof(bmInfo.bmiHeader);
	if (0 == GetDIBits(hdc, hbm, 0, 0, NULL, &bmInfo, DIB_RGB_COLORS)) {
		cout << "error" << endl;
	}
	bmInfo.bmiHeader.biCompression = BI_RGB;
	int bmSize = bmInfo.bmiHeader.biWidth * bmInfo.bmiHeader.biHeight;
	screenshot.Data = new RGBQUAD[bmSize];
	if (0 == GetDIBits(hdc, hbm, 0, bmInfo.bmiHeader.biHeight, (LPVOID)screenshot.Data, &bmInfo, DIB_RGB_COLORS)) {
		cout << "error getting bitmap pixel data" << endl;
	}
	//image stored from bottom left of screen to top right
	
	/*
	//storing image
	BITMAP bmpScreen;
	GetObject(hbm, sizeof(BITMAP), &bmpScreen);

	BITMAPFILEHEADER   bmfHeader;
	BITMAPINFOHEADER   bi;

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bmpScreen.bmWidth;
	bi.biHeight = bmpScreen.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;
	DWORD dwBmpSize = ((bmpScreen.bmWidth * bi.biBitCount + 31) / 32) * 4 * bmpScreen.bmHeight;

	HANDLE hDIB = GlobalAlloc(GHND, dwBmpSize);
	


	HANDLE hFile = CreateFile(L"captureqwsx.bmp",
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	// Add the size of the headers to the size of the bitmap to get the total file size
	DWORD dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	//Offset to where the actual bitmap bits start.
	bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);

	//Size of the file
	bmfHeader.bfSize = dwSizeofDIB;

	//bfType must always be BM for Bitmaps
	bmfHeader.bfType = 0x4D42; //BM   

	DWORD dwBytesWritten = 0;
	WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPVOID)screenshot.Data, dwBmpSize, &dwBytesWritten, NULL);
	GlobalUnlock(hDIB);
	GlobalFree(hDIB);

	//Close the handle for the file that was created
	CloseHandle(hFile);

	*/

	screenshot.detectPixel(bmSize);

	DeleteObject(hbm);
	ReleaseDC(NULL, hdc);
	delete[] screenshot.Data;

	// Sleep(10);
}