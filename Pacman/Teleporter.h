#ifndef TELEPORTER_H
#define TELEPORTER_H

#include "BaseComponent.h"

class Teleporter : public BaseComponent
{
private:
	Teleporter* other = nullptr;

public:
	Teleporter();
	~Teleporter() override;
	Teleporter* GetOtherTP();
	void SetOtherTP(Teleporter* other);
};
#endif