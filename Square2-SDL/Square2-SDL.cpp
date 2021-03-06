// Square2-SDL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "SDL.h"
#include <stdio.h>


int posX = 100;
int posY = 200;
int sizeX = 300;
int sizeY = 400;

SDL_Window* window;
SDL_Renderer* renderer;

bool InitEverything();
bool InitSDL();
bool CreateWindow();
bool CreateRenderer();
void SetupRenderer();

void Render();
void RunGame();

SDL_Rect playerPos;

int main(int argc, char* args[])
{
	if (!InitEverything())
		return -1;

	playerPos.x = 0;
	playerPos.y = 0;
	playerPos.w = 20;
	playerPos.h = 20;

	RunGame();
}
void Render()
{
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	SDL_RenderFillRect(renderer, &playerPos);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	SDL_RenderPresent(renderer);
}
bool InitEverything()
{
	if (!InitSDL())
		return false;

	if (!CreateWindow())
		return false;

	if (!CreateRenderer())
		return false;

	SetupRenderer();

	return true;
}
bool InitSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}
bool CreateWindow()
{
	window = SDL_CreateWindow("Square2", posX, posY, sizeX, sizeY, 0);

	if (window == nullptr)
	{
		std::cout << "Failed to create window : " << SDL_GetError();
		return false;
	}

	return true;
}
bool CreateRenderer()
{
	renderer = SDL_CreateRenderer(window, -1, 0);

	if (renderer == nullptr)
	{
		std::cout << "Failed to create renderer : " << SDL_GetError();
		return false;
	}

	return true;
}
void SetupRenderer()
{
	SDL_RenderSetLogicalSize(renderer, sizeX, sizeY);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
}
void RunGame()
{
	bool loop = true;

	while (loop)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				loop = false;
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_RIGHT:
					++playerPos.x;
					break;
				case SDLK_LEFT:
					--playerPos.x;
					break;
				case SDLK_DOWN:
					++playerPos.y;
					break;
				case SDLK_UP:
					--playerPos.y;
					break;
				default:
					break;
				}
			}
		}

		Render();
	}
}