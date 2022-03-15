#include "GameObject.h"

class BaseComponent
{
public:
	GameObject* GO = nullptr;

public:
	BaseComponent() = default;
	~BaseComponent() = default;

	virtual void Draw() const {};
	virtual void Update(const float deltaTime) {};
	void SetGO(GameObject* go);
};

