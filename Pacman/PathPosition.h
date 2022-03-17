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

	void Start() override;
	void Update(const float dt) override;
	unsigned int GetTilePosX() const;
	unsigned int GetTilePosY() const;
	Vector2f GetTileWorldPos(const unsigned int x, const unsigned int y) const;
	void SetPos(const unsigned int x, const unsigned int y);
};
#endif