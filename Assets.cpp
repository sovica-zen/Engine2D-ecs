#include "Assets.h"
#include <iostream>

void Assets::addTexture(std::string name, std::string path) {
	textures[name] = sf::Texture();
	textures[name].loadFromFile(path);
}

void Assets::addAnimation(std::string name, Animation animation) {
	animations[name] = animation;
}

void Assets::addSound(std::string name, std::string path) {
	sounds[name] = sf::Sound();
	sounds[name].setBuffer(buffers[name]);
	sounds[name].setVolume(50);	
}

void Assets::addFont(std::string name, std::string path) {
	fonts[name] = sf::Font();
	fonts[name].loadFromFile(path);
}


sf::Texture& Assets::getTexture(std::string name) {
	return textures[name];
}

Animation& Assets::getAnimation(std::string name) {
	return animations[name];
}

sf::Sound& Assets::getSound(std::string name) {
	return sounds[name];
}

sf::Font& Assets::getFont(std::string name) {
	return fonts[name];
}

sf::SoundBuffer& Assets::getBuffer(std::string name) {
	return buffers[name];
}

void Assets::addBuffer(std::string name, std::string path) {
	buffers[name] = sf::SoundBuffer();
	buffers[name].loadFromFile(path);
}
