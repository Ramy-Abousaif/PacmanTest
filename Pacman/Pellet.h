#ifndef PELLET_H
#define PELLET_H

#include "BaseComponent.h"

class Pellet : public BaseComponent
{
private:
	unsigned int pointsToAdd = 0;

public:
	Pellet();
	~Pellet() override;
	void SetAddedPoints(const int points);
	int GetAddedPoints() const;
};
#endif