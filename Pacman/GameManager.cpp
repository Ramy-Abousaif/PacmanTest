#include "GameManager.h"
#include "MyGame.h"
#include "Enemy.h"
#include "PlayerController.h"
#include "Collision.h"
#include "Teleporter.h"
#include "GameObject.h"
#include "PathmapTile.h"
#include "MapLoader.h"
#include "TextUI.h"
#include "LivesUI.h"
#include "PointsUI.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Movement.h"
#include "PathPosition.h"

GameManager::GameManager()
{
	this->playerController = nullptr;
	this->gs = GameState::Pause;
	introSound = new Audio("audio\\intro.wav");
	chomp = new Audio("audio\\chomp.wav");
	bigChomp = new Audio("audio\\big_chomp.wav");
	ghostKill = new Audio("audio\\ghost_kill.wav");
	death = new Audio("audio\\death.wav");

	introSound->SetUpDevice();
	chomp->SetUpDevice();
	bigChomp->SetUpDevice();
	ghostKill->SetUpDevice();
	death->SetUpDevice();
}


GameManager::~GameManager()
{
	delete map;
	map = nullptr;
}

void GameManager::GameOver()
{
	this->gs = GameState::GameOver;

	std::vector<GameObject*> allGameObjects = MyGame::Instance->GetAllGameObjects();
	for (GameObject* obj : allGameObjects)
		MyGame::Instance->DestroyGameObject(obj);

	GameObject* gameOverGO = MyGame::Instance->CreateGameObjectInstance();
	gameOverGO->tag = TagManager::UI;
	TextUI* gameOverText = gameOverGO->AddComponent<TextUI>();
	gameOverText->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	gameOverText->SetPos(440, 300);
	gameOverText->SetText("GAME OVER");

	GameObject* pointsTextGO = MyGame::Instance->CreateGameObjectInstance();
	pointsTextGO->tag = TagManager::UI;
	TextUI* pointsText = pointsTextGO->AddComponent<TextUI>();
	pointsText->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	pointsText->SetPos(445, 325);
	pointsText->SetText("Points: ");

	GameObject* pointsValueGO = MyGame::Instance->CreateGameObjectInstance();
	pointsValueGO->tag = TagManager::UI;
	TextUI* pointsValueText = pointsValueGO->AddComponent<TextUI>();
	pointsValueText->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	pointsValueText->SetPos(545, 325);
	PointsUI* pointsUI = pointsValueGO->AddComponent<PointsUI>();
	pointsUI->ShowPoints(this->points);
}

void GameManager::Win()
{
	this->gs = GameState::GameOver;

	AddPoints(100 * lives);

	std::vector<GameObject*> allGameObjects = MyGame::Instance->GetAllGameObjects();
	for (GameObject* obj : allGameObjects)
		MyGame::Instance->DestroyGameObject(obj);

	GameObject* winTextGO = MyGame::Instance->CreateGameObjectInstance();
	winTextGO->tag = TagManager::UI;
	TextUI* winText = winTextGO->AddComponent<TextUI>();
	winText->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	winText->SetPos(450, 300);
	winText->SetText("YOU WIN!");

	GameObject* pointsTextGO = MyGame::Instance->CreateGameObjectInstance();
	pointsTextGO->tag = TagManager::UI;
	TextUI* pointsText = pointsTextGO->AddComponent<TextUI>();
	pointsText->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	pointsText->SetPos(430, 325);
	pointsText->SetText("Points: ");

	GameObject* pointsValueGO = MyGame::Instance->CreateGameObjectInstance();
	pointsValueGO->tag = TagManager::UI;
	TextUI* pointsValueText = pointsValueGO->AddComponent<TextUI>();
	pointsValueText->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	pointsValueText->SetPos(530, 325);
	PointsUI* pointsUI = pointsValueGO->AddComponent<PointsUI>();
	pointsUI->ShowPoints(this->points);
}

void GameManager::Reset()
{
	this->gs = GameState::Pause;
	timer = 0.0f;

	if (enemies.size() > 0)
	{
		for (Enemy* enemy : enemies)
			MyGame::Instance->DestroyGameObject(enemy->GetGameObject());

		enemies.clear();
	}

	if (playerController != nullptr)
		MyGame::Instance->DestroyGameObject(playerController->GetGameObject());

	readyTextGO = MyGame::Instance->CreateGameObjectInstance();
	readyTextGO->tag = TagManager::UI;
	TextUI* readyText = readyTextGO->AddComponent<TextUI>();
	readyText->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	readyText->SetPos(475, 410);
	readyText->SetText("READY!");

	InitGhosts();
	InitPlayer();
}

void GameManager::AddPoints(const unsigned int _points)
{
	points += _points;
	PointsCollectedEvent pointsCollectedEvent;
	pointsCollectedEvent.points = points;
	PointsCollectedEventDispatcher::Invoke(pointsCollectedEvent);
}

void GameManager::InitUI()
{
	//FPS UI
	fpsTextGO = MyGame::Instance->CreateGameObjectInstance();
	fpsTextGO->tag = TagManager::UI;
	TextUI* fpsText = fpsTextGO->AddComponent<TextUI>();
	fpsText->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	fpsText->SetPos(900, 50);
	fpsText->SetText("FPS: ");

	GameObject* fpsValueGO = MyGame::Instance->CreateGameObjectInstance();
	fpsValueGO->tag = TagManager::UI;
	fpsValue = fpsValueGO->AddComponent<TextUI>();
	fpsValue->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	fpsValue->SetPos(980, 50);
	fpsValue->SetText(fps);

	//Lives UI
	LivesUI* livesUI;
	GameObject* livesTextGO = MyGame::Instance->CreateGameObjectInstance();
	livesTextGO->tag = TagManager::UI;
	TextUI* livesText = livesTextGO->AddComponent<TextUI>();
	livesText->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	livesText->SetPos(20, 90);
	livesText->SetText("Lives: ");

	GameObject* livesValueGO = MyGame::Instance->CreateGameObjectInstance();
	livesValueGO->tag = TagManager::UI;
	TextUI* livesValueText = livesValueGO->AddComponent<TextUI>();
	livesValueText->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	livesValueText->SetPos(110, 90);
	livesUI = livesValueGO->AddComponent<LivesUI>();
	livesUI->ShowLives(this->lives);

	//Points UI
	PointsUI* pointsUI;
	GameObject* pointsTextGO = MyGame::Instance->CreateGameObjectInstance();
	pointsTextGO->tag = TagManager::UI;
	TextUI* pointsText = pointsTextGO->AddComponent<TextUI>();
	pointsText->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	pointsText->SetPos(20, 50);
	pointsText->SetText("Score: ");

	GameObject* pointsValueGO = MyGame::Instance->CreateGameObjectInstance();
	pointsValueGO->tag = TagManager::UI;
	TextUI* pointsValue = pointsValueGO->AddComponent<TextUI>();
	pointsValue->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	pointsValue->SetPos(110, 50);
	pointsUI = pointsValueGO->AddComponent<PointsUI>();
	pointsUI->ShowPoints(this->points);
}

void GameManager::InitMap()
{
	MapLoader mapLoader;
	map = mapLoader.Read("map.txt");
	map->SetDistBetweenTiles(0.5f);
}

void GameManager::InitMapOBJs()
{
	GameObject* background = MyGame::Instance->CreateGameObjectInstance();
	background->tag = TagManager::Background;
	SpriteRenderer* spriteRenderer = background->AddComponent<SpriteRenderer>();
	spriteRenderer->SetSprite("playfield.png");

	Teleporter* tp1 = nullptr;
	Teleporter* tp2 = nullptr;
	for (unsigned int x = 0; x < map->GetSizeX(); ++x)
	{
		for (unsigned int y = 0; y < map->GetSizeY(); ++y)
		{
			Tile* tile = map->GetTile(x, y);
			if (!tile->canPlayerWalk)
				continue;

			GameObject* mapObj = MyGame::Instance->CreateGameObjectInstance();
			PathPosition* pathPosition = mapObj->AddComponent<PathPosition>();
			pathPosition->SetPos(x, y);
			switch (tile->type)
			{
				case TileType::TeleportTile:
				{
					mapObj->tag = TagManager::Teleport;
					Teleporter* teleporter = mapObj->AddComponent<Teleporter>();

					if (tp1 == nullptr)
						tp1 = teleporter;
					else
						tp2->SetOtherTP(teleporter);

					tp2 = teleporter;
				}
				break;
				case TileType::Cherry:
				{
					/*
					mapObj->tag = TagManager::Cherry;
					SpriteRenderer* sr = mapObj->AddComponent<SpriteRenderer>();
					sr->SetSprite("Big_Dot_32.png");
					sr->SetColour(255, 0, 0);
					*/
				}
				break;
				case TileType::BigPellet:
				{
					mapObj->tag = TagManager::BigPellet;
					SpriteRenderer* sr = mapObj->AddComponent<SpriteRenderer>();
					sr->SetSprite("Big_Dot_32.png");
					pelletsOnMap++;
				}
				break;
				case TileType::Pellet:
				{
					mapObj->tag = TagManager::Pellet;
					SpriteRenderer* sr = mapObj->AddComponent<SpriteRenderer>();
					sr->SetSprite("Small_Dot_32.png");
					pelletsOnMap++;
				}
				break;
			}
		}
	}

	if (tp1 != nullptr && tp2 != nullptr && tp1 != tp2)
		tp2->SetOtherTP(tp1);
}

void GameManager::InitPlayer()
{
	GameObject* playerObject = MyGame::Instance->CreateGameObjectInstance();
	playerObject->tag = TagManager::Player;

	this->playerController = playerObject->AddComponent<PlayerController>();
	this->playerController->SetActive(false);

	this->playerController->Assign((PlayerHitEventListener*)this);
	this->playerController->Assign((PelletCollectedEventListener*)this);
	this->playerController->Assign((BigPelletCollectedEventListener*)this);
	this->playerController->Assign((GhostKilledEventListener*)this);
}

void GameManager::InitGhosts()
{
	//Order of ghosts leaving the pen red -> blue -> pink -> orange
	GameObject* redGhostGO = MyGame::Instance->CreateGameObjectInstance();
	redGhostGO->tag = TagManager::Ghost;

	RedGhost* redGhost = redGhostGO->AddComponent<RedGhost>();
	enemies.push_back(redGhost);


	GameObject* blueGhostGO = MyGame::Instance->CreateGameObjectInstance();
	blueGhostGO->tag = TagManager::Ghost;

	BlueGhost* blueGhost = blueGhostGO->AddComponent<BlueGhost>();
	enemies.push_back(blueGhost);


	GameObject* pinkGhostGO = MyGame::Instance->CreateGameObjectInstance();
	pinkGhostGO->tag = TagManager::Ghost;

	PinkGhost* pinkGhost = pinkGhostGO->AddComponent<PinkGhost>();
	enemies.push_back(pinkGhost);


	GameObject* orangeGhostGO = MyGame::Instance->CreateGameObjectInstance();
	orangeGhostGO->tag = TagManager::Ghost;

	OrangeGhost* orangeGhost = orangeGhostGO->AddComponent<OrangeGhost>();
	enemies.push_back(orangeGhost);


	for (Enemy* enemy : enemies)
		enemy->SetActive(false);
}

void GameManager::OnEvent(const PlayerHitEvent& event, const PlayerHitEventDispatcher& sender)
{
	if (this->gs != GameState::Play)
		return;

	if (lives == 1)
	{
		GameOver();
		return;
	}

	death->Play();
	lives--;
	LivesUpdateEvent livesUpdateEvent;
	livesUpdateEvent.lives = lives;
	LivesUpdateEventDispatcher::Invoke(livesUpdateEvent);

	Reset();
}

void GameManager::OnEvent(const PelletCollectedEvent& event, const PelletCollectedEventDispatcher& sender)
{
	if(gs == GameState::Play)
		chomp->Play();

	pelletsOnMap--;
	AddPoints(10);

	if (pelletsOnMap == 0)
		Win();
}

void GameManager::OnEvent(const BigPelletCollectedEvent& event, const BigPelletCollectedEventDispatcher& sender)
{
	bigChomp->Play();
	pelletsOnMap--;
	streak = 1;
	AddPoints(50);

	if (pelletsOnMap == 0)
		Win();
}

void GameManager::OnEvent(const GhostKilledEvent& event, const GhostKilledEventDispatcher& sender)
{
	ghostKill->Play();
	AddPoints(200 * streak);
	streak++;
	stopTimer = 0.0f;
	hitStop = true;
}

void GameManager::Awake()
{
	this->SetDuration(3.0f);
}

void GameManager::Start()
{
	introSound->Play();
	InitMap();
	InitMapOBJs();

	Reset();

	InitUI();
}

void GameManager::SetDuration(const float _duration)
{
	this->duration = _duration;
}

void GameManager::_Update(const float& dt)
{
	timer += dt;
	stopTimer += dt;

	HitStop();

	if (timer >= duration)
	{
		timer = 0.0f;
		switch (this->gs)
		{
			case GameState::Pause:
			{
				this->gs = GameState::Play;

				playerController->SetActive(true);
				int timerIndex = 0;
				for (Enemy* enemy : enemies)
				{
					enemy->SetNewDuration(5.0f * timerIndex + 1.0f);
					enemy->SetActive(true);
					timerIndex++;
					if(readyTextGO != nullptr)
						MyGame::Instance->DestroyGameObject(readyTextGO);
				}
			}
			break;
		}
	}

	fps = std::to_string((int) (1/ dt));
	fpsValue->SetText(fps);
	fpsTextGO->SetActive(MyGame::Instance->ShowFPS());
	fpsValue->SetActive(MyGame::Instance->ShowFPS());
}

void GameManager::HitStop()
{
	if (gs == GameState::Pause)
		return;

	if (!hitStop)
		return;

	if (stopTimer <= 0.5f)
	{
		playerController->SetActive(false);
		for (Enemy* enemy : enemies)
			enemy->GetGameObject()->GetComponent<Movement>()->SetSpeed(0.0f);
	}
	else
	{
		playerController->SetActive(true);
		for (Enemy* enemy : enemies)
		{
			if(enemy->GetState() == EnemyState::Flee)
				enemy->GetGameObject()->GetComponent<Movement>()->SetSpeed(0.5f);
			else
				enemy->GetGameObject()->GetComponent<Movement>()->SetSpeed(enemy->GetGameObject()->GetComponent<Movement>()->GetOriginSpeed());
		}

		hitStop = false;
	}
}

PathmapTile* GameManager::GetMap() const
{
	return this->map;
}