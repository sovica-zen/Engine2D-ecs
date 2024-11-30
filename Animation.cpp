#include "Animation.h"

Animation::Animation(sf::Texture& texture) {
	auto texsize = texture.getSize();
	int y = size.y;
	int x = size.x / keyframes;
	
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(x, y)));
	sprite.setOrigin(x / 2.0, y / 2.0);
	sprite.scale(scale, scale);
}

Animation::Animation(size_t speed, size_t keyframes, sf::Texture& texture)
	: speed(speed), keyframes(keyframes) {
	auto texsize = texture.getSize();
	int y = texsize.y;
	int x = texsize.x / keyframes;
	size.x = x;
	size.y = y;
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(x, y)));
	sprite.setOrigin(x / 2.0, y / 2.0);
	sprite.scale(scale,scale);
}

Animation::Animation(){}

void Animation::update() {
	current_frame++;
	int currentKeyframe = (current_frame / speed) % keyframes;
	sprite.setTextureRect(sf::IntRect(
		sf::Vector2i(currentKeyframe*size.x, 0), sf::Vector2i(size.x, size.y)                      
	));
}

sf::Sprite& Animation::getSprite() {
	return sprite;
}

int Animation::getScale() {
	return scale;
}

void Animation::setScale(int s) {
	scale = s;
}

void Animation::end() {
	 has_ended = true;
}

bool Animation::isEnded() {
	return has_ended;
}

void Animation::setOrientation(int orientation){
	sprite.setScale(orientation * scale, scale);
}
