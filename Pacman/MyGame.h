#ifndef MYGAME_H
#define MYGAME_H

#include "PathmapTile.h"
#include "Vector2f.h"
#include <list>

class GameObject;
class Drawer;

class MyGame
{
private:
	Drawer* drawer;
	std::list<GameObject*> gameObjects;
	PathmapTile* map;
	Vector2f input;

	void UpdateInput();

public:
	MyGame(Drawer* drawer);
	~MyGame();

	Vector2f TakeInput() const;
	void Draw() const;
	void Start();
	void Update(const float dt);
};
#endif