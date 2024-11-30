#include "Scene.h"
#include "GameEngine.h"

Scene::Scene(){}
Scene::Scene(GameEngine* gameEngine) {}

// calls derived scene's update() a bunch of times
void Scene::simulate(size_t frame) {
	update();
}

void Scene::doAction(const Action& action) {
	// save to replay file for example 
	// idk
	sDoAction(action);
}

void Scene::registerAction(int inputKey, const std::string& actionName) {
	m_actionMap[inputKey] = actionName;
}

ActionMap& Scene::getActionMap() {
	return m_actionMap;
}

