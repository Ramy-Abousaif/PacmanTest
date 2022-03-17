#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "Drawer.h"
#include "BaseComponent.h"

class SpriteRenderer : public BaseComponent
{
private:
	Drawer* drawer;
	const char* path;
	bool flipX = false;
	bool flipY = false;
	float rot = 0.f;
public:
	SpriteRenderer();
	~SpriteRenderer() override;

	void Draw() const override;
	void SetDrawer(Drawer* drawer);
	void SetFlip(const bool x, const bool y);
	void SetRotation(const float angle);
	void SetSprite(const char* path);
	void Update(const float dt) override;
};
#endif