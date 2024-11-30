#pragma once
#include "EntityManager.h"
#include <SFML/Graphics.hpp>
#include "Action.h"


typedef std::map<int, std::string> ActionMap;

class GameEngine;

class Scene {
protected:
	GameEngine * m_game = nullptr;
	EntityManager m_entities;
	ActionMap m_actionMap;

	int m_current_frame = 0;
	bool m_paused = false;
	bool m_has_ended = false;

public:
	
	Scene();
	Scene(GameEngine* gameEngine);

	virtual void update() = 0;
	virtual void sDoAction(const Action & action) = 0;
	virtual void sRender() = 0;

	void simulate(const size_t n);
	void doAction(const Action & action); 
	void registerAction(int inputKey, const std::string& actionName);

	ActionMap& getActionMap();
};