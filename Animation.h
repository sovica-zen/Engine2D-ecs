#pragma once
#include <SFML/Graphics.hpp>
#include "vec2.h"

class Animation {
	sf::Sprite sprite;
	size_t speed = 30;
	size_t current_frame = 0;
	size_t keyframes = 1;
	vec2 size = vec2(100, 100);
	int scale = 1;
	bool has_ended = false;

public:
	Animation();
	Animation(size_t speed, size_t duration, sf::Texture& texture);
	Animation(sf::Texture& texture);

	void update();
	sf::Sprite& getSprite();
	int getScale();
	void setScale(int s);
	size_t getSpeed();
	size_t getKeyframes();
	void end();
	bool isEnded();
	void setOrientation(int orientation);
};