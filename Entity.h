#pragma once
#include <string>
#include <memory>
#include "Components.h"

typedef std::tuple<
	CTransform,
	CBBox,
	CInput,
	CState,
	CAnimation,
	CGravity,
	CText,
	CHitbox,
	CLifetime,
	CInvuln,
	CHp,
	CDecorative
> ComponentTuple;

class Entity {
	const size_t m_id = 0;
	std::string m_tag = "default";
	bool m_alive = true;

	ComponentTuple m_components;

public:

	Entity(const std::string& tag, size_t id);

	bool isActive() const;
	const size_t id() const;
	const std::string& tag() const;
	void destroy();


	template<typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {
		auto& component = getComponent<T>();
		component = T(std::forward<TArgs>(mArgs)...);
		component.has = true;
		return component;
	}

	template<typename T>
	T& getComponent() {
		return std::get<T>(m_components);
	}

	template<typename T>
	const T& getComponent() const {
		return std::get<T>(m_components);
	}

	template<typename T>
	bool hasComponent() const {
		return getComponent<T>().has;
	}

	template<typename T>
	void removeComponent() {
		getComponent<T>() = T();
	}

};


