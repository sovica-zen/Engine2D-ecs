#pragma once

#include <SFML/Graphics.hpp>
#include "Assets.h"
#include "Action.h"
#include "Physics.h"

constexpr auto SCR_WIDTH = 320*2;
constexpr auto SCR_HEIGHT = 224*2;

class Scene;

class GameEngine {
	bool m_running = true;
	std::map<std::string, std::shared_ptr<Scene>> m_scenes;
	sf::RenderWindow m_window;	
	std::string m_current_scene;
	Assets m_assets;
	
	std::shared_ptr<Scene> currentScene();
	void update();
	void fpsCounter();

public:
	void run();
	void init();

	sf::RenderWindow& window();
	Assets& getAssets();
	void setCurrentScene(std::string s);
};