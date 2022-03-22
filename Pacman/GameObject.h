#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector2f.h"
#include <Vector>

class BaseComponent;
class MyGame;

enum class TagManager : short
{
	Default,
	Manager,
	Background,
	UI,
	Player,
	Ghost,
	Teleport,
	Cherry,
	Pellet,
	BigPellet
};

class GameObject
{
private:
	std::vector<BaseComponent*> initialComponents;
	std::vector<BaseComponent*> components;
	void StartComponents();
	void UpdateComponents(const float dt);
	void DrawComponents() const;
	bool active = false;

public:
	GameObject(const Vector2f& pos);
	~GameObject();

	TagManager tag;
	Vector2f pos;
	void Draw() const;
	void Update(const float dt);
	void SetActive(const bool active);

	template<class T = BaseComponent>
	T* GetComponent()
	{
		for (BaseComponent* component : components)
		{
			T* thisComponent = dynamic_cast<T*>(component);
			if (thisComponent == nullptr)
				continue;

			return thisComponent;
		}
		return nullptr;
	}

	template<class T = BaseComponent>
	T* AddComponent()
	{
		T* component = new T();
		component->SetGO(this);
		initialComponents.push_back(component);
		components.push_back(component);
		component->Awake();
		return component;
	}
};
#endif

