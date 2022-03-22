#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "BaseComponent.h"

class SpriteRenderer : public BaseComponent
{
protected:
	void _Draw() const override;

private:
	const char* path;
	bool flipX = false;
	bool flipY = false;
	float r = 255, g = 255, b = 255;
	float rot = 0.0f;
public:
	SpriteRenderer();
	~SpriteRenderer() override;

	void SetFlip(const bool x, const bool y);
	void SetColour(float r, float g, float b);
	void SetRotation(const float angle);
	void SetSprite(const char* path);
	float GetColourR();
	float GetColourG();
	float GetColourB();
};
#endif