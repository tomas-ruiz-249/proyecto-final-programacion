#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>
#include "Canvas.h"
#include "Drawable.h"
#include "Enemy.h"
#include "enemyManager.h"
#include "Lamp.h"

Canvas::Canvas()
{
	screenWidth = 0;
	screenHeight = 0;
	windowWidth = 0;
	windowHeight = 0;
	halfWindowHeight = 0;
	halfWindowWidth = 0;
	FOV = 0;
	halfFOV = 0;
	screenDist = 0;
	scale = 0;
	rayCaster = RayCaster();
	backgroundOffset = 0;
	cellSize = 0;
	darkness = 0;
	textureManager = TextureManager::getInstance();
}

Canvas::Canvas(int width, int height)
{
	screenWidth = width;
	screenHeight = height;
	windowWidth = screenWidth * 0.8;
	windowHeight = screenHeight * 0.8;
	halfWindowWidth = windowWidth / 2;
	halfWindowHeight = windowHeight / 2;

	FOV = PI / 3;
	halfFOV = FOV / 2;
	screenDist = halfWindowWidth / tan(halfFOV);

	int numRays = windowWidth / 2;
	double deltaAngle = FOV / numRays;
	rayCaster = RayCaster(numRays, deltaAngle);
	scale = windowWidth / numRays;
	darkness = 0.00000009;
	textureManager = TextureManager::getInstance();

	backgroundOffset = 0;

	cellSize = windowHeight / GRID_SIZE;
}

void Canvas::startWindow()
{
	InitWindow(windowWidth, windowHeight, "");
	textureManager->loadTexturesToVRAM();
	SetWindowState(FLAG_VSYNC_HINT);
	SetTargetFPS(60);
	DisableCursor();
}

void Canvas::draw(const Map& map, const Player& player, ObjectManager& objManager, EnemyManager& enemyManager)
{
	BeginDrawing();
	ClearBackground(BLACK);
	draw3D(player, map, objManager, enemyManager);
	EndDrawing();
}

void Canvas::draw3D(const Player& player, const Map& map, ObjectManager& objManager, EnemyManager& enemyManager)
{
	drawBackground();

	//add walls to queue
	double rayAngle = player.angle - (halfFOV) + 0.0001;
	auto rays = rayCaster.getAllRays(rayAngle, player, map);
	for (auto& ray : rays) {
		Drawable* casted = &ray;
		drawQueue.push_back(&ray);
	}
	rayCaster.clearRays();

	//add objects to draw queue
	auto objects = objManager.getObjectList();
	for (auto& obj : *objects) {
		obj->sprite->depth = obj->sprite->getDistanceFromPlayer(obj->position, player);
		Drawable* casted = obj->sprite;
		drawQueue.push_back(casted);
	}
	
	//add enemies to draw queue
	auto enemies = enemyManager.getEnemyList();
	for (auto& enemy: *enemies){
		enemy.sprite->depth = enemy.sprite->getDistanceFromPlayer(enemy.position, player);
		enemy.sprite->position = enemy.position;
		drawQueue.push_back(enemy.sprite);
	}

	//sort queue by distance from player and draw
	std::sort(drawQueue.begin(), drawQueue.end(), [](const Drawable* a, const Drawable* b) { return a->depth > b->depth; });
	RayCastResult* rayPtr;
	Drawable* spritePtr;
	Animated* animatedPtr;
	for (auto& drawablePtr : drawQueue) {
		rayPtr = dynamic_cast<RayCastResult*>(drawablePtr);
		spritePtr = dynamic_cast<Drawable*>(drawablePtr);
		animatedPtr = dynamic_cast<Animated*>(drawablePtr);
		if (rayPtr) {
			drawColumn(*rayPtr);
		}
		else if (animatedPtr) {
			drawAnimatedSprite(*animatedPtr, player);
		}
		else if (spritePtr) {
			drawStaticSprite(*spritePtr, player);
		}
	}
	drawQueue.clear();

	drawWeapon(*player.weapon);
}


void Canvas::drawStaticSprite(Drawable sprite, Player player)
{
	//difference between player position and object position;
	Point2D d;
	d.x = sprite.position.x - player.position.x;
	d.y = sprite.position.y - player.position.y;
	double angleToSprite = atan2(d.y, d.x);

	//angle from player direction to sprite
	double delta = angleToSprite - player.angle;
	if ((d.x > 0 and player.angle > PI) or (d.x < 0 and d.y < 0)) {
		delta += PI * 2;
	}

	double deltaRays = delta / rayCaster.getDeltaAngle();
	auto halfNumRays = rayCaster.getNumRays() / 2;
	int screenPosX = (halfNumRays + deltaRays) * scale;

	double dist = sprite.getDistanceFromPlayer(sprite.position, player);

	if ((-sprite.tex.width < screenPosX) and (screenPosX < (windowWidth + sprite.tex.width)) and dist > 0.0) {
		double imgRatio = (float)sprite.tex.width / (float)sprite.tex.height;
		double proj = screenDist / dist * sprite.scale;
		double projWidth = proj * imgRatio;
		double projHeight = proj;
		double halfWidth = projWidth / 2;
		double posX = screenPosX - halfWidth;
		double heightShift = projHeight * sprite.shift;
		double posY = halfWindowHeight - projHeight / 2 + heightShift;
		sprite.textureArea = { 0,0, (float)sprite.tex.width, (float)sprite.tex.height };
		sprite.positionOnWindow = { (float)(posX), (float)(posY), (float)(projWidth), (float)(projHeight) };
		Color textureColor = WHITE;
		textureColor.r = 225 / (1 + pow(sprite.depth, 5) * darkness);
		textureColor.g = 225 / (1 + pow(sprite.depth, 5) * darkness);
		textureColor.b = 225 / (1 + pow(sprite.depth, 5) * darkness);
		DrawTexturePro(sprite.tex, sprite.textureArea, sprite.positionOnWindow, { 0,0 }, 0, textureColor);
	}
}

void Canvas::drawAnimatedSprite(Animated& sprite, Player player)
{
	//difference between player position and object position;
	Point2D d;
	d.x = sprite.position.x - player.position.x;
	d.y = sprite.position.y - player.position.y;
	double angleToSprite = atan2(d.y, d.x);

	//angle from player direction to sprite
	double delta = angleToSprite - player.angle;
	if ((d.x > 0 and player.angle > PI) or (d.x < 0 and d.y < 0)) {
		delta += PI * 2;
	}

	double deltaRays = delta / rayCaster.getDeltaAngle();
	auto halfNumRays = rayCaster.getNumRays() / 2;
	int screenPosX = (halfNumRays + deltaRays) * scale;

	double dist = sprite.getDistanceFromPlayer(sprite.position, player);

	int& index = sprite.animationIndex;

	if (index > sprite.animations.size() - 1) {
		drawStaticSprite(sprite, player);
		return;
	}

	Animation& current = sprite.animations[sprite.animationIndex];

	if ((-current.texture.width < screenPosX) and (screenPosX < (windowWidth + current.texture.width)) and dist > 0.0) {
		double imgRatio = (float)current.texture.width / (float)current.texture.height;
		double proj = screenDist / dist * sprite.scale;
		double projWidth = proj * imgRatio / current.numFrames;
		double projHeight = proj;
		double halfWidth = projWidth / 2;
		double posX = screenPosX - halfWidth;
		double heightShift = projHeight * sprite.shift;
		double posY = halfWindowHeight - projHeight / 2 + heightShift;
		current.textureArea = { 0,0, (float)current.texture.width, (float)current.texture.height };
		current.positionOnWindow = { (float)(posX), (float)(posY), (float)(projWidth), (float)(projHeight) };

		sprite.isOnScreenCenter = (halfWindowWidth - current.positionOnWindow.width) < posX 
							and posX < (halfWindowWidth + current.positionOnWindow.width);

		Color textureColor = WHITE;
		textureColor.r = 225 / (1 + pow(sprite.depth, 5) * darkness);
		textureColor.g = 225 / (1 + pow(sprite.depth, 5) * darkness);
		textureColor.b = 225 / (1 + pow(sprite.depth, 5) * darkness);
		animate(sprite, index, textureColor);
	}
}

void Canvas::drawColumn(RayCastResult ray)
{
	Color wallColor = WHITE;
	wallColor.r = 225 / (1 + pow(ray.depth, 5) * darkness);
	wallColor.g = 225 / (1 + pow(ray.depth, 5) * darkness);
	wallColor.b = 225 / (1 + pow(ray.depth, 5) * darkness);

	double projectionHeight = screenDist / (ray.depth + 0.0001);

	Texture columnTexture;
	switch (ray.wall) {
	case brick:
		columnTexture = textureManager->getTexture("walls\\brick.png");
		break;
	case stone:
		columnTexture = textureManager->getTexture("walls\\stone.png");
		break;
	case mossyStone:
		columnTexture = textureManager->getTexture("walls\\mossy_stone.png");
		break;
	default:
		columnTexture = textureManager->getTexture("");
		break;
	}

	if (ray.horizontalTextureOffset > columnTexture.width) {
		ray.horizontalTextureOffset = 0;
	}
	Rectangle source = { ray.horizontalTextureOffset * (columnTexture.width - scale), 0, scale, columnTexture.height };
	Rectangle dest = { ray.index * scale, halfWindowHeight - (projectionHeight / 2), scale, projectionHeight };
	ray.textureArea = source;
	ray.positionOnWindow = dest;
	DrawTexturePro(columnTexture, ray.textureArea, ray.positionOnWindow, { 0,0 }, 0.f, wallColor);
}

void Canvas::drawWeapon(Weapon& weapon)
{
	int& index = weapon.sprite->animationIndex;
	Animation& anim = weapon.sprite->animations[index];
	if (weapon.reloading and !anim.isAnimationDone()) {
		anim.positionOnWindow.x = (float)(halfWindowWidth * 0.8);
		anim.positionOnWindow.y = (float)(windowHeight - anim.texture.height);
		animate(*weapon.sprite, 0, WHITE);
		if (anim.isAnimationDone()) {
			weapon.reloading = false;
		}
	}
	else {
		anim.resetAnimation();
		Texture& shotgun = weapon.sprite->tex;
		weapon.sprite->positionOnWindow.x = (float)(halfWindowWidth * 0.8);
		weapon.sprite->positionOnWindow.y = (float)(windowHeight - shotgun.height);
		DrawTexturePro(shotgun, weapon.sprite->textureArea, weapon.sprite->positionOnWindow, { 0,0 }, 0, WHITE);
	}
}

void Canvas::drawBackground()
{
	Texture background = textureManager->getTexture("backgrounds\\sunset.png");
	backgroundOffset += GetMouseDelta().x * 1.1;
	if (backgroundOffset > background.width) {
		backgroundOffset = 0;
	}
	Rectangle source = { backgroundOffset, 0, background.width, background.height };
	Rectangle dest = { 0, 0, windowWidth, halfWindowHeight };
	DrawTexturePro(background, source, dest, { 0,0 }, 0, WHITE);
	Color light = { 30, 30, 20 ,255 };
	DrawRectangleGradientV(0, halfWindowHeight, windowWidth, halfWindowHeight, BLACK, light);
}

void Canvas::animate(Animated& animated, int index, Color color)
{
	Animation& current = animated.animations[index];
	current.frameTimer += GetFrameTime();
	if (current.frameTimer > GetFrameTime() * current.animationSpeed) {
		current.frameTimer = 0;
		if (!current.stop) {
			current.nextFrame();
		}
	}
	int frame = current.getCurrentFrame();
	int frameWidth = current.texture.width / current.numFrames;
	current.textureArea.width = frameWidth;
	current.textureArea.x = frame * frameWidth;
	DrawTexturePro(current.texture, current.textureArea, current.positionOnWindow, {0,0}, 0, color);
	current.positionOnWindow.width = current.texture.width /current.numFrames;
}


//TODO: usar funciones para dibujar minimapa

void Canvas::drawPlayer(Player player)
{
	int x = player.position.x * cellSize;
	int y = player.position.y * cellSize;
	double cosA = cos(player.angle);
	double sinA = sin(player.angle);
	DrawCircle(x, y, cellSize / 9, YELLOW);
	DrawLine(x, y, x + cosA * 20, y + sinA * 20, YELLOW);
}

void Canvas::drawMap(Map map)
{
	for (int row = 0; row < GRID_SIZE; row++) {
		for (int column = 0; column < GRID_SIZE; column++) {
			if (map.getElementAt(row, column) == 0) {
				DrawRectangle(column * cellSize, row * cellSize, cellSize, cellSize, BLACK);
			}
			else {
				DrawRectangle(column * cellSize, row * cellSize, cellSize, cellSize, WHITE);
			}
		}
	}
}

void Canvas::drawRay2D(Point2D end)
{
	int x = end.x * cellSize;
	int y = end.y * cellSize;
	DrawCircle(x, y, cellSize / 9, GREEN);
}

void Canvas::drawRay2D(Point2D start, Point2D end)
{
	Vector2 pos;
	Vector2 hit;
	pos.x = start.x * cellSize;
	pos.y = start.y * cellSize;
	hit.x = end.x * cellSize;
	hit.y = end.y * cellSize;
	DrawLineEx(pos, hit,  1.f, GREEN);
}