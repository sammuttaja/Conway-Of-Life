#include <iostream>
#include "Window.h"

int main(int argc, char *argv[]) {
	Window* window = new Window();
	window->Run();
	free(window);
	return 1;
}