#include "PlayerController.h"

void PlayerController::SetGameInstance(MyGame* game)
{
	this->gameInstance = game;
}

void PlayerController::SetPlayerSpeed(const float speed)
{
	this->speed = speed;
}

void PlayerController::Update(const float dt)
{
	const Vector2f playerInput = gameInstance->TakeInput();
	GO->Pos += playerInput * speed * dt;
}
