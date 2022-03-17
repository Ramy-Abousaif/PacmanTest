#include "MyGame.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "SpriteRenderer.h"
#include "SDL.h"
#include "PlayerController.h"
#include "MapLoader.h"
#include "Animator.h"
#include "PathPosition.h"
#include "Movement.h"
#include "Collision.h"
#include "Teleporter.h"
#include "Dot.h"
#include "Event.h"
#include "EventHandler.h"
#include "TextUI.h"
#include "PointsUI.h"

MyGame* MyGame::Instance = nullptr;

MyGame::MyGame(Drawer* drawer)
{
	this->Instance = this;
	this->input = Vector2f(-1.0f, 0.0f);
	this->drawer = drawer;
	this->map = nullptr;
}

MyGame::~MyGame()
{
	delete map;
	map = nullptr;

	for (unsigned int i = 0; i < gameObjects.size(); ++i)
		DestroyGameObject(gameObjects[i]);

	DestroyQueuedGameObjects();
}

void MyGame::Draw() const
{
	for (GameObject* go : gameObjects)
		go->Draw();
}

void MyGame::Start()
{
	//Initialize background gameobject
	GameObject* background = CreateGameObjectInstance();
	SpriteRenderer* spriteRenderer = background->AddComponent<SpriteRenderer>();
	spriteRenderer->SetDrawer(drawer);
	spriteRenderer->SetSprite("playfield.png");
	background->tag = TagManager::Background;

	//Read and load map
	MapLoader mapLoader;
	map = mapLoader.Read("map.txt");
	map->SetDistBetweenTiles(0.5f);

	//Initialize tilemap
	std::vector<GameObject*> tileObjects;
	Teleporter* firstTeleport = nullptr;
	Teleporter* previousTeleport = nullptr;

	for (unsigned int x = 0; x < map->GetSizeX(); ++x)
	{
		for (unsigned int y = 0; y < map->GetSizeY(); ++y)
		{
			const Tile& tile = map->GetTile(x, y);
			if (!tile.isWalkable)
				continue;

			GameObject* tileObject = CreateGameObjectInstance();
			PathPosition* pathPosition = tileObject->AddComponent<PathPosition>();
			pathPosition->SetPos(x, y);

			switch (tile.type)
			{
				case TileType::Teleport:
				{
					tileObject->tag = TagManager::Teleport;
					Teleporter* teleporter = tileObject->AddComponent<Teleporter>();
					if (firstTeleport == nullptr)
						firstTeleport = teleporter;
					else
						previousTeleport->SetOtherTP(teleporter);

					previousTeleport = teleporter;
				}
				break;
				case TileType::BigDot:
				{
					tileObject->tag = TagManager::BigDot;
					SpriteRenderer* spriteRenderer = tileObject->AddComponent<SpriteRenderer>();
					spriteRenderer->SetDrawer(drawer);
					spriteRenderer->SetSprite("Big_Dot_32.png");
					Dot* dot = tileObject->AddComponent<Dot>();
					dot->SetAddedPoints(50);
				}
				break;
				case TileType::Dot:
				{
					tileObject->tag = TagManager::Dot;
					SpriteRenderer* spriteRenderer = tileObject->AddComponent<SpriteRenderer>();
					spriteRenderer->SetDrawer(drawer);
					spriteRenderer->SetSprite("Small_Dot_32.png");
					Dot* dot = tileObject->AddComponent<Dot>();
					dot->SetAddedPoints(10);
				}
				break;
			}
			tileObjects.push_back(tileObject);
		}
	}

	if (firstTeleport != nullptr && previousTeleport != nullptr && firstTeleport != previousTeleport)
		previousTeleport->SetOtherTP(firstTeleport);

	//FPS UI
	GameObject* fpsTextGO = CreateGameObjectInstance();
	fpsTextGO->tag = TagManager::UI;
	TextUI* fpsText = fpsTextGO->AddComponent<TextUI>();
	fpsText->SetDrawer(drawer);
	fpsText->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	fpsText->SetPos(900, 50);
	fpsText->SetText("FPS: ");

	GameObject* fpsValueGO = CreateGameObjectInstance();
	fpsValueGO->tag = TagManager::UI;
	fpsValue = fpsValueGO->AddComponent<TextUI>();
	fpsValue->SetDrawer(drawer);
	fpsValue->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	fpsValue->SetPos(980, 50);
	fpsValue->SetText(fps);

	//Lives UI
	GameObject* livesTextGO = CreateGameObjectInstance();
	livesTextGO->tag = TagManager::UI;
	TextUI* livesText = livesTextGO->AddComponent<TextUI>();
	livesText->SetDrawer(drawer);
	livesText->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	livesText->SetPos(20, 90);
	livesText->SetText("Lives: ");

	GameObject* livesValueGO = CreateGameObjectInstance();
	livesValueGO->tag = TagManager::UI;
	TextUI* livesValueText = livesValueGO->AddComponent<TextUI>();
	livesValueText->SetDrawer(drawer);
	livesValueText->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	livesValueText->SetPos(110, 90);
	livesValueText->SetText("0");

	//Points UI
	PointsUI* pointsUI;
	GameObject* pointsTextGO = CreateGameObjectInstance();
	pointsTextGO->tag = TagManager::UI;
	TextUI* pointsText = pointsTextGO->AddComponent<TextUI>();
	pointsText->SetDrawer(drawer);
	pointsText->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	pointsText->SetPos(20, 50);
	pointsText->SetText("Score: ");

	GameObject* pointsValueGO = CreateGameObjectInstance();
	pointsValueGO->tag = TagManager::UI;
	TextUI* pointsValue = pointsValueGO->AddComponent<TextUI>();
	pointsValue->SetDrawer(drawer);
	pointsValue->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	pointsValue->SetPos(110, 50);
	pointsValue->SetText("0");
	pointsUI = pointsValueGO->AddComponent<PointsUI>();

	//Initialize player
	GameObject* player = CreateGameObjectInstance();
	player->tag = TagManager::Player;
	SpriteRenderer* sr = player->AddComponent<SpriteRenderer>();
	sr->SetDrawer(drawer);
	Animator* anim = player->AddComponent<Animator>();
	Animation idleAnim;
	idleAnim.name = "idle";
	idleAnim.sprites = { "open_32.png" , "closed_32.png" }, idleAnim.timeBetweenFrames = 0.25f;
	anim->AddAnimation(idleAnim);
	anim->SetCurrentAnimation("idle");
	PathPosition* pathPosition = player->AddComponent<PathPosition>();
	pathPosition->SetPos(13, 7);
	Movement* movement = player->AddComponent<Movement>();
	movement->SetDesiredPos(12, 7);
	PlayerController* pc = player->AddComponent<PlayerController>();
	pc->SetPlayerSpeed(4.0f);
	Collision* collision = player->AddComponent<Collision>();
	collision->Assign((CollisionEventListener*)pc);
	pc->Assign((PointsCollectedEventListener*)pointsUI);

	for (unsigned int i = 0; i < tileObjects.size(); ++i)
	{
		collision->AddOther(tileObjects[i]);
	}
}

bool MyGame::UpdateInput()
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_ESCAPE])
		return false;

	if (keystate[SDL_SCANCODE_UP])
		input = Vector2f(0, 1);
	else if (keystate[SDL_SCANCODE_DOWN])
		input = Vector2f(0, -1);
	else if (keystate[SDL_SCANCODE_RIGHT])
		input = Vector2f(1, 0);
	else if (keystate[SDL_SCANCODE_LEFT])
		input = Vector2f(-1, 0);

	return true;
}

Vector2f MyGame::TakeInput() const
{
	return input;
}

PathmapTile* MyGame::GetMap() const
{
	return map;
}

Drawer* MyGame::GetDrawer() const
{
	return drawer;
}

GameObject* MyGame::CreateGameObjectInstance(const Vector2f& pos)
{
	GameObject* gameObject = new GameObject(pos);
	gameObjects.push_back(gameObject);
	return gameObject;
}

void MyGame::DestroyGameObject(GameObject* gameObject)
{
	if (gameObject == nullptr)
		return;

	gameObject->SetActive(false);
	gameObjectsToDestroy.push_back(gameObject);
}

bool MyGame::Update(const float dt)
{
	if (!UpdateInput())
		return false;

	for (GameObject* go : gameObjects)
		go->Update(dt);

	fps = std::to_string((int)(1 / dt));
	fpsValue->SetText(fps);

	DestroyQueuedGameObjects();

	return true;
}

void MyGame::DestroyQueuedGameObjects()
{
	for (unsigned int i = 0; i < gameObjectsToDestroy.size(); ++i)
	{
		for (unsigned int j = 0; j < gameObjects.size(); ++j)
		{
			if (gameObjects[j] == gameObjectsToDestroy[i])
			{
				gameObjects.erase(gameObjects.begin() + j);
				break;
			}
		}

		delete gameObjectsToDestroy[i];
		gameObjectsToDestroy[i] = nullptr;
	}
	gameObjectsToDestroy.clear();
}
