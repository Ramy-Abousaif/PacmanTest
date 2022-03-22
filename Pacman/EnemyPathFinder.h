#ifndef ENEMYPATHFINDER_H
#define ENEMYPATHFINDER_H

#include "BaseComponent.h"

struct Tile;
class Movement;
class PathPosition;

class EnemyPathFinder : public BaseComponent
{
protected:
	void _Update(const float& dt) override;
	int SqrDist(Tile* tile1, Tile* tile2) const;
	bool WalkableTile(Tile* tile) const;
	void NextDesiredPos();

private:
	Tile* target = nullptr;
	Movement* movement = nullptr;
	PathPosition* pathPosition = nullptr;

	bool includePlayerTiles = false;

	int lookDirX = 0, lookDirY = 0;

public:
	EnemyPathFinder();
	~EnemyPathFinder() override;

	void Awake() override;
	void SetDesiredPos(const unsigned int x, const unsigned int y, const bool los = true);
	void SetPlayerTileInclusion(const bool _includeTile);
	bool ReachedDesiredPos() const;
};
#endif