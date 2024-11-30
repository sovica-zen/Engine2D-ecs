#pragma once
#include "Scene.h"

class SceneMenu : public Scene {
	std::vector<std::shared_ptr<Entity>> menu_items = {};
	size_t current_menu_item = 1;

public:
	SceneMenu();
	SceneMenu(GameEngine* gameEngine);
	void update();
	void sDoAction(const Action& action);
	void sRender();
	void init();
};