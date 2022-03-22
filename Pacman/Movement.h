#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "BaseComponent.h"

class PathPosition;

class Movement : public BaseComponent
{
protected:
	void _Update(const float& dt) override;

private:
	PathPosition* pathPosition = nullptr;

	unsigned int desiredPosX = 0;
	unsigned int desiredPosY = 0;
	unsigned int currentPosX = 0;
	unsigned int currentPosY = 0;
	float speed = 1.0f;
	float originSpeed = 1.0f;

public:
	Movement();
	~Movement() override;

	void Awake() override;
	void Start() override;
	void SetSpeed(const float& _speed);
	void SetOriginSpeed(const float& _originSpeed);
	float GetOriginSpeed();
	bool SetDesiredPos(const unsigned int x, const unsigned int y);
	unsigned int GetDesiredPosX() const;
	unsigned int GetDesiredPosY() const;
	void SetCurrentPos(const unsigned int x, const unsigned int y);
	unsigned int GetCurrentPosX() const;
	unsigned int GetCurrentPosY() const;
	bool ReachedDesiredPos() const;

	int GetDirX() const;
	int GetDirY() const;
};
#endif