#include "SpriteRenderer.h"
#include "MyGame.h"
#include "Drawer.h"
#include "GameObject.h"

SpriteRenderer::SpriteRenderer()
{
	path = nullptr;
	flipX = false;
	flipY = false;
	rot = 0.0f;
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::SetSprite(const char* path)
{
	this->path = path;
}

void SpriteRenderer::_Draw() const
{
	MyGame::Instance->GetDrawer()->Draw(path, GetGameObject()->pos, flipX, flipY, rot, r, g, b);
}

void SpriteRenderer::SetColour(float r, float g, float b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

float SpriteRenderer::GetColourR()
{
	return this->r;
}

float SpriteRenderer::GetColourG()
{
	return this->g;
}

float SpriteRenderer::GetColourB()
{
	return this->b;
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