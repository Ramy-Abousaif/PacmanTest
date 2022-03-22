#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "BaseComponent.h"
#include "Event.h"
#include "GameObject.h"

class PlayerController;
class Enemy;
class PathmapTile;
class TextUI;

enum class GameState : short
{
	Play,
	Pause,
	GameOver
};

class GameManager : public BaseComponent, PlayerHitEventListener, PelletCollectedEventListener, BigPelletCollectedEventListener, GhostKilledEventListener, LivesUpdateEventDispatcher, PointsCollectedEventDispatcher
{
protected:
	void _Update(const float& dt) override;

private:
	GameState gs = GameState::Pause;
	PathmapTile* map = nullptr;
	float timer = 0.0f;
	float stopTimer = 0.0f;
	bool hitStop = false;
	float duration = 1.0f;
	std::string fps = "0";
	GameObject* readyTextGO;
	GameObject* fpsTextGO;
	TextUI* fpsValue;
	unsigned short lives = 3;
	unsigned int points = 0;
	unsigned int pelletsOnMap = 0;
	unsigned int streak = 1;

	PlayerController* playerController = nullptr;
	std::vector<Enemy*> enemies;

	void InitUI();
	void InitMap();
	void InitMapOBJs();
	void InitPlayer();
	void InitGhosts();

	void GameOver();
	void Win();
	void Reset();
	void HitStop();
	void AddPoints(const unsigned int _points);

public:
	GameManager();
	~GameManager() override;
	void Awake() override;
	void Start() override;
	void SetDuration(const float _duration);
	PathmapTile* GetMap() const;

	void OnEvent(const PlayerHitEvent& event, const PlayerHitEventDispatcher& sender) override;
	void OnEvent(const PelletCollectedEvent& event, const PelletCollectedEventDispatcher& sender) override;
	void OnEvent(const BigPelletCollectedEvent& event, const BigPelletCollectedEventDispatcher& sender) override;
	void OnEvent(const GhostKilledEvent& event, const GhostKilledEventDispatcher& sender) override;
	void Assign(LivesUpdateEventListener* listener) { LivesUpdateEventDispatcher::Assign(listener); }
	void Unassign(LivesUpdateEventListener* listener) { LivesUpdateEventDispatcher::Unassign(listener); }
	void Assign(PointsCollectedEventListener* listener) { PointsCollectedEventDispatcher::Assign(listener); }
	void Unassign(PointsCollectedEventListener* listener) { PointsCollectedEventDispatcher::Unassign(listener); }
};
#endif
