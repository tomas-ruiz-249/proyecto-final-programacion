#include <raylib.h>
#include <cmath>
#include "Player.h"
#include <iostream>

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
