#include <iostream>
#include <Windows.h>
#include "Capture.h"
#include "Screenshot.h"

using namespace std;

int main() {
	Sleep(2000);
	Screenshot a;
	Capture c("오버워치");
	c.switchWindow();
	while(1){
		
		c.captureScreen(a);

	}




	system("pause");
}