#include "Drawer.h"
#include "BaseComponent.h"

class SpriteRenderer : public BaseComponent
{
private:
	Drawer* drawer;
	const char* path;
public:
	SpriteRenderer() = default;
	~SpriteRenderer() = default;

	void Draw() const override;
	void SetDrawer(Drawer* drawer);
	void SetSprite(const char* path);
	void Update(const float dt) override {};
};

