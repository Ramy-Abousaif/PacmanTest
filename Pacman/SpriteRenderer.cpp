#include "SpriteRenderer.h"

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
	drawer->Draw(path, GO->Pos);
}
