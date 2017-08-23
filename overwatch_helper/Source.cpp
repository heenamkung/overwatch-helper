#include <iostream>
#include <Windows.h>
#include "Capture.h"
#include "Screenshot.h"

using namespace std;

int main() {
	Screenshot a;
	Capture c;

	
	while(1){
		c.captureScreen(a);

	}




	system("pause");
}