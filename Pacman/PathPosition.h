#ifndef PATHPOSITION_H
#define PATHPOSITION_H

#include "BaseComponent.h"

class PathmapTile;

class PathPosition : public BaseComponent
{
private:
	PathmapTile* map = nullptr;

public:
	PathPosition();
	~PathPosition() override;

	PathmapTile* GetMap() const;
	void Awake() override;
	unsigned int GetTilePosX() const;
	unsigned int GetTilePosY() const;
	void SetPos(const unsigned int x, const unsigned int y);
};
#endif