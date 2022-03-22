#ifndef MYGAME_H
#define MYGAME_H

#include "Vector2f.h"
#include <vector>
#include "GameObject.h"
#include <string>

class GameObject;
class Drawer;

class MyGame
{
private:
	Drawer* drawer;
	std::vector<GameObject*> gameObjects;
	Vector2f input;
	bool toggleFPS = false;
	std::vector<GameObject*> gameObjectsToDestroy;

	void DestroyQueuedGameObjects();
	bool UpdateInput();

public:
	MyGame(Drawer* drawer);
	~MyGame();

	static MyGame* Instance;

	std::vector<GameObject*> GetGameObjectsByTag(const TagManager& _tag);
	std::vector<GameObject*> GetAllGameObjects() const;

	template<class T = BaseComponent>
	std::vector<T*> GetComponents()
	{
		std::vector<T*> output;
		for (GameObject* go : gameObjects)
		{
			if (go == nullptr)
				continue;

			T* component = go->GetComponent<T>();
			if (component != nullptr)
				output.push_back(component);
		}
		return output;
	}
	template<class T = BaseComponent>
	T* GetComponent()
	{
		for (GameObject* go : gameObjects)
		{
			if (go == nullptr)
				continue;

			T* component = go->GetComponent<T>();
			if (component != nullptr)
				return component;
		}
		return nullptr;
	}

	template<class T = BaseComponent>
	std::vector<GameObject*> GetGameObjectsByComponent()
	{
		std::vector<GameObject*> result;
		for (GameObject* obj : gameObjects)
		{
			if (obj == nullptr)
				continue;

			if (obj->GetComponent<T>() != nullptr)
				result.push_back(obj);
		}
		return result;
	}

	template<class T = BaseComponent>
	GameObject* GetGameObjectByComponent()
	{
		for (GameObject* obj : gameObjects)
		{
			if (obj == nullptr)
				continue;

			if (obj->GetComponent<T>() != nullptr)
				return obj;
		}
		return nullptr;
	}

	Vector2f TakeInput() const;
	void ResetInput();
	bool ShowFPS();
	void Draw() const;
	GameObject* CreateGameObjectInstance(const Vector2f& pos = Vector2f(0.0f, 0.0f));
	void DestroyGameObject(GameObject* go);
	void Start();
	bool Update(const float dt);
	Drawer* GetDrawer() const;
};
#endif