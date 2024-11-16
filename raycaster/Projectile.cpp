#include "Projectile.h"
#include "TextureManager.h"
#include "RayCaster.h"

Projectile::Projectile(Point2D pos, double ang)
{
	position = pos;
	speed = 10;
	angle = ang;
	timer = 0;
	timeLimit = 3;

	sprite = new Animated();
	sprite->scale = 1;
	sprite->shift = -0.3;

	TextureManager* texMgr = TextureManager::getInstance();
	Animation fireball = {};
	fireball.texture = texMgr->getTexture("sprites\\animated\\fireball.png");
	fireball.numFrames = 2;
	fireball.animationSpeed = 2;
	sprite->animations.push_back(fireball);
}

bool Projectile::shoot()
{
	RayCaster raycaster;
	Player* player = Player::getInstance();
	Map map = *Map::getInstance();

	RayCastResult rayToWall = raycaster.rayCast(angle, position, map);
	double distanceToPlayer = sprite->getDistanceFromPlayer(position, *player);

	bool projectileCrash = distanceToPlayer < 0.5 or rayToWall.depth < 0.5 or timer > timeLimit;
	if (projectileCrash) {
		return true;
	}
	else {
		Point2D d;
		d.x = cos(angle) * speed * GetFrameTime();
		d.y = sin(angle) * speed * GetFrameTime();
		position.x += d.x;
		position.y += d.y;
		timer += GetFrameTime();
		return false;
	}
}

Point2D Projectile::getPosition()
{
	return position;
}
