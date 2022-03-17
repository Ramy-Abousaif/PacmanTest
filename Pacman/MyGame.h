#ifndef MYGAME_H
#define MYGAME_H

#include "PathmapTile.h"
#include "Vector2f.h"
#include <vector>
#include <string>

class GameObject;
class Drawer;
class TextUI;
class PointsUI;

class MyGame
{
private:
	Drawer* drawer;
	PathmapTile* map;
	std::vector<GameObject*> gameObjects;
	Vector2f input;
	std::string fps = "0";
	TextUI* fpsValue;
	std::vector<GameObject*> gameObjectsToDestroy;

	void DestroyQueuedGameObjects();
	bool UpdateInput();

public:
	MyGame(Drawer* drawer);
	~MyGame();

	static MyGame* Instance;

	PathmapTile* GetMap() const;
	Vector2f TakeInput() const;
	void Draw() const;
	GameObject* CreateGameObjectInstance(const Vector2f& pos = Vector2f(0.0f, 0.0f));
	void DestroyGameObject(GameObject* go);
	void Start();
	bool Update(const float dt);
	Drawer* GetDrawer() const;
};
#endif