#include <windows.h>

#include <iostream>

#include "color.h"
#include "scence.h"
#include "symbol.h"

int main() {
	SetConsoleOutputCP(CP_UTF8);
	CScene scene;
	scene.generate();
	scene.eraseRandomGrids(20);
	scene.play();
	return 0;
}