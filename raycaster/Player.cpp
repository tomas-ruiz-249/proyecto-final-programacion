#include <raylib.h>
#include <iostream>
#include <cmath>
#include "Player.h"
#include "TextureManager.h";

void Player::move(Map& map)
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

Player::Player()
{
	position = { 2.1, 8 };
	speed = 5.0;
	rotationSpeed = 0.09f;
	angle = 0;
	weapon = new Weapon();

	//initialize weapon texture
	auto texMgr = TextureManager::getInstance();
	weapon->sprite->animationIndex = 0;
	weapon->sprite->tex = texMgr->getTexture("sprites\\static\\shotgun.png");
	Animation shooting = {};
	shooting.texture = texMgr->getTexture("sprites\\animated\\shotgun.png");
	shooting.numFrames = 11;
	shooting.animationSpeed = 0.09;
	shooting.textureArea = { 0, 0, (float)shooting.texture.width, (float)shooting.texture.height };
	shooting.positionOnWindow.width = (float)(shooting.texture.width);
	shooting.positionOnWindow.height = (float)(shooting.texture.height);
	weapon->sprite->animations.push_back(shooting);
}
