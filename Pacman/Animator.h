#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "BaseComponent.h"
#include <vector>
#include <string>

class SpriteRenderer;

struct Animation
{
	std::string name;
	std::vector<char*> sprites;
	float timeBetweenFrames = 1.0f;
};

class Animator : public BaseComponent
{
protected:
	void _Update(const float& dt) override;

private:
	SpriteRenderer* spriteRenderer;
	std::vector<Animation> animations;
	unsigned int animationIndex = 0;
	unsigned int frameIndex = 0;
	float counter = 0.0f;
    bool pause = false;
	float originR = 255, originG = 255, originB = 255;

public:
	Animator();
	~Animator() override;
	void Awake() override;
	void SetFlip(const bool x, const bool y);
	void SetRotation(const float angle);
	void Flash(float _timer, float _duration, const float offset, const float modulus, const float thresHold);
	void ForceOriginColour();
	void SetCurrentAnimation(const std::string& name);
	void AddAnimation(const Animation& animation);
	void SetPause(const bool _pause);
};
#endif