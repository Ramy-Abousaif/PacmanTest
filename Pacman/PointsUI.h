#ifndef POINTSUI_H
#define POINTSUI_H

#include "BaseComponent.h"
#include "TextUI.h"
#include "Event.h"

class PointsUI : public BaseComponent, PointsCollectedEventListener
{
private:
	TextUI* text = nullptr;

public:
	PointsUI();
	~PointsUI() override;

	void Start() override;
	void OnEvent(const PointsCollectedEvent& event, const PointsCollectedEventDispatcher& sender) override;
};
#endif