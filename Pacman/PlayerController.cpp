#include "PlayerController.h"
#include "PathPosition.h"
#include "Movement.h"
#include "Collision.h"
#include "MyGame.h"
#include "GameObject.h"
#include "Animator.h"
#include "Teleporter.h"
#include "Enemy.h"
#include "PathmapTile.h"
#include <vector>

PlayerController::PlayerController()
{
	this->anim = nullptr;
	this->pathPosition = nullptr;
	this->movement = nullptr;
	this->tpLoc = nullptr;
}

PlayerController::~PlayerController()
{
}

void PlayerController::Assign(PelletCollectedEventListener* listener)
{
	PelletCollectedEventDispatcher::Assign(listener);
}

void PlayerController::Unassign(PelletCollectedEventListener* listener)
{
	PelletCollectedEventDispatcher::Unassign(listener);
}

void PlayerController::Assign(BigPelletCollectedEventListener* listener)
{
	BigPelletCollectedEventDispatcher::Assign(listener);
}

void PlayerController::Unassign(BigPelletCollectedEventListener* listener)
{
	BigPelletCollectedEventDispatcher::Unassign(listener);
}

void PlayerController::Assign(PlayerHitEventListener* listener)
{
	PlayerHitEventDispatcher::Assign(listener);
}

void PlayerController::Unassign(PlayerHitEventListener* listener)
{
	PlayerHitEventDispatcher::Unassign(listener);
}

void PlayerController::Assign(GhostKilledEventListener* listener)
{
	GhostKilledEventDispatcher::Assign(listener);
}

void PlayerController::Unassign(GhostKilledEventListener* listener)
{
	GhostKilledEventDispatcher::Unassign(listener);
}

void PlayerController::Hit()
{
	PlayerHitEvent playerHitEvent;
	PlayerHitEventDispatcher::Invoke(playerHitEvent);
}

void PlayerController::Pellet()
{
	PelletCollectedEvent pelletCollectedEvent;
	PelletCollectedEventDispatcher::Invoke(pelletCollectedEvent);
}

void PlayerController::BigPellet()
{
	BigPelletCollectedEvent bigPointsCollectedEvent;
	BigPelletCollectedEventDispatcher::Invoke(bigPointsCollectedEvent);
}

void PlayerController::GhostKill()
{
	GhostKilledEvent ghostKilledEvent;
	GhostKilledEventDispatcher::Invoke(ghostKilledEvent);
}

void PlayerController::OnEvent(const CollisionEvent& event, const CollisionEventDispatcher& other)
{
	switch (event.other->tag)
	{
		case TagManager::Ghost:
		{
			Enemy* ghost = event.other->GetComponent<Enemy>();
			if (ghost->GetState() != EnemyState::Dead)
			{
				if (ghost->GetState() == EnemyState::Flee)
				{
					ghost->SetDeadState();
					GhostKill();
				}
				else
					Hit();
			}
		}
		break;
		case TagManager::Teleport:
		{
			if (event.type == CollisionType::OnEnter && tpLoc == nullptr)
			{
				Teleporter* teleporter = event.other->GetComponent<Teleporter>();
				Teleporter* otherTeleporter = teleporter->GetOtherTP();
				tpLoc = otherTeleporter;
				this->GetGameObject()->pos = otherTeleporter->GetGameObject()->pos;
				const int currentXPos = (int)pathPosition->GetTilePosX();
				const int currentYPos = (int)pathPosition->GetTilePosY();
				const unsigned int DesiredLocX = (unsigned int)(currentXPos + movement->GetDirX());
				const unsigned int DesiredLocY = (unsigned int)(currentYPos + movement->GetDirY());
				movement->SetDesiredPos(DesiredLocX, DesiredLocY);
			}
			else if (event.type == CollisionType::OnExit && event.other == tpLoc->GetGameObject())
				tpLoc = nullptr;
		}
		break;
		case TagManager::Pellet:
		{
			Pellet();
			MyGame::Instance->DestroyGameObject(event.other);
		}
		break;
		case TagManager::BigPellet:
		{
			BigPellet();
			MyGame::Instance->DestroyGameObject(event.other);
		}
		break;
	}
}

void PlayerController::Awake()
{
	this->movement = GetGameObject()->GetComponent<Movement>();
	if (movement == nullptr)
		movement = GetGameObject()->AddComponent<Movement>();

	this->pathPosition = GetGameObject()->GetComponent<PathPosition>();
	if (pathPosition == nullptr)
		pathPosition = GetGameObject()->AddComponent<PathPosition>();

	this->anim = GetGameObject()->GetComponent<Animator>();
	if (anim == nullptr)
		anim = GetGameObject()->AddComponent<Animator>();

	if(GetGameObject()->GetComponent<Collision>() == nullptr)
		GetGameObject()->AddComponent<Collision>();

	Animation idlePlayerAnim;
	idlePlayerAnim.name = "idle";
	idlePlayerAnim.sprites = { "closed_32.png" , "open_32.png" };
	idlePlayerAnim.timeBetweenFrames = 0.25f;
	this->anim->AddAnimation(idlePlayerAnim);
	this->anim->SetPause(true);
	MyGame::Instance->ResetInput();
}

void PlayerController::Start()
{
	this->pathPosition->SetPos(14, 7);
	this->movement->SetSpeed(4.0f);
	this->movement->SetOriginSpeed(4.0f);

	Collision* collision = GetGameObject()->GetComponent<Collision>();

	std::vector<GameObject*> pellets = MyGame::Instance->GetGameObjectsByTag(TagManager::Pellet);
	for (GameObject* pellet : pellets)
		collision->AddOther(pellet);

	std::vector<GameObject*> bigPellets = MyGame::Instance->GetGameObjectsByTag(TagManager::BigPellet);
	for (GameObject* bigPellet : bigPellets)
		collision->AddOther(bigPellet);

	std::vector<GameObject*> ghosts = MyGame::Instance->GetGameObjectsByTag(TagManager::Ghost);
	for (GameObject* ghost : ghosts)
		collision->AddOther(ghost);

	std::vector<GameObject*> teleporters = MyGame::Instance->GetGameObjectsByTag(TagManager::Teleport);
	for (GameObject* teleporter : teleporters)
		collision->AddOther(teleporter);

	collision->Assign((CollisionEventListener*)this);
}

void PlayerController::_Update(const float& dt)
{
	if (this->movement->ReachedDesiredPos())
	{
		const unsigned int currentPosX = this->movement->GetCurrentPosX();
		const unsigned int currentPosY = this->movement->GetCurrentPosY();

		const Vector2f myInput = MyGame::Instance->TakeInput();
		int inputX = (int)myInput.X;
		int inputY = (int)myInput.Y;

		if (IsWalkable(currentPosX + inputX, currentPosY + inputY) && (inputX != 0 || inputY != 0))
		{
			if (this->movement->SetDesiredPos(currentPosX + inputX, currentPosY + inputY))
			{
				prevInputX = inputX;
				prevInputY = inputY;
			}
		}
		else if (IsWalkable(currentPosX + prevInputX, currentPosY + prevInputY))
			this->movement->SetDesiredPos(currentPosX + prevInputX, currentPosY + prevInputY);
	}

	float rot = 90.0f * (float)prevInputY;
	const bool flipX = (prevInputX < 0);
	if (!flipX)
		rot *= -1;

	this->anim->SetRotation(rot);
	this->anim->SetFlip(flipX, false);
	this->anim->SetPause(this->movement->ReachedDesiredPos());
}

bool PlayerController::IsWalkable(const unsigned int x, const unsigned int y) const
{
	if (!this->pathPosition->GetMap()->IsPosValid(x, y))
		return false;

	Tile* tile = this->pathPosition->GetMap()->GetTile(x, y);
	return tile->canPlayerWalk;
}
