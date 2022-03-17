#include "PointsUI.h"
#include "TextUI.h"
#include "Drawer.h"
#include <string>
#include <sstream>

PointsUI::PointsUI()
{
	this->text = nullptr;
}

PointsUI::~PointsUI()
{
}

void PointsUI::Start()
{
	this->text = gameObject->GetComponent<TextUI>();
}

void PointsUI::OnEvent(const PointsCollectedEvent& event, const PointsCollectedEventDispatcher& sender)
{
	std::string text;
	std::stringstream textStream;
	textStream << event.points;
	text = textStream.str();
	this->text->SetText(text);
}
