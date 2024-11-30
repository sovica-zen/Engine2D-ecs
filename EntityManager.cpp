#include "EntityManager.h"
#include <iostream>

EntityManager::EntityManager() {}

const EntityVec& EntityManager::getEntities() {
	return m_entities;
}

EntityVec& EntityManager::getEntities(const std::string& tag) {
	return m_entityMap[tag];
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag) {
	Entity new_entity = Entity(tag, m_totalEntities++);
	auto entity_ptr = std::make_shared<Entity>(new_entity);
	m_toAdd.push_back(entity_ptr);
	
	return entity_ptr;
}

void EntityManager::update() {
	for (auto e : m_toAdd) {
		m_entities.push_back(e);
		m_entityMap[e->tag()].push_back(e);
	}
	m_toAdd.clear();

	m_entities.erase(
		std::remove_if(
			m_entities.begin(),
			m_entities.end(),
			[](std::shared_ptr<Entity>& e) {return !e->isActive();}
		),
		m_entities.end()
	);
	
	std::for_each(
		m_entityMap.begin(), m_entityMap.end(),
		[](std::pair <const std::string, EntityVec>& p) {
			p.second.erase(
				std::remove_if(
					p.second.begin(),
					p.second.end(),
					[](std::shared_ptr<Entity>& e) {return !e->isActive();}
				),
				p.second.end()
			);
		}
	);
}

