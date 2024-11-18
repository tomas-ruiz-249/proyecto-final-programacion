#include <raylib.h>
#include <iostream>
#include <cmath>
#include "Player.h"
#include "TextureManager.h";

void Player::act(Map& map)
{
	if (isAlive()) {
		move(map);
		attack();
	}
	hurtTimer += GetFrameTime();
}

void Player::move(Map map)
{
	double cosAngle = cos(angle);
	double sinAngle = sin(angle);
	double speedPlayer = speed * GetFrameTime();
	Point2D d = { 0,0 };
	if (IsKeyDown(KEY_W)) {
		d.x += speedPlayer * cosAngle;
		d.y += speedPlayer * sinAngle;
	}
	if (IsKeyDown(KEY_S)) {
		d.x += -speedPlayer * cosAngle;
		d.y += -speedPlayer * sinAngle;
	}
	if (IsKeyDown(KEY_A)) {
		d.x += speedPlayer * sinAngle;
		d.y += -speedPlayer * cosAngle;
	}
	if (IsKeyDown(KEY_D)) {
		d.x += -speedPlayer * sinAngle;
		d.y += speedPlayer * cosAngle;
	}
	if (map.isPositionEmpty((int)(position.y + d.y), (int)position.x)) {
		position.y += d.y;
	}
	if (map.isPositionEmpty((int)position.y, (int)(position.x + d.x))) {
		position.x += d.x;
	}

	if (GetMouseDelta().x < 0) {
		angle -= rotationSpeed * GetFrameTime() * -GetMouseDelta().x;
	}
	if (GetMouseDelta().x > 0) {
		angle += rotationSpeed * GetFrameTime() * GetMouseDelta().x;
	}

	if (angle > PI * 2) {
		angle = 0;
	}
	if (angle < 0) {
		angle = PI * 2;
	}	
}

void Player::takeDamage(int damage)
{
	if (hurtTimer > 0.3) {
		health -= damage;
		hurtTimer = 0;
	}
}

void Player::attack()
{
	if ((IsMouseButtonDown(MOUSE_BUTTON_LEFT) or IsKeyDown(KEY_SPACE)) and weapon->canShoot()) {
		weapon->shoot();
		justShot = true;
	}
}

bool Player::heal(int healthPoints)
{
	if (health < maxHealth) {
		health += healthPoints;
		return true;
	}
	return false;
}


Player* Player::getInstance()
{
	if (!player) {
		player = new Player();
	}
	return player;
}

Player::Player()
{
	maxHealth = 100;
	hurtTimer = 0;
	health = maxHealth;
	position = { 20, 21 };
	speed = 5.0;
	rotationSpeed = 0.09f;
	angle = 0;
	weapon = new Weapon();
	justShot = false;


	//initialize weapon texture
	auto texMgr = TextureManager::getInstance();
	weapon->sprite = new Animated();
	weapon->sprite->animationIndex = 0;
	Texture staticTex = texMgr->getTexture("sprites\\static\\shotgun.png");
	weapon->sprite->tex = staticTex;
	weapon->sprite->textureArea = { 0, 0, (float)staticTex.width, (float)staticTex.height };
	weapon->sprite->positionOnWindow.width = staticTex.width;
	weapon->sprite->positionOnWindow.height = staticTex.height;
	//shooting animation
	Animation shooting = {};
	shooting.texture = texMgr->getTexture("sprites\\animated\\gun.png");
	shooting.numFrames = 11;
	shooting.animationSpeed = 5.0;
	shooting.textureArea = { 0, 0, (float)shooting.texture.width, (float)shooting.texture.height };
	shooting.positionOnWindow.width = (float)(shooting.texture.width / shooting.numFrames);
	shooting.positionOnWindow.height = (float)(shooting.texture.height);
	weapon->sprite->animations.push_back(shooting);
}

Player* Player::player = nullptr;
