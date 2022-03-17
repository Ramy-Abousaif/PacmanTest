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
private:
	SpriteRenderer* spriteRenderer;
	std::vector<Animation> animations;
	unsigned int animationIndex = 0;
	unsigned int frameIndex = 0;
	float counter = 0.0f;

public:
	Animator();
	~Animator() override;
	void Start() override;
	void Update(const float dt) override;
	void SetFlip(const bool x, const bool y);
	void SetRotation(const float angle);
	void SetCurrentAnimation(const std::string& name);
	void AddAnimation(const Animation& animation);
};
#endif