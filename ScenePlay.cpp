#include "ScenePlay.h"
#include "GameEngine.h"
#include <iostream>
#include <fstream>


ScenePlay::ScenePlay() {}

ScenePlay::ScenePlay(GameEngine* gameEngine) {
	m_game = gameEngine;
	init();
}

void ScenePlay::update() {
	sMovement();
	sAnimation();
	sCollision();
	sCamera();
	sHitbox();
	sInvuln();
	m_entities.update();
}

void ScenePlay::init() {
	registerAction(sf::Keyboard::A, "LEFT");
	registerAction(sf::Keyboard::S, "DOWN");
	registerAction(sf::Keyboard::W, "UP");
	registerAction(sf::Keyboard::D, "RIGHT");
	registerAction(sf::Keyboard::Space, "ATTACK");
	registerAction(sf::Keyboard::Escape, "EXIT");
	registerAction(sf::Keyboard::B, "DEBUG");
	
	m_player = makePlayer("player");


	// setup view
	m_view = sf::View(
		sf::Vector2f(SCR_WIDTH / 2.0, SCR_HEIGHT / 2.0), sf::Vector2f(SCR_WIDTH, SCR_HEIGHT)
	);
	m_view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	m_game->window().setView(m_view);

}

std::shared_ptr<Entity> ScenePlay::makePlayer(std::string tag) {
	auto e = m_entities.addEntity(tag);
	e->addComponent<CTransform>();
	e->addComponent<CHitbox>();
	return e;
}	

//systems
void ScenePlay::sRender() {
	m_game->window().clear(sf::Color(0x0F0F0F));
	sf::RectangleShape bg = sf::RectangleShape(sf::Vector2f(1920, 1080));

	if (debug) {
		DebugRect();
		debugCenter();
	}

	healthBar();

	for (auto &e : m_entities.getEntities()) {
		if (e->hasComponent<CAnimation>()) {
			auto& sprite = e->getComponent<CAnimation>().animation.getSprite();
			vec2 pos = e->getComponent<CTransform>().pos;
			sprite.setPosition(pos.x, pos.y);
			m_game->window().draw(sprite);
		}
	}
}

void ScenePlay::sAnimation() {
	
}

void ScenePlay::sMovement() {
	for (auto& e : m_entities.getEntities()) {
		if (e->hasComponent<CGravity>()) {
			float accel = e->getComponent<CGravity>().accel;
			e->getComponent<CTransform>().velocity.y += accel;
		}

		if (e->hasComponent<CTransform>()) {
			vec2 vel = e->getComponent<CTransform>().velocity;
			e->getComponent<CTransform>().previous_pos = e->getComponent<CTransform>().pos;
			e->getComponent<CTransform>().previous_velocity = e->getComponent<CTransform>().velocity;
			e->getComponent<CTransform>().pos += vel;
		}
	}
	friction();
}

void ScenePlay::sCollision() {
	characterCollision(m_enemy);
	characterCollision(m_player);
	
}

void ScenePlay::DebugRect() {
	for (auto& e : m_entities.getEntities()) {
		if (e->hasComponent<CBBox>() && e->hasComponent<CTransform>()) {

			vec2 size = e->getComponent<CBBox>().size;
			vec2 pos = e->getComponent<CTransform>().pos;
			auto rec = sf::RectangleShape(sf::Vector2f(size.x,size.y));
			rec.setFillColor(sf::Color::Transparent);
			rec.setOutlineColor(sf::Color::Green);
			if (e->tag() == "floor"){ rec.setOutlineColor(sf::Color::Magenta); }
			if (e->tag() == "attack") { rec.setOutlineColor(sf::Color::Red); }
			rec.setOutlineThickness(1);
			rec.setOrigin(size.x/2, size.y/2);
			rec.setPosition(pos.x, pos.y);
			m_game->window().draw(rec);
		}
	}
}

void ScenePlay::debugCenter() {
	for (auto& e : m_entities.getEntities()) {
		if (e->hasComponent<CBBox>() && e->hasComponent<CTransform>()) {

			vec2 sizey = vec2(2, 10000);
			vec2 pos = vec2(SCR_WIDTH, SCR_HEIGHT);
			auto rec = sf::RectangleShape(sf::Vector2f(sizey.x, sizey.y));
			rec.setFillColor(sf::Color::White);
			rec.setOrigin(sizey.x / 2, sizey.y / 2);
			rec.setPosition(pos.x, pos.y);
			m_game->window().draw(rec);
		}
	}
}

void ScenePlay::sDoAction(const Action& action) {
	if (action.type() == "START") {
		if (action.name() == "DOWN") {
			m_player->getComponent<CState>().state = "crouch";
			//m_player->getComponent<CTransform>().velocity.y = player_speed;
		}
		else if (action.name() == "LEFT") {
			m_player->getComponent<CTransform>().velocity.x = -player_speed;
			m_player->getComponent<CTransform>().orientation = -1;
		}
		else if (action.name() == "RIGHT") {
			m_player->getComponent<CTransform>().velocity.x = player_speed;
			m_player->getComponent<CTransform>().orientation = 1;
		}
		else if (action.name() == "UP") {
			if (m_player->getComponent<CState>().state != "jump") {
				m_player->getComponent<CState>().state = "jump";
				m_player->getComponent<CTransform>().velocity.y = -20;
			}
		}
		else if (action.name() == "ATTACK") {
			std::cout << " attack ";
		}
	}

	if (action.type() == "END") {
		if (action.name() == "DOWN") {
			m_player->getComponent<CTransform>().velocity.y = 0;
		}
		else if (action.name() == "LEFT") {
			m_player->getComponent<CTransform>().velocity.x = 0;
		}
		else if (action.name() == "RIGHT") {
			m_player->getComponent<CTransform>().velocity.x = 0;
		}
		else if (action.name() == "UP") {
			m_player->getComponent<CState>().state = "stand";
			//m_player->getComponent<CTransform>().velocity.y = 0;
		}
		else if (action.name() == "ATTACK") {
			attack();
		}
		else if (action.name() == "EXIT") {
			std::cout << " exit ";
			m_game->window().setView(m_game->window().getDefaultView());
			m_game->setCurrentScene("menu");
		}
		else if (action.name() == "DEBUG") {
			debug = !debug;
		}
	}
}

void ScenePlay::makeFloor() {
	auto e = m_entities.addEntity("floor");
	e->addComponent<CTransform>(vec2(SCR_WIDTH/2.0, SCR_HEIGHT-50.0), vec2(0.0,0.0), 0.0);
	e->addComponent<CBBox>(2 * SCR_WIDTH, 100.0);
}

void ScenePlay::addTerrain(vec2 pos, vec2 size, sf::Texture& texture) {
	auto e = m_entities.addEntity("floor");
	e->addComponent<CTransform>(pos, vec2(0.0, 0.0), 0.0);
	e->addComponent<CBBox>(size.x, size.y);
	e->addComponent<CAnimation>(1, 1, texture);
	vec2 texturesize = vec2(texture.getSize().x, texture.getSize().y);
	e->getComponent<CAnimation>().animation.getSprite().setScale(
		size.x / texturesize.x, 
		size.y / texturesize.y
	);
}

void ScenePlay::sCamera() {
	sf::Vector2f cam_center = m_view.getCenter();
	vec2 player = m_player->getComponent<CTransform>().pos;

	// centered on player.x
	//sf::View centered = sf::View(
	//	sf::Vector2f(SCR_WIDTH / 2.0, SCR_HEIGHT / 2.0), sf::Vector2f(SCR_WIDTH, SCR_HEIGHT)
	//);;
	//centered.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	//centered.setCenter(sf::Vector2f(m_player->getComponent<CTransform>().pos.x, SCR_HEIGHT/2.0));

	// linearly catch up to player when leaving 100px box
	//sf::View linear = sf::View(
	//	sf::Vector2f(SCR_WIDTH / 2.0, SCR_HEIGHT / 2.0), sf::Vector2f(SCR_WIDTH, SCR_HEIGHT)
	//);;
	//float dist_squared = 
	//	(cam_center.x - player.x) * (cam_center.x - player.x) + 
	//	(cam_center.y - player.y) * (cam_center.y - player.y);
	//if (dist_squared > 100 * 100) {
	//	linear.setCenter(
	//		linear.getCenter() + 
	//		sf::Vector2f(0.03 * (-cam_center.x + player.x), 0.03 * (-cam_center.y + player.y))
	//	);
	//}

	//accelerate toward player
	float accel = (cam_center.x - player.x) * 0.05;
	camera_vel = accel;
	if (abs(cam_center.x - player.x) < 3) { camera_vel = 0; }
	
	m_view.setCenter(sf::Vector2f(m_view.getCenter().x - camera_vel, m_view.getCenter().y));

	m_game->window().setView(m_view);
}

void ScenePlay::attack() {
	auto attack = m_entities.addEntity("attack");
	vec2 offset = m_player->getComponent<CHitbox>().offset;
	vec2 hitBbox = m_player->getComponent<CHitbox>().size;
	vec2 playerpos = m_player->getComponent<CTransform>().pos;
	int orient = m_player->getComponent<CTransform>().orientation;
	attack->addComponent<CTransform>(
		vec2(playerpos.x + orient*offset.x, playerpos.y + offset.y), 
		vec2(0, 0), 
		0.0
	);
	attack->addComponent<CBBox>(hitBbox, false);
	attack->addComponent<CLifetime>(20);

	m_player->getComponent<CState>().state = "attack";
}

void ScenePlay::sHitbox() {
	for (auto e : m_entities.getEntities("attack")) {
		vec2 offset = vec2 (
			m_player->getComponent<CHitbox>().offset.x * m_player->getComponent<CTransform>().orientation,
			m_player->getComponent<CHitbox>().offset.y
		);
		e->getComponent<CTransform>().pos = m_player->getComponent<CTransform>().pos + offset;
		e->getComponent<CLifetime>().remaining--;
		if (e->getComponent<CLifetime>().remaining < 0) { 
			e->destroy(); 
			m_player->getComponent<CState>().state = "stand";
		}
	}
	hitboxCollision();
}

void ScenePlay::hitboxCollision() {
	for (auto e : m_entities.getEntities("enemy")) {
		if (e->getComponent<CInvuln>().is_invuln) continue;

		for (auto h : m_entities.getEntities("attack")) {
			if (Physics::isCollision(e, h)) {
				if (!e->getComponent<CInvuln>().is_invuln) {
					e->getComponent<CHp>().remaining -= 13;
					e->getComponent<CInvuln>().is_invuln = true;
					e->getComponent<CInvuln>().remaining = 45;
					
					knockBack();
				}
			}
		}
	}
}
	
void ScenePlay::characterCollision(std::shared_ptr<Entity> character) {
	std::string tag = character->tag();
	auto& charTransform = character->getComponent<CTransform>();
	
	for (auto& e : m_entities.getEntities()) {
		auto& eTransform = e->getComponent<CTransform>();

		if (e->tag() == tag || !e->getComponent<CBBox>().collision) continue;
		vec2 overlap = Physics::getOverlap(character, e);
		if (Physics::isCollision(character, e)) {
			vec2 prevOverlap = Physics::getPrevOverlap(character, e);
			if (charTransform.pos.y < eTransform.pos.y && prevOverlap.y <= 0) {
				charTransform.velocity.y = 0;
				charTransform.pos.y -= overlap.y + 0.01;
				if (tag=="enemy") friction();
			}
			else if (charTransform.pos.y > eTransform.pos.y && prevOverlap.y <= 0) {
				charTransform.velocity.y = 0;
				charTransform.pos.y += overlap.y + 0.01;
			}
			else if (charTransform.pos.x < eTransform.pos.x && prevOverlap.x <= 0) {
				charTransform.velocity.x = 0;
				charTransform.pos.x -= overlap.x + 0.001;
			}
			else if (charTransform.pos.x > eTransform.pos.x && prevOverlap.x <= 0) {
				charTransform.velocity.x = 0;
				charTransform.pos.x += overlap.x + 0.001;
			}
		}
	}
}

void ScenePlay::sInvuln() {
	for (auto e : m_entities.getEntities()) {
		if (!e->hasComponent<CInvuln>() || !e->hasComponent<CAnimation>()) continue;

		auto& inv = e->getComponent<CInvuln>();
		if (inv.is_invuln) {
			e->getComponent<CAnimation>().animation.getSprite().setColor(sf::Color::Red);
			inv.remaining--;
		}

		if (inv.remaining < 0) {
			e->getComponent<CAnimation>().animation.getSprite().setColor(sf::Color::White);
			inv.is_invuln = false;
			inv.remaining = INT_MAX;
		}
	}
}

void ScenePlay::knockBack() {
	auto& transform = m_enemy->getComponent<CTransform>();
	float x_delta = transform.pos.x - m_player->getComponent<CTransform>().pos.x;
	float dir = (x_delta > 0.0) ? 1.0 : -1.0;
	transform.velocity = vec2(dir*10,-6);
	m_game->getAssets().getSound("punch").play();

}

void ScenePlay::friction() {
		auto& transform = m_enemy->getComponent<CTransform>();
		float dir = transform.velocity.x > 0 ? 1.0 : -1.0;
		transform.velocity.x /= 1.1;
}

void ScenePlay::healthBar() {
	for (auto e : m_entities.getEntities()) {
		if (!e->hasComponent<CHp>()) continue;

		auto& hp = e->getComponent<CHp>();
		float ratio = hp.remaining / hp.total;

		if (ratio < 0) continue;
		
		vec2 size = vec2(60,10);
		vec2 pos = e->getComponent<CTransform>().pos;
		auto rec = sf::RectangleShape(sf::Vector2f(size.x, size.y));
		rec.setFillColor(sf::Color::Color(255,0,0,200));
		rec.setOrigin(size.x / 2, size.y / 2);
		rec.setPosition(pos.x, pos.y- 140);
		m_game->window().draw(rec);

		size = vec2(ratio*60, 10);
		rec = sf::RectangleShape(sf::Vector2f(size.x, size.y));
		rec.setFillColor(sf::Color::Color(0, 255, 0, 255));
		rec.setOrigin(size.x / 2, size.y / 2);
		rec.setPosition(pos.x, pos.y- 140);
		m_game->window().draw(rec);
	}
}

