#include "Drawer.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Vector2f.h"

Drawer* Drawer::Create(SDL_Window* aWindow, SDL_Renderer* aRenderer)
{
	Drawer* drawer = new Drawer(aWindow, aRenderer);

	if (!drawer->Init())
	{
		delete drawer;
		drawer = NULL;
	}

	return drawer;
}

Drawer::Drawer(SDL_Window* aWindow, SDL_Renderer* aRenderer)
: myWindow(aWindow)
, myRenderer(aRenderer)
{
}

Drawer::~Drawer(void)
{
}

bool Drawer::Init()
{
	if (myWindow == nullptr)
		return false;

	return true;
}

void Drawer::Draw(const char* anImage, const Vector2f& pos)
{
	int screenWidth;
	int screenHeigth;
	SDL_GetWindowSize(myWindow, &screenWidth, &screenHeigth);

	SDL_Surface* surface = IMG_Load(anImage);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(myRenderer, surface);

	SDL_Rect sizeRect;
	sizeRect.x = 0;
	sizeRect.y = 0;
	sizeRect.w = surface->w;
	sizeRect.h = surface->h;

	SDL_Rect posRect;
	posRect.x = (int)(pos.X * + ppuX + (screenWidth - sizeRect.w) / 2);
	posRect.y = (int)(pos.Y * - ppuY + (screenHeigth - sizeRect.h) / 2);
	posRect.w = sizeRect.w;
	posRect.h = sizeRect.h;

	SDL_RenderCopyEx(myRenderer, texture, &sizeRect, &posRect, 0, nullptr, SDL_FLIP_NONE);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void Drawer::DrawText(const char* aText, const char* aFontFile, int aX, int aY)
{
	TTF_Font* font=TTF_OpenFont(aFontFile, 24);

	SDL_Color fg={255,0,0,255};
	SDL_Surface* surface = TTF_RenderText_Solid(font, aText, fg);

	SDL_Texture* optimizedSurface = SDL_CreateTextureFromSurface(myRenderer, surface);

    SDL_Rect sizeRect;
    sizeRect.x = 0 ;
    sizeRect.y = 0 ;
    sizeRect.w = surface->w ;
    sizeRect.h = surface->h ;

    SDL_Rect posRect ;
    posRect.x = aX;
    posRect.y = aY;
	posRect.w = sizeRect.w;
	posRect.h = sizeRect.h;

	SDL_RenderCopy(myRenderer, optimizedSurface, &sizeRect, &posRect);
	SDL_DestroyTexture(optimizedSurface);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}

void Drawer::SetPPU(const int sizeX, const int sizeY)
{
	if (sizeX < 1 || sizeY < 1)
	{
		return;
	}
	this->ppuX = sizeX;
	this->ppuY = sizeY;
}
