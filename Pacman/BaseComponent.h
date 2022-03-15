#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

#include "GameObject.h"

class BaseComponent
{
public:
	GameObject* GO = nullptr;

public:
	BaseComponent() = default;
	~BaseComponent() = default;

	virtual void Start();
	virtual void Draw() const {};
	virtual void Update(const float deltaTime) {};
	void SetGO(GameObject* go);
};
#endif