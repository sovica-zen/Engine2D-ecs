#include "SceneMenu.h"
#include "GameEngine.h"

#include <iostream>

SceneMenu::SceneMenu() {}

SceneMenu::SceneMenu(GameEngine* gameEngine) { 
	m_game = gameEngine;
	init();
}

void SceneMenu::update() {
	m_current_frame++;
	m_entities.update();
}

void SceneMenu::sRender() {
	m_game->window().clear(sf::Color(0x0F0F0F));
	for (auto e : m_entities.getEntities()) {
		if (e->hasComponent<CText>() && e->hasComponent<CTransform>()) {
			vec2 pos = e->getComponent<CTransform>().pos;
			sf::Text& t = e->getComponent<CText>().text;
			t.setPosition(sf::Vector2f(pos.x, pos.y));
			t.setFillColor(sf::Color::White);
			if (menu_items[current_menu_item] == e) {
				t.setFillColor(sf::Color::Red);
			}
			m_game->window().draw(t);
		}
	}
}

void SceneMenu::init() {
	registerAction(sf::Keyboard::S, "DOWN");
	registerAction(sf::Keyboard::W, "UP");
	registerAction(sf::Keyboard::Space, "SPACE");
	registerAction(sf::Keyboard::Enter, "ENTER");
	registerAction(sf::Keyboard::Escape, "EXIT");

	auto e = m_entities.addEntity("menu_item_1");
	e->addComponent<CText>("level 1", m_game->getAssets().getFont("arial"));
	e->addComponent<CTransform>(vec2(200, 200), vec2(0, 0), 0);
	e->addComponent<CBBox>(vec2(500,50));
	menu_items.push_back(e);

	auto f = m_entities.addEntity("menu_item_2");
	f->addComponent<CText>("level 2", m_game->getAssets().getFont("arial"));
	f->addComponent<CTransform>(vec2(200, 400), vec2(0,0), 0);
	f->addComponent<CBBox>(vec2(500, 50));
	menu_items.push_back(f);

	auto g = m_entities.addEntity("menu_item_3");
	g->addComponent<CText>("level 3", m_game->getAssets().getFont("arial"));
	g->addComponent<CTransform>(vec2(200, 600), vec2(0,0), 0);
	g->addComponent<CBBox>(vec2(500, 50));
	menu_items.push_back(g);

	m_game->window().setView(m_game->window().getDefaultView());
}

void SceneMenu::sDoAction(const Action& action) {
	if (action.type() == "START") {
	}

	if (action.type() == "END") {
		if (action.name() == "DOWN") {
			current_menu_item = (current_menu_item + 1 + menu_items.size()) % menu_items.size();
		}
		else if (action.name() == "UP") {
			current_menu_item = (current_menu_item - 1 + menu_items.size()) % menu_items.size();
		}
		else if (action.name() == "ENTER" || action.name() == "SPACE") {
			if (menu_items[current_menu_item]->getComponent<CText>().raw_text == "level 3") {
				m_game->setCurrentScene("level3");
			}
		}
		else if (action.name() == "EXIT") {
			m_game->window().close();
		}
	}
}

void makeMenu(std::vector<std::string>) {
	//adds each menu component with automatic spacing and other things
}
