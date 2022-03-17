#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer()
{
	drawer = nullptr;
	path = nullptr;
	flipX = false;
	flipY = false;
	rot = 0.f;
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::Update(const float dt)
{

}

void SpriteRenderer::SetDrawer(Drawer* drawer)
{
	this->drawer = drawer;
}

void SpriteRenderer::SetSprite(const char* path)
{
	this->path = path;
}

void SpriteRenderer::Draw() const
{
	drawer->Draw(path, gameObject->pos, flipX, flipY, rot);
}

void SpriteRenderer::SetFlip(const bool x, const bool y)
{
	this->flipX = x;
	this->flipY = y;
}

void SpriteRenderer::SetRotation(const float angle)
{
	this->rot = angle;
}