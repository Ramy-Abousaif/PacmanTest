#ifndef DOT_H
#define DOT_H

#include "BaseComponent.h"

class Dot : public BaseComponent
{
private:
	unsigned int pointsToAdd = 0;

public:
	Dot();
	~Dot() override;
	void Start() override;
	void Update(const float dt) override;
	void SetAddedPoints(const int points);
	int GetAddedPoints() const;
};
#endif