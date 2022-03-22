#include "Enemy.h"
#include "GameObject.h"
#include "MyGame.h"
#include "PlayerController.h"
#include "Animator.h"
#include "PathPosition.h"
#include "Movement.h"
#include "EnemyPathfinder.h"
#include "PathmapTile.h"

Enemy::Enemy()
{
	this->state = EnemyState::Still;
	this->anim = nullptr;
	this->movement = nullptr;
	this->pathPosition = nullptr;
	this->pathFinder = nullptr;
}


Enemy::~Enemy()
{
}

EnemyState Enemy::GetState() const
{
	return this->state;
}

Tile* Enemy::GetRandomTile() const
{
	PathmapTile* map = this->pathPosition->GetMap();
	Tile* tile = nullptr;

	do
		tile = map->GetTile(rand() % map->GetSizeX(), rand() % map->GetSizeY());
	while (!tile->canPlayerWalk);

	return tile;
}

void Enemy::SetChaseState()
{
	if (this->state == EnemyState::Chase)
		return;

	this->state = EnemyState::Chase;
	timer = 0.0f;
	duration = 20.0f;
	Tile* chaseTile = GetChaseTile();
	this->pathFinder->SetPlayerTileInclusion(true);
	this->pathFinder->SetDesiredPos(chaseTile->x, chaseTile->y);
	this->anim->SetCurrentAnimation("idle");
}

void Enemy::SetFleeState()
{
	const EnemyState lastState = this->state;
	if (lastState == EnemyState::Still || lastState == EnemyState::Dead)
		return;

	this->state = EnemyState::Flee;
	timer = 0.0f;
	duration = 7.0f;
	this->movement->SetSpeed(0.5f);

	if (lastState != EnemyState::Flee)
	{
		this->anim->SetCurrentAnimation("fleeing");
		if (lastState != EnemyState::LeavingPen)
		{
			this->pathFinder->SetDesiredPos(GetRandomTile()->x, GetRandomTile()->y);
			this->pathFinder->SetPlayerTileInclusion(true);
		}
	}
}

void Enemy::SetStillState()
{
	this->state = EnemyState::Still;
	timer = 0.0f;
	duration = 5.0f;
	this->movement->SetActive(false);
	this->pathFinder->SetActive(false);
	this->anim->SetCurrentAnimation("idle");
}

void Enemy::SetLeavingPenState()
{
	if (this->state != EnemyState::Still)
		return;

	this->state = EnemyState::LeavingPen;
	this->pathFinder->SetDesiredPos(this->pathPosition->GetTilePosX(), this->pathPosition->GetTilePosY() + 5);
	this->movement->SetActive(true);
	this->pathFinder->SetActive(true);
	this->pathFinder->SetPlayerTileInclusion(false);
}

void Enemy::SetRoamState()
{
	if (this->state == EnemyState::Roam)
		return;

	this->state = EnemyState::Roam;
	timer = 0.0f;
	duration = 7.0f;
	this->pathFinder->SetPlayerTileInclusion(true);
	this->pathFinder->SetDesiredPos(GetRoamTile()->x, GetRoamTile()->y);
	this->anim->SetCurrentAnimation("idle");
}

void Enemy::Awake()
{
	this->pathPosition = GetGameObject()->GetComponent<PathPosition>();
	if(pathPosition == nullptr)
		pathPosition = GetGameObject()->AddComponent<PathPosition>();

	this->movement = GetGameObject()->GetComponent<Movement>();
	if(movement == nullptr)
		movement = GetGameObject()->AddComponent<Movement>();

	this->pathFinder = GetGameObject()->GetComponent<EnemyPathFinder>();
	if (pathFinder == nullptr)
		pathFinder = GetGameObject()->AddComponent<EnemyPathFinder>();

	this->anim = GetGameObject()->GetComponent<Animator>();
	if(anim == nullptr)
		anim = GetGameObject()->AddComponent<Animator>();

	SetUpAnims();
}

void Enemy::Start()
{
	this->anim->SetCurrentAnimation("idle");
	this->movement->SetCurrentPos(GetGhostTile()->x, GetGhostTile()->y);
	this->movement->SetActive(false);
	this->pathFinder->SetActive(false);
	this->movement->SetSpeed(3.0f);
	this->movement->SetOriginSpeed(3.0f);

	PlayerController* playerController = MyGame::Instance->GetComponent<PlayerController>();
	playerController->Assign((BigPelletCollectedEventListener*)this);
}

void Enemy::_Update(const float& dt)
{
	timer += dt;

	switch (state)
	{
		case EnemyState::Flee:
		{
			if (this->pathFinder->ReachedDesiredPos())
				this->pathFinder->SetDesiredPos(GetRandomTile()->x, GetRandomTile()->y);

			this->anim->Flash(timer, duration, 2, 0.5f, 0.15f);
		}
		break;
		case EnemyState::Chase:
		{
			if (this->pathFinder->ReachedDesiredPos())
				this->pathFinder->SetDesiredPos(GetChaseTile()->x, GetChaseTile()->y, false);
		}
		break;
		case EnemyState::LeavingPen:
		{
			if (!this->pathFinder->ReachedDesiredPos())
				return;
		}
		break;
		case EnemyState::Dead:
		{
			//Goes back to pen and stay there
			if (this->pathFinder->ReachedDesiredPos())
				SetStillState();

			return;
		}
		break;
		case EnemyState::Roam:
		{
			//Set regularly by timer
		}
		break;
	}

	//Regularly check the timer to enter a new state
	if (timer >= duration)
		GoToState();
}

void Enemy::GoToState()
{
	this->anim->ForceOriginColour();
	this->movement->SetSpeed(3.0f);
	switch (state)
	{
		case EnemyState::Dead:
		{
			//State set in player controller
		}
		break;
		case EnemyState::Still:
		{
			SetLeavingPenState();
		}
		break;
		case EnemyState::LeavingPen:
		{
			if (this->pathFinder->ReachedDesiredPos())
				SetRoamState();
		}
		break;
		default:
		{
			//Regularly switch between chase and roam state when method is called
			if (stateIndex < 5)
			{
				if (state == EnemyState::Chase)
				{
					SetRoamState();
					stateIndex++;
				}
				else
					SetChaseState();
			}
			else
				SetChaseState();
		}
		break;
	}
}

void Enemy::SetNewDuration(const float seconds)
{
	if (seconds < 0.0f)
		return;

	duration = seconds;
	timer = 0.0f;
}

void Enemy::SetDeadState()
{
	if (this->state != EnemyState::Flee)
		return;

	this->state = EnemyState::Dead;
	this->anim->ForceOriginColour();
	this->movement->SetSpeed(3.0f);
	this->pathFinder->SetDesiredPos(GetGhostTile()->x, GetGhostTile()->y);
	this->anim->SetCurrentAnimation("dead");
	this->pathFinder->SetPlayerTileInclusion(false);
}

void Enemy::OnEvent(const BigPelletCollectedEvent& event, const BigPelletCollectedEventDispatcher& sender)
{
	SetFleeState();
}

/*RED GHOST*/

void RedGhost::SetUpAnims()
{
	Animation idleAnim;
	idleAnim.name = "idle";
	idleAnim.sprites = { "ghost_32_red.png" };
	idleAnim.timeBetweenFrames = 60.0f;

	Animation fleeingAnim;
	fleeingAnim.name = "fleeing";
	fleeingAnim.sprites = { "Ghost_Vulnerable_32.png" };
	fleeingAnim.timeBetweenFrames = 60.0f;

	Animation deadAnim;
	deadAnim.name = "dead";
	deadAnim.sprites = { "Ghost_Dead_32.png" };
	deadAnim.timeBetweenFrames = 60.0f;

	this->anim->AddAnimation(idleAnim);
	this->anim->AddAnimation(fleeingAnim);
	this->anim->AddAnimation(deadAnim);
}

//Spawn pos
Tile* RedGhost::GetGhostTile() const
{
	return this->pathPosition->GetMap()->GetTile(12, 16);
}

//Initial roam target
Tile* RedGhost::GetRoamTile() const
{
	return this->pathPosition->GetMap()->GetTile(25, 0);
}

//Behaviour: Chase state is always going to get the player's position
Tile* RedGhost::GetChaseTile() const
{
	PlayerController* playerController = MyGame::Instance->GetComponent<PlayerController>();
	Vector2f playerPos = playerController->GetGameObject()->pos;
	const unsigned int playerPosX = this->pathPosition->GetMap()->WorldPosToTilePosX(playerPos.X);
	const unsigned int playerPosY = this->pathPosition->GetMap()->WorldPosToTilePosY(playerPos.Y);
	return this->pathPosition->GetMap()->GetTile(playerPosX, playerPosY);
}

/*ORANGE GHOST*/

void OrangeGhost::SetUpAnims()
{
	Animation idleAnim;
	idleAnim.name = "idle";
	idleAnim.sprites = { "ghost_32_orange.png" };
	idleAnim.timeBetweenFrames = 60.0f;

	Animation fleeingAnim;
	fleeingAnim.name = "fleeing";
	fleeingAnim.sprites = { "Ghost_Vulnerable_32.png" };
	fleeingAnim.timeBetweenFrames = 60.0f;

	Animation deadAnim;
	deadAnim.name = "dead";
	deadAnim.sprites = { "Ghost_Dead_32.png" };
	deadAnim.timeBetweenFrames = 60.0f;

	this->anim->AddAnimation(idleAnim);
	this->anim->AddAnimation(fleeingAnim);
	this->anim->AddAnimation(deadAnim);
}

//Spawn pos
Tile* OrangeGhost::GetGhostTile() const
{
	return this->pathPosition->GetMap()->GetTile(15, 16);
}

//Initial roam target
Tile* OrangeGhost::GetRoamTile() const
{
	return this->pathPosition->GetMap()->GetTile(27, 0);
}

//Behaviour: Always roam unless player is within a certain distance in the chase state
Tile* OrangeGhost::GetChaseTile() const
{
	const int ghostPosX = (int)this->pathPosition->GetTilePosX();
	const int ghostPosY = (int)this->pathPosition->GetTilePosY();

	PlayerController* playerController = MyGame::Instance->GetComponent<PlayerController>();
	const int playerPosX = (int)this->pathPosition->GetMap()->WorldPosToTilePosX(playerController->GetGameObject()->pos.X);
	const int playerPosY = (int)this->pathPosition->GetMap()->WorldPosToTilePosX(playerController->GetGameObject()->pos.Y);

	int sqrDistance = (ghostPosY - playerPosY) * (ghostPosY - playerPosY) + (ghostPosY - playerPosY) * (ghostPosY - playerPosY);

	if (sqrDistance < 36)
		return GetRoamTile();
	else
		return this->pathPosition->GetMap()->GetTile(playerPosX, playerPosY);
}

/*PINK GHOST*/

void PinkGhost::SetUpAnims()
{
	Animation idleAnim;
	idleAnim.name = "idle";
	idleAnim.sprites = { "ghost_32_pink.png" };
	idleAnim.timeBetweenFrames = 60.0f;

	Animation fleeingAnim;
	fleeingAnim.name = "fleeing";
	fleeingAnim.sprites = { "Ghost_Vulnerable_32.png" };
	fleeingAnim.timeBetweenFrames = 60.0f;

	Animation deadAnim;
	deadAnim.name = "dead";
	deadAnim.sprites = { "Ghost_Dead_32.png" };
	deadAnim.timeBetweenFrames = 60.0f;

	this->anim->AddAnimation(idleAnim);
	this->anim->AddAnimation(fleeingAnim);
	this->anim->AddAnimation(deadAnim);
}

//Spawn pos
Tile* PinkGhost::GetGhostTile() const
{
	return this->pathPosition->GetMap()->GetTile(14, 16);
}

//Initial roam target
Tile* PinkGhost::GetRoamTile() const
{
	return this->pathPosition->GetMap()->GetTile(0, 0);
}

//Behaviour: Tries to get player's future position as a target while chasing them
Tile* PinkGhost::GetChaseTile() const
{
	PlayerController* playerController = MyGame::Instance->GetComponent<PlayerController>();
	Movement* playerMovement = playerController->GetGameObject()->GetComponent<Movement>();
	const unsigned int playerPosX = this->pathPosition->GetMap()->WorldPosToTilePosX(playerController->GetGameObject()->pos.X);
	const unsigned int playerPosY = this->pathPosition->GetMap()->WorldPosToTilePosY(playerController->GetGameObject()->pos.Y);
	int playerDirX = playerMovement->GetDirX();
	int playerDirY = playerMovement->GetDirY();

	//If within bounds get furthest distance with direction aka 4
	for (int i = 4; i >= 0; --i)
	{
		if (this->pathPosition->GetMap()->IsPosValid(playerPosX + playerDirX * i, playerPosY + playerDirY * i))
		{
			playerDirX *= i;
			playerDirY *= i;
			break;
		}
	}

	return this->pathPosition->GetMap()->GetTile(playerPosX + playerDirX, playerPosY + playerDirY);
}

/*BLUE GHOST*/

void BlueGhost::SetUpAnims()
{
	Animation idleAnim;
	idleAnim.name = "idle";
	idleAnim.sprites = { "ghost_32_cyan.png" };
	idleAnim.timeBetweenFrames = 60.0f;

	Animation fleeingAnim;
	fleeingAnim.name = "fleeing";
	fleeingAnim.sprites = { "Ghost_Vulnerable_32.png" };
	fleeingAnim.timeBetweenFrames = 60.0f;

	Animation deadAnim;
	deadAnim.name = "dead";
	deadAnim.sprites = { "Ghost_Dead_32.png" };
	deadAnim.timeBetweenFrames = 60.0f;

	this->anim->AddAnimation(idleAnim);
	this->anim->AddAnimation(fleeingAnim);
	this->anim->AddAnimation(deadAnim);
}

//Spawn pos
Tile* BlueGhost::GetGhostTile() const
{
	return this->pathPosition->GetMap()->GetTile(13, 16);
}

//Initial roam target
Tile* BlueGhost::GetRoamTile() const
{
	return this->pathPosition->GetMap()->GetTile(0, 30);
}

//Behaviour: Tries to get player's future position as a target while chasing them
Tile* BlueGhost::GetChaseTile() const
{
	PlayerController* playerController = MyGame::Instance->GetComponent<PlayerController>();
	Movement* playerMovement = playerController->GetGameObject()->GetComponent<Movement>();
	const unsigned int playerPosX = this->pathPosition->GetMap()->WorldPosToTilePosX(playerController->GetGameObject()->pos.X);
	const unsigned int playerPosY = this->pathPosition->GetMap()->WorldPosToTilePosY(playerController->GetGameObject()->pos.Y);
	int playerDirX = playerMovement->GetDirX() * 2;
	int playerDirY = playerMovement->GetDirY() * 2;

	//If within bounds get furthest distance with direction aka 2
	for (int i = 2; i >= 0; --i)
	{
		if (this->pathPosition->GetMap()->IsPosValid(playerPosX + playerDirX * i, playerPosY + playerDirY * i))
		{
			playerDirX *= i;
			playerDirY *= i;
			break;
		}
	}

	return this->pathPosition->GetMap()->GetTile(playerPosX + playerDirX, playerPosY + playerDirY);
}