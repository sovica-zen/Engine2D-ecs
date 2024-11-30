#include "Entity.h"

Entity::Entity(const std::string& tag, size_t id) : m_tag(tag), m_id(id) {}

bool Entity::isActive() const {
	return m_alive;
}

const size_t Entity::id() const {
	return m_id;
}

const std::string& Entity::tag() const {
	return m_tag;
}

void Entity::destroy() {
	m_alive = false;
}
