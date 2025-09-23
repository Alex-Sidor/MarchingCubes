#include <iostream>

#include "Screen.h"

Screen screen(800,800);

int main()
{
	

	while(!screen.shouldClose()){
		screen.clearBuffer();
		screen.updateScreen();
	}
}
