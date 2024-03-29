#include "PointsUI.h"
#include "TextUI.h"
#include "Drawer.h"
#include "GameObject.h"
#include "GameManager.h"
#include <string>
#include <sstream>
#include "MyGame.h"

PointsUI::PointsUI()
{
	this->text = nullptr;
}

PointsUI::~PointsUI()
{
}

void PointsUI::Awake()
{
	this->text = GetGameObject()->GetComponent<TextUI>();
	if (this->text == nullptr)
		this->text = GetGameObject()->AddComponent<TextUI>();
}

void PointsUI::Start()
{
	GameManager* gameManager = MyGame::Instance->GetComponent<GameManager>();
	if(gameManager != nullptr)
		gameManager->Assign((PointsCollectedEventListener*)this);
}

void PointsUI::ShowPoints(const unsigned int _points)
{
	std::string text;
	std::stringstream textStream;
	textStream << _points;
	text = textStream.str();
	this->text->SetText(text);
}

void PointsUI::OnEvent(const PointsCollectedEvent& event, const PointsCollectedEventDispatcher& sender)
{
	ShowPoints(event.points);
}
