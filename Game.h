#pragma once
#include "EntityManager.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>

struct PlayerConfig { int SR, CR, FR; };
struct EnemyConfig { int SR, CR, FR; };
struct BulletConfig { int SR, CR, FR; };

constexpr auto SCR_WIDTH = 1920;
constexpr auto SCR_HEIGHT = 1080;


class Game {
public:
	sf::RenderWindow m_window;
	EntityManager m_entities;
	sf::Font m_font;
	sf::Text m_text;
	PlayerConfig m_playerConfig;
	EnemyConfig m_enemyConfig;
	BulletConfig m_bulletConfig;
	size_t m_score = 0;
	size_t m_currentFrame = 0;
	size_t m_lastFrameFired = 0;
	size_t mLastEnemySpawnTime = 0;
	bool m_paused = false;
	bool m_running = true;

	std::shared_ptr<Entity> m_player;

	void init(const std::string& config);
	void setPaused(bool paused);

	void sUserInput();

	void sMovement();
	void sLifespan();
	//void sRender();
	void sEnemySpawner();
	void sBulletSpawner();
	void sCollision();
	void spawnPlayer();
	void spawnEnemy();
	void spawnSmall(std::shared_ptr<Entity>& original);
	void spawnBullet();
	void spawnSpecial();

	void run();


	Game();
	Game(const std::string& config);

};

