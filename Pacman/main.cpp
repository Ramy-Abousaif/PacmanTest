#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "assert.h"
#include "drawer.h"
#include <iostream>
#include "MyGame.h"

int main(int argc, char **argv)
{
	/* initialize SDL */
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		assert(0 && "Failed to initialize video!");
		exit(-1);
	}
	
	SDL_Window* window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_OPENGL);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(window == nullptr)
	{
		assert(0 && "Failed to create window!");
		exit(-1);
	}

	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 3)
	{
		assert(0 && "No support for JPGs and PNGs!");
		exit(-1);
	}

	if (TTF_Init() == -1)
	{
		assert(0 && "Failed to create ttf!");
		exit(-1);
	}

	Drawer* drawer = Drawer::Create(window, renderer);
	drawer->SetPPU(44, 44);

	MyGame* game = new MyGame(drawer);

	game->Start();

	SDL_Event event;
	float lastFrame = (float)SDL_GetTicks() * 0.001f;
	while (SDL_PollEvent(&event) >= 0)
	{
		float currentFrame = (float)SDL_GetTicks() * 0.001f;
		float elapsedTime = currentFrame - lastFrame;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		if (!game->Update(elapsedTime))
			break;

		game->Draw();
		
		lastFrame = currentFrame;		
		SDL_RenderPresent(renderer);
		SDL_Delay(1);
	}

	delete game;
	delete drawer;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit( );

	return 0;
}

