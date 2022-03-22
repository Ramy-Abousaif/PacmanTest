#include "TextUI.h"
#include "Drawer.h"
#include "MyGame.h"

TextUI::TextUI()
{
	this->fontPath = "";
	this->posX = 0;
	this->posY = 0;
}


TextUI::~TextUI()
{
}

void TextUI::_Draw() const
{
	MyGame::Instance->GetDrawer()->DrawText(text.c_str(), fontPath, posX, posY);
}

void TextUI::SetText(const std::string& text)
{
	this->text = text;
}

void TextUI::SetFont(const char* fontPath)
{
	this->fontPath = fontPath;
}


void TextUI::SetPos(const int x, const int y)
{
	this->posX = x;
	this->posY = y;
}

int TextUI::GetPosX() const
{
	return this->posX;
}

int TextUI::GetPosY() const
{
	return this->posY;
}