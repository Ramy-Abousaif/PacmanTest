#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector2f.h"
#include <Vector>

class BaseComponent;
class MyGame;

enum class TagManager : short
{
	Background,
	UI,
	Player,
	Ghost,
	Teleport,
	Dot,
	BigDot
};

class GameObject
{
private:
	std::vector<BaseComponent*> components;
	void UpdateComponents(const float dt);
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
		for (unsigned int i = 0; i < components.size(); ++i)
		{
			T* component = dynamic_cast<T*>(components[i]);
			if (component == nullptr)
				continue;

			return component;
		}
		return nullptr;
	}

	template<class T = BaseComponent>
	T* AddComponent()
	{
		T* component = new T();
		component->SetGO(this);
		components.push_back(component);
		component->Start();
		return component;
	}
};
#endif

