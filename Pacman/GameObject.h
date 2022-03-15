#include "Vector2f.h"
#include <list>

class BaseComponent;
class GameObject
{
private:
	bool Active;
	std::list<BaseComponent*> components;
	void UpdateComponents(const float dt);

public:
	GameObject();
	GameObject(const Vector2f& pos);
	~GameObject() = default;

	void Draw() const;
	virtual void Update(const float dt);
	void SetActive(const bool active);

	Vector2f Pos;

	template<class T = BaseComponent>
	T* AddComponent()
	{
		T* component = new T();
		component->SetGO(this);
		components.push_back(component);
		return component;
	}
};

