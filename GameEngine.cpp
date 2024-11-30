#include "GameEngine.h"
#include "Scene.h"
#include "ScenePlay.h"
#include "SceneMenu.h"
#include <memory>
#include <iostream>
#include <fstream>


void GameEngine::run() {
	m_window.create(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "gaming");
	m_window.setFramerateLimit(60);
	sf::Event event;
	
		
	while (m_window.isOpen()) {
		while (m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				m_window.close();
			}

			// look for key releases
			if (event.type == sf::Event::KeyReleased) {

				if (currentScene()->getActionMap().find(event.key.code) ==
					currentScene()->getActionMap().end()) 
				{ continue; }

				const std::string action_type = (event.type == sf::Event::KeyPressed) ? "START" : "END";

				currentScene()->doAction(
					Action(currentScene()->getActionMap().at(event.key.code), action_type)
				);
			}
		}

		// look for key downs/holds
		for (auto& a : currentScene()->getActionMap()) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode(a.first))) {
				currentScene()->doAction(Action(currentScene()->getActionMap().at(a.first), "START"));
			}
		}

		update();
		currentScene()->sRender();
		m_window.display();
	}
}

void GameEngine::init() {
	std::ifstream infile;
	std::string token, name, path, texturename;
	int speed, keyframes;
	infile.open("assets.txt", std::ios::in);

	while (infile >> token) {
		if (token == "ANIMATION") {
			infile >> name >> speed >> keyframes >> texturename;
			sf::Texture& texture = m_assets.getTexture(texturename);
			m_assets.addAnimation(name, Animation(speed, keyframes, texture));
		}
		else if (token == "TEXTURE") {
			infile >> name >> path;
			m_assets.addTexture(name, path);
		}
		else if (token == "SOUND") {
			infile >> name >> path;
			m_assets.addBuffer(name, path);
			m_assets.addSound(name, path);
		}
		else if (token == "FONT") {
			infile >> name >> path;
			m_assets.addFont(name, path);
		}
	}

	std::shared_ptr<Scene> playScene = std::make_shared<ScenePlay>(this);
	std::shared_ptr<Scene> menuScene = std::make_shared<SceneMenu>(this);
	m_scenes["level3"] = playScene;
	m_scenes["menu"] = menuScene;
	m_current_scene = "level3";
}

void GameEngine::update() {
	currentScene()->update();
}

void GameEngine::fpsCounter() {
}

sf::RenderWindow& GameEngine::window() {
	return m_window;
}

Assets& GameEngine::getAssets() {
	return m_assets;
}

void GameEngine::setCurrentScene(std::string s) {
	m_current_scene = s;
}

std::shared_ptr<Scene> GameEngine::currentScene() {
	return m_scenes[m_current_scene];
}

