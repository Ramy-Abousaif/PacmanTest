#include "MyGame.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "SDL.h"
#include "GameManager.h"

MyGame* MyGame::Instance = nullptr;

MyGame::MyGame(Drawer* drawer)
{
	this->Instance = this;
	this->input = Vector2f(1.0f, 0.0f);
	this->drawer = drawer;
}

MyGame::~MyGame()
{
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
	//Initialize Game Manager
	GameObject* gameManagerGO = CreateGameObjectInstance();
	gameManagerGO->tag = TagManager::Manager;
	GameManager* gameManager = gameManagerGO->AddComponent<GameManager>();
}

bool MyGame::UpdateInput()
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_ESCAPE])
		return false;

	if (keystate[SDL_SCANCODE_Q])
		toggleFPS = !toggleFPS;

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

bool MyGame::ShowFPS()
{
	return toggleFPS;
}

Vector2f MyGame::TakeInput() const
{
	return input;
}

void MyGame::ResetInput()
{
	this->input = Vector2f(1, 0);
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

std::vector<GameObject*> MyGame::GetGameObjectsByTag(const TagManager& _tag)
{
	std::vector<GameObject*> result;
	for (GameObject* obj : gameObjects)
	{
		if (obj == nullptr)
			continue;

		if (obj->tag == _tag)
			result.push_back(obj);
	}
	return result;
}

std::vector<GameObject*> MyGame::GetAllGameObjects() const
{
	std::vector<GameObject*> output;
	for (GameObject* obj : gameObjects)
		output.push_back(obj);

	return output;
}

void MyGame::DestroyGameObject(GameObject* gameObject)
{
	if (gameObject == nullptr)
		return;

	for (GameObject* gameObjectToDestroy : gameObjectsToDestroy)
	{
		if (gameObjectToDestroy == gameObject)
			return;
	}
	gameObject->SetActive(false);
	gameObjectsToDestroy.push_back(gameObject);
}

bool MyGame::Update(const float dt)
{
	if (!UpdateInput())
		return false;

	for (GameObject* go : gameObjects)
		go->Update(dt);

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
