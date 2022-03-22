#ifndef TEXTUI_H
#define TEXTUI_H

#include <string>
#include "BaseComponent.h"

class Drawer;

class TextUI : public BaseComponent
{
protected:
	void _Draw() const override;

private:
	std::string text;
	int posX = 0;
	int posY = 0;
	const char* fontPath;

public:
	TextUI();
	~TextUI() override;

	void SetPos(const int x, const int y);
	void SetText(const std::string& text);
	void SetFont(const char* fontPath);
	int GetPosX() const;
    int GetPosY() const;
};
#endif