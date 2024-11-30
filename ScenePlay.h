#pragma once
#include "Scene.h"

class ScenePlay : public Scene {

private:
	std::shared_ptr<Entity> m_player;
	std::shared_ptr<Entity> m_enemy;
	int player_speed = 7;
	float gravity = 0.70;
	float camera_vel = 0;

	sf::View m_view;

	void sDoAction(const Action& action);
	void sAnimation();
	void sMovement();
	void sCollision();
	void sCamera();
	void sHitbox();
	void sInvuln();
	
	void DebugRect();
	void debugCenter();
	void makeFloor();
	void addTerrain(vec2 pos, vec2 size, sf::Texture& texture);
	void characterCollision(std::shared_ptr<Entity> character);
	void knockBack();
	void friction();
	void healthBar();
	void hitboxCollision();
	void attack();
	void init();
	std::shared_ptr<Entity> makePlayer(std::string tag);

public:
	ScenePlay();
	ScenePlay(GameEngine* gameEngine);

	bool debug = true;

	void update();
	void sRender();
	

};

