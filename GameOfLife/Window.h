#pragma once
#include <SDL2\SDL.h>
#include <iostream>
#include <vector>
#include <array>
#include "Tools.h"
class Window
{
private:
	const int Col = 50;
	const int Row = 100;
	SDL_Window * window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool running = true;
	int Map[50][100];
public:
	Window();
	void Run();
	~Window();

private:
	void Render();
	void CheckEvents();
	void DrawGrid();
	void CreateEnteties();
	void UpdateEnteties();
};

