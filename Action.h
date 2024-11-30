#pragma once

class Action {
	std::string m_name = "default";
	std::string m_type = "START";

public:
	std::string name() const { return m_name; }
	std::string type() const { return m_type; }
	std::string toString() {
		return m_name + " " + m_type;
	}

	Action() {}
	Action(std::string name, std::string type): m_name(name), m_type(type) {}
};