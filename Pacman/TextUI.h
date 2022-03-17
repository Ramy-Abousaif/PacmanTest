#ifndef TEXTUI_H
#define TEXTUI_H

#include <string>
#include "BaseComponent.h"

class Drawer;

class TextUI : public BaseComponent
{
private:
	Drawer* drawer = nullptr;
	std::string text;
	int posX = 0;
	int posY = 0;
	const char* fontPath;

public:
	TextUI();
	~TextUI() override;

	void Draw() const override;
	void SetDrawer(Drawer* drawer);
	void SetPos(const int x, const int y);
	void SetText(const std::string& text);
	void SetFont(const char* fontPath);
	int GetPosX() const;
    int GetPosY() const;
	void Update(const float dt) override;
};
#endif