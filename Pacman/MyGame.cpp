#include "MyGame.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "SpriteRenderer.h"
#include "SDL.h"
#include "PlayerController.h"
#include "MapLoader.h"

MyGame::MyGame(Drawer* drawer)
{
	this->drawer = drawer;
}


MyGame::~MyGame()
{
	if (map != nullptr)
	{
		delete map;
		map = nullptr;
	}
}

void MyGame::Draw() const
{
	for (GameObject* go : gameObjects)
	{
		go->Draw();
	}
}

void MyGame::Start()
{
	GameObject* background = new GameObject();
	SpriteRenderer* spriteRenderer = background->AddComponent<SpriteRenderer>();
	spriteRenderer->SetDrawer(drawer);
	spriteRenderer->SetSprite("playfield.png");
	gameObjects.push_back(background);

	MapLoader mapLoader;
	map = mapLoader.Read("map.txt");

	for (int x = 0; x < map->GetSizeX(); ++x)
	{
		for (int y = 0; y < map->GetSizeY(); ++y)
		{
			const Tile& tile = map->GetTile(x, y);
			if (tile.type != TileType::BigDot && tile.type != TileType::Dot)
				continue;

			Vector2f pos{ (float)x , (float)y };
			pos /= 2;
			pos.X -= (((float)map->GetSizeX()) / 2.0f) / 2.0f;
			pos.Y -= (((float)map->GetSizeY()) / 2.0f) / 2.0f;
			pos.X += 0.75f;
			pos.Y += 0.25f;

			GameObject* smallDotObject = new GameObject(pos);
			SpriteRenderer* spriteRenderer = smallDotObject->AddComponent<SpriteRenderer>();
			spriteRenderer->SetDrawer(drawer);

			if (tile.type == TileType::Dot)
				spriteRenderer->SetSprite("Small_Dot_32.png");
			else
				spriteRenderer->SetSprite("Big_Dot_32.png");

			gameObjects.push_back(smallDotObject);
		}
	}

	GameObject* playerObject = new GameObject(Vector2f(0.0f, 0.5f));
	SpriteRenderer* spriteRenderer = playerObject->AddComponent<SpriteRenderer>();
	spriteRenderer->SetDrawer(drawer);
	spriteRenderer->SetSprite("open_32.png");
	PlayerController* playerController = playerObject->AddComponent<PlayerController>();
	playerController->SetGameInstance(this);
	playerController->SetPlayerSpeed(10.0f);
	gameObjects.push_back(playerObject);
}

void MyGame::UpdateInput()
{
	input = Vector2f(0, 0);
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_ESCAPE])
		return;

	if (keystate[SDL_SCANCODE_UP])
		input = Vector2f(0, 1);
	else if (keystate[SDL_SCANCODE_DOWN])
		input = Vector2f(0, -1);
	else if (keystate[SDL_SCANCODE_RIGHT])
		input = Vector2f(1, 0);
	else if (keystate[SDL_SCANCODE_LEFT])
		input = Vector2f(-1, 0);
}

Vector2f MyGame::TakeInput() const
{
	return input;
}

void MyGame::Update(const float dt)
{
	for (GameObject* go : gameObjects)
	{
		go->Update(dt);
	}
}
