#ifndef DRAWER_H
#define DRAWER_H

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
class Vector2f;

class Drawer
{
private:
	int ppuX = 1;
	int ppuY = 1;

public:
	static Drawer* Create(SDL_Window* aWindow, SDL_Renderer* aRenderer);
	~Drawer(void);

	void SetPPU(const int X, const int Y);
	void Draw(const char* anImage, const Vector2f& pos, bool flipX = false, bool flipY = false, float angle = 0.0f, float r = 255, float g = 255, float b = 255);
	void DrawText(const char* aText, const char* aFontFile, int aX, int aY);

private:
	Drawer(SDL_Window* aWindow, SDL_Renderer* aRenderer);
	bool Init();
	
	SDL_Window* myWindow;
	SDL_Renderer* myRenderer;
	SDL_Surface* world;
};

#endif