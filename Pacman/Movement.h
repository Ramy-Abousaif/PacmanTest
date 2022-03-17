#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "BaseComponent.h"

class PathmapTile;
class PathPosition;

class Movement : public BaseComponent
{
private:
	PathmapTile* map = nullptr;
	PathPosition* pathPosition = nullptr;

	unsigned int desiredPosX = 0;
	unsigned int desiredPosY = 0;
	unsigned int currentPosX = 0;
	unsigned int currentPosY = 0;

public:
	Movement();
	~Movement() override;

	void Start() override;
	void Update(const float dt) override;
	bool SetDesiredPos(const unsigned int x, const unsigned int y);
	unsigned int GetDesiredPosX() const;
	unsigned int GetDesiredPosY() const;
	void SetCurrentPos(const unsigned int x, const unsigned int y);
	unsigned int GetCurrentPosX() const;
	unsigned int GetCurrentPosY() const;
	bool ReachedDesiredPos() const;

private:
	bool IsWalkable(const unsigned int x, const unsigned int y) const;
};
#endif