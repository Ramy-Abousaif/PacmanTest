#ifndef DRAWER_H
#define DRAWER_H

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

class Drawer
{
public:
	static Drawer* Create(SDL_Window* aWindow, SDL_Renderer* aRenderer);
	~Drawer(void);

	void Draw(const char* anImage, const Vector2f& pos);
	void DrawText(const char* aText, const char* aFontFile, int aX, int aY);
	void SetPPU(const int X, const int Y);

private:
	int ppuX = 1;
	int ppuY = 1;

	Drawer(SDL_Window* aWindow, SDL_Renderer* aRenderer);
	bool Init();
	
	SDL_Window* myWindow;
	SDL_Renderer* myRenderer;
	SDL_Surface* world;
};

#endif