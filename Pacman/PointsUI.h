#ifndef POINTSUI_H
#define POINTSUI_H

#include "BaseComponent.h"
#include "Event.h"

class TextUI;

class PointsUI : public BaseComponent, PointsCollectedEventListener
{
private:
	TextUI* text = nullptr;

public:
	PointsUI();
	~PointsUI() override;

	void Awake() override;
	void Start() override;
	void ShowPoints(const unsigned int _points);
	void OnEvent(const PointsCollectedEvent& event, const PointsCollectedEventDispatcher& sender) override;
};
#endif