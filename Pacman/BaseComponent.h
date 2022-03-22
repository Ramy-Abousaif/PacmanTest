#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

class GameObject;

class BaseComponent
{
protected:
	virtual void _Draw() const {};
	virtual void _Update(const float& dt) {};

private:
	bool active = true;
	GameObject* gameObject = nullptr;

public:
	BaseComponent();
	virtual ~BaseComponent() = default;

	virtual void Awake();
	virtual void Start();
	void SetActive(const bool _active);
	bool GetActive() const;
	GameObject* GetGameObject() const;
	void SetGO(GameObject* go);
	void Draw() const;
	void Update(const float dt);
};
#endif