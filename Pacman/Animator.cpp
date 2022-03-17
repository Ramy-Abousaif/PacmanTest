#include "Animator.h"
#include "SpriteRenderer.h"

Animator::Animator()
{
	this->spriteRenderer = nullptr;
	this->counter = 0.f;
	this->frameIndex = 0;
}

Animator::~Animator()
{
}

void Animator::Start()
{
	this->spriteRenderer = gameObject->GetComponent<SpriteRenderer>();
}

void Animator::SetRotation(const float angle)
{
	this->spriteRenderer->SetRotation(angle);
}

void Animator::SetFlip(const bool x, const bool y)
{
	this->spriteRenderer->SetFlip(x, y);
}

void Animator::Update(const float dt)
{
	counter += dt;
	if (counter >= animations[animationIndex].timeBetweenFrames)
	{
		frameIndex = (frameIndex + 1) % animations[animationIndex].sprites.size();
		counter = 0.0f;
		this->spriteRenderer->SetSprite(animations[animationIndex].sprites[frameIndex]);
	}
}

void Animator::SetCurrentAnimation(const std::string& name)
{
	for (unsigned int i = 0; i < animations.size(); ++i)
	{
		if (name.compare(animations[i].name) == 0)
		{
			animationIndex = i;
			frameIndex = 0;
			this->spriteRenderer->SetSprite(animations[animationIndex].sprites[frameIndex]);
		}
	}

}

void Animator::AddAnimation(const Animation& animation)
{
	if (animation.sprites.size() < 1)
		return;

	animations.push_back(animation);
}
