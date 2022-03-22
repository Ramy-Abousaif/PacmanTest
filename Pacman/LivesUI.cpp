#include "LivesUI.h"
#include "Drawer.h"
#include "GameObject.h"
#include "GameManager.h"
#include "TextUI.h"
#include <string>
#include <sstream>
#include "MyGame.h"

LivesUI::LivesUI()
{
	this->text = nullptr;
}


LivesUI::~LivesUI()
{
}

void LivesUI::Awake()
{
	this->text = GetGameObject()->GetComponent<TextUI>();
	if (this->text == nullptr)
		this->text = GetGameObject()->AddComponent<TextUI>();
}

void LivesUI::Start()
{
	GameManager* gameManager = MyGame::Instance->GetComponent<GameManager>();
	if(gameManager != nullptr)
		gameManager->Assign((LivesUpdateEventListener*)this);
}

void LivesUI::ShowLives(const unsigned int _lives)
{
	std::string text;
	std::stringstream textStream;
	textStream << _lives;
	text = textStream.str();
	this->text->SetText(text);
}

void LivesUI::OnEvent(const LivesUpdateEvent& event, const LivesUpdateEventDispatcher& sender)
{
	ShowLives(event.lives);
}