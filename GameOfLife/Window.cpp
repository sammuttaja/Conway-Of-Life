#include "Window.h"

#define Length(arr) sizeof(arr)/sizeof(*arr)
#define ColLength(arr, type) sizeof(arr[0])/sizeof(type)

Window::Window()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return;
	}
	;
	if (SDL_CreateWindowAndRenderer(1000, 500, 0, &window, &renderer) < 0) {
		std::cerr << SDL_GetError() << std::endl;
		return;
	}
	CreateEnteties();
}

static inline int GridPos(int pos) {
	return pos / GridSize;
}

void Window::CreateEnteties() {
	
	int seed = rand() % 100;
	

	for (int i = 0; i < 700; i++) {
		int x = rand() % Col;
		int y = rand() % Row;
		//enteties.push_back(temp);
		if(Map[x][y] != 1)
			Map[x][y] = 1;
	}
}

void Window::UpdateEnteties() {

	for (int x = 0; x < Col; x++) {
		for (int y = 0; y < Row; y++) {

			int neighbours = 0;
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					int col = x + i;
					int row = y + j;
					if (col < Col && col >= 0 && row < Row & row >= 0 && !(i == 0 && j == 0) && Map[col][row] == 1)
						neighbours++;
				}
			}

			if (Map[x][y] == 1) {
				if (neighbours > 3 || neighbours < 3)
					Map[x][y] = 0;
			}

			if (Map[x][y] == 0) {
				if (neighbours == 3)
					Map[x][y] = 1;
			}
		}
	}

}

void Window::Run()
{
	while (running) {
		Render();
		UpdateEnteties();
		CheckEvents();
		SDL_Delay(400);
	}
}

//Debug Grid
void Window::DrawGrid() {

	for (Uint32 i = 0; i < 1000; i += GridSize) {
		SDL_RenderDrawLine(renderer, i, 0, i, 500);
	}
	for (Uint32 i = 0; i < 500; i += GridSize) {
		SDL_RenderDrawLine(renderer, 0, i, 1000, i);
	}
}

void Window::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
#if _DEBUG
	DrawGrid();
#endif
	SDL_Rect rect;

	for (int i = 0; i < Col; i++) {
		for (int j = 0; j < Row; j++) {

			if (Map[i][j] == 1) {
				rect.x = i * GridSize + 2;
				rect.y = j * GridSize + 2;
				rect.w = GridSize - 3;
				rect.h = GridSize - 3;
				SDL_RenderFillRect(renderer, &rect);
			}
		}
	}/*
	for (Uint32 i = 0; i < enteties.size(); i++) {
		rect.x = enteties[i].Position.x * GridSize+2;
		rect.y = enteties[i].Position.y * GridSize+2;
		rect.w = GridSize - 3;
		rect.h = GridSize - 3;
		SDL_RenderFillRect(renderer, &rect);
	}*/
	SDL_RenderPresent(renderer);
}



void Window::CheckEvents()
{
	SDL_Event event_;
	while (SDL_PollEvent(&event_) != 0) {

		switch (event_.type) {
			case SDL_QUIT: {
				running = false;
				return;
			}
			case SDL_MOUSEBUTTONDOWN: {
				if (event_.button.button == SDL_BUTTON_LEFT) {
					int x = (event_.button.x) / GridSize;
					int y = (event_.button.y) / GridSize;
					Map[x][y] = 1;
				}
			}
		}
	}
}

Window::~Window()
{
	if (renderer)
		SDL_DestroyRenderer(renderer);
	if(window)
		SDL_DestroyWindow(window);
}
