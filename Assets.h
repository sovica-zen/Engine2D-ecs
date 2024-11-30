#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include <memory>

class Assets {
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, Animation> animations;
	std::map<std::string, sf::Sound> sounds;
	std::map<std::string, sf::SoundBuffer> buffers;
	std::map<std::string, sf::Font> fonts;

public:
	void addTexture(std::string name, std::string path);
	void addAnimation(std::string name, Animation animation);
	void addSound(std::string name, std::string path);
	void addFont(std::string name, std::string path);

	sf::Texture& getTexture(std::string name);
	Animation& getAnimation(std::string name);
	sf::Sound& getSound(std::string name);
	sf::Font& getFont(std::string name);
	sf::SoundBuffer& getBuffer(std::string name);
	void addBuffer(std::string name, std::string path);
};