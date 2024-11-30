#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "vec2.h"


class Component {
public:
	bool has = false;
};

class CTransform: public Component {
public:
	vec2 pos = { 0.0, 0.0 };
	vec2 velocity = { 0.0, 0.0 };
	float angle = 0.0;
	int orientation = 1;

	vec2 previous_pos = { 0.0, 0.0 };
	vec2 previous_velocity = { 0.0, 0.0 };
	float previous_angle = 0.0;

	CTransform(){}
	CTransform(const vec2 p, const vec2 v, float a)
		: pos(p), velocity(v), angle(a), previous_velocity(v), previous_pos(p), previous_angle(a) {}
};

class CInput: public Component {
public:
	bool up = false, left = false, right = false, down = false, click = false, space = false, pause = false;
	void setFalse() {
		up, left, right, down, click, space, pause = false;
	}

	CInput(){}
	
};

class CState : public Component {
public:
	std::string state = "default_state";
	CState(std::string state): state(state) {}
	CState(){}
};

class CBBox : public Component {
public:

	vec2 size = vec2(100, 100);
	vec2 half_size = vec2(50, 50);
	bool collision = true;

	CBBox() {}
	CBBox(float w, float h) : size(w, h), half_size(w / 2.0, h / 2.0) {}
	CBBox(vec2 v) : size(v.x, v.y), half_size(v.x / 2.0, v.y / 2.0) {}
	CBBox(vec2 v, bool col) : size(v.x, v.y), half_size(v.x / 2.0, v.y / 2.0), collision(col) {}
};

class CAnimation : public Component {
public:
	Animation animation;

	CAnimation(){}
	CAnimation(size_t speed, size_t keyframes, sf::Texture& texture) {
		animation = Animation(speed, keyframes, texture);
	}
	CAnimation(sf::Texture& texture) {
		animation = Animation(texture);
	}
	CAnimation(Animation anim) {
		animation = anim;
	}
};

class CGravity : public Component {
public:
	float accel = 0.0;

	CGravity(){}
	CGravity(float accel): accel(accel) {}
};


class CText : public Component {
public:
	std::string raw_text = "defaulttext";
	sf::Text text;

	CText() {}
	CText(const std::string& s, const sf::Font& font): raw_text(s) {
		text.setString(raw_text);
		text.setFont(font);
	}

};

class CHitbox : public Component {
public:
	vec2 offset;
	vec2 size;

	CHitbox() {}
	CHitbox(vec2 pos, vec2 size): offset(pos), size(size) {}

};

class CLifetime : public Component {
public:
	int total = 0;
	int remaining = 0;

	CLifetime(): total(INT_MAX), remaining(INT_MAX) {}
	CLifetime(int total) : total(total), remaining(total) {}
};

class CHp : public Component {
public:
	float total = 0;
	float remaining = 0;

	CHp() : total(INT_MAX), remaining(INT_MAX) {}
	CHp(int total) : total(total), remaining(total) {}
};

class CInvuln : public Component {
public:
	bool is_invuln = false;
	int duration = 0;
	int remaining = 0;

	CInvuln() : duration(INT_MAX), remaining(INT_MAX) {}
	CInvuln(int total) : duration(total), remaining(total), is_invuln(true) {}
};

class CDecorative : public Component {
public:

	CDecorative() {}
};