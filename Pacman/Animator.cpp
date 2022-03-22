#include "Animator.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

Animator::Animator()
{
	this->spriteRenderer = nullptr;
	this->frameIndex = 0;
}

Animator::~Animator()
{
}

void Animator::Awake()
{
	this->spriteRenderer = GetGameObject()->GetComponent<SpriteRenderer>();
	if (spriteRenderer == nullptr)
		spriteRenderer = GetGameObject()->AddComponent<SpriteRenderer>();
}

void Animator::SetRotation(const float angle)
{
	this->spriteRenderer->SetRotation(angle);
	this->originR = spriteRenderer->GetColourR();
	this->originG = spriteRenderer->GetColourG();
	this->originB = spriteRenderer->GetColourB();
}

void Animator::SetFlip(const bool x, const bool y)
{
	this->spriteRenderer->SetFlip(x, y);
}

void Animator::_Update(const float& dt)
{
	if (pause)
		return;

	counter += dt;
	if (counter >= animations[animationIndex].timeBetweenFrames)
	{
		frameIndex = (frameIndex + 1) % animations[animationIndex].sprites.size();
		counter = 0.0f;
		this->spriteRenderer->SetSprite(animations[animationIndex].sprites[frameIndex]);
	}
}

void Animator::Flash(float _timer, float _duration, const float offset, const float modulus, const float thresHold)
{
	if (_timer > (_duration - offset))
	{

		if (fmod(_timer, modulus) <= thresHold)
			this->spriteRenderer->SetColour(255.0f, 0.0f, 0.0f);
		else
			this->spriteRenderer->SetColour(originR, originG, originB);
	}
	else
		this->spriteRenderer->SetColour(originR, originG, originB);
}

void Animator::ForceOriginColour()
{
	this->spriteRenderer->SetColour(originR, originG, originB);
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
			return;
		}
	}
}

void Animator::AddAnimation(const Animation& animation)
{
	if (animation.sprites.size() < 1)
		return;

	animations.push_back(animation);

	if (animations.size() < 2)
		SetCurrentAnimation(animation.name);
}

void Animator::SetPause(const bool _pause)
{
	this->pause = _pause;
}
