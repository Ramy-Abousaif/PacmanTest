#include "MyGame.h"
#include "BaseComponent.h"
#include "Drawer.h"

class PlayerController : public BaseComponent
{
private:
	MyGame* gameInstance;
	float speed = 1.0f;

public:
	PlayerController() = default;
	~PlayerController() = default;
	void SetGameInstance(MyGame* game);
	void SetPlayerSpeed(const float speed);
	virtual void Update(const float dt) override;
};

