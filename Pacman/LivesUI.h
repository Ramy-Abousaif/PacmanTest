#ifndef LIVESUI_H
#define LIVESUI_H

#include "BaseComponent.h"
#include "Event.h"

class TextUI;

class LivesUI : public BaseComponent, LivesUpdateEventListener
{
private:
	TextUI* text = nullptr;

public:
	LivesUI();
	~LivesUI() override;

	void Awake() override;
	void Start() override;
	void ShowLives(const unsigned int _lives);
	void OnEvent(const LivesUpdateEvent& event, const LivesUpdateEventDispatcher& sender) override;
};
#endif