#include "Canvas.h"
#include <cmath>
#include <string>
#include <iostream>

Canvas::Canvas()
{
	screenWidth = 0;
	screenHeight = 0;
	halfScreenHeight = 0;
	halfScreenWidth = 0;
	FOV = 0;
	halfFOV = 0;
	screenDist = 0;
	scale = 0;
	rayCaster = RayCaster();
	backgroundOffset = 0;
	cellSize = 0;
}

Canvas::Canvas(int width, int height)
{
	screenWidth = width * 0.8;
	screenHeight = height * 0.8;
	halfScreenWidth = screenWidth / 2;
	halfScreenHeight = screenHeight / 2;

	FOV = PI / 3;
	halfFOV = FOV / 2;
	screenDist = halfScreenWidth / tan(halfFOV);
	
	int numRays = screenWidth;
	double deltaAngle = FOV / numRays;
	rayCaster = RayCaster(numRays, deltaAngle);
	scale = screenWidth / numRays;

	backgroundOffset = 0;

	cellSize = screenHeight / GRID_SIZE;
}

void Canvas::startWindow()
{
	InitWindow(screenWidth, screenHeight, "");
	SetWindowState(FLAG_VSYNC_HINT);
	SetTargetFPS(60);
	DisableCursor();
	textureManager.loadTexturesToVRAM();
}

void Canvas::draw(Map& map, Player& player, std::vector<Object>& objects)
{
	BeginDrawing();
		ClearBackground(BLACK);
		draw3D(player, map);
	EndDrawing();
}

void Canvas::draw3D(Player player, Map map)
{	
	drawBackground();

	double rayAngle = player.angle - (halfFOV) + 0.0001;
	auto rays = rayCaster.getAllRays(rayAngle, player, map);
	for (auto& ray : rays) {
		drawColumn(ray);
	}
	rayCaster.clearRays();
	
	drawWeapon();
}

void Canvas::drawColumn(RayCastResult ray)
{
	Color wallColor = WHITE;
	double darkness = 0.000009;
	wallColor.r = 225 / (1 + pow(ray.length, 5) * darkness);
	wallColor.g = 225 / (1 + pow(ray.length, 5) * darkness);
	wallColor.b = 225 / (1 + pow(ray.length, 5) * darkness);

	double projectionHeight = screenDist / (ray.length + 0.0001);

	Texture columnTexture;
	switch (ray.wall) {
		case brick:
			columnTexture = textureManager.getTexture("walls\\brick.png");
			break;
		case stone:
			columnTexture = textureManager.getTexture("walls\\stone.png");
			break;
		case mossyStone:
			columnTexture = textureManager.getTexture("walls\\mossy_stone.png");
			break;
		default:
			columnTexture = textureManager.getTexture("");
			break;
	}

	if (ray.textureOffset > columnTexture.width) {
		ray.textureOffset = 0;
	}
	Rectangle source = { ray.textureOffset * (columnTexture.width - scale), 0, scale, columnTexture.height };
	Rectangle dest = { ray.index * scale, halfScreenHeight - (projectionHeight / 2), scale, projectionHeight };
	DrawTexturePro(columnTexture, source, dest, { 0,0 }, 0.f, wallColor);
}

void Canvas::drawWeapon()
{
	Texture2D shotgun = textureManager.getTexture("sprites\\static\\shotgun.png");
	double shotgunScale = 0.5;
	Vector2 position = { halfScreenWidth - (shotgun.width * shotgunScale) / 4, screenHeight - (shotgun.height * shotgunScale)};
	DrawTextureEx(shotgun, position, 0, shotgunScale, WHITE);
}

void Canvas::drawBackground()
{
	Texture background = textureManager.getTexture("backgrounds\\sunset.png");
	backgroundOffset += GetMouseDelta().x * 1.1;
	if (backgroundOffset > background.width) {
		 backgroundOffset = 0;
	}
	Rectangle source = { backgroundOffset, 0, background.width, background.height };
	Rectangle dest = { 0, 0, screenWidth, halfScreenHeight };
	DrawTexturePro(background, source, dest, { 0,0 }, 0, WHITE);
	Color light = { 30, 30, 20 ,255 };
	DrawRectangleGradientV(0, halfScreenHeight, screenWidth, halfScreenHeight, BLACK, light);
}

void Canvas::drawObject(Object& object, Player& player)
{
	//double playerDist = object.getDistanceFromPlayer(player);
	//Point2D d;
	//d.x = object.position.x - player.position.x;
	//d.y = object.position.y - player.position.y;
	//double theta = atan2(d.y, d.x);
	//double angCenterSprite = theta - player.angle;
	//if ((d.x > 0 && player.angle > PI) || (d.x < 0 && d.y < 0)) {
	//	angCenterSprite += PI * 2;
	//}

	//double deltaRays = angCenterSprite / deltaAngle;
	//double screenPosX = ((numRays / 2) + deltaRays) * scale;

	////render
	//Texture objectTexture = textureManager.getTexture("sprites\\static\\health.png");
	//Rectangle src = { 0, 0, objectTexture.width, objectTexture.height };
	//double objScale = 0.4;
	//Rectangle dest;
	//dest.x = (halfScreenWidth - objectTexture.width * objScale / 2);
	//dest.y = (halfScreenHeight - objectTexture.height * objScale / 2);
	//dest.width = objectTexture.width * objScale;
	//dest.height = objectTexture.height * objScale;

	//if (-(objectTexture.width) / 2 < screenPosX && screenPosX < (screenWidth + objectTexture.width) && playerDist < 0.5) {
	//	DrawTexturePro(objectTexture, src, dest, { 0,0 }, 0, WHITE);
	//}
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