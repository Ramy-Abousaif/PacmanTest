#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

#include "GameObject.h"

class BaseComponent
{
public:
	BaseComponent() = default;
	virtual ~BaseComponent() = default;

	GameObject* gameObject = nullptr;
	virtual void Start();
	virtual void Draw() const;
	virtual void Update(const float dt);
	void SetGO(GameObject* go);
};
#endif