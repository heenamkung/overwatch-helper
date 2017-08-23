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



	screenshot.detectPixel(bmSize);

	DeleteObject(hbm);
	ReleaseDC(NULL, hdc);
	delete[] screenshot.Data;

	// Sleep(10);
}