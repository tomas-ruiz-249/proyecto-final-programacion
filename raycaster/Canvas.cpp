#include "Canvas.h"
#include <cmath>
#include <string>
#include <iostream>

void Canvas::startWindow()
{
	InitWindow(screenWidth, screenHeight, "game");
	SetWindowState(FLAG_VSYNC_HINT);
	SetTargetFPS(60);
	DisableCursor();
	textureManager.loadTexturesToVRAM();
}

void Canvas::draw(Map map, Player player)
{
	BeginDrawing();
		ClearBackground(BLACK);
		draw3D(player, map);
		//drawMap(map);
		//drawPlayer(player);
	EndDrawing();
}

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

void Canvas::draw3D(Player player, Map map)
{	
	drawBackground();
	double rayAngle = player.angle - (halfFOV) + 0.0001;
	RayCastResult hit;
	for (int ray = 0; ray < numRays; ray++) {
		hit = rayCaster.rayCast(rayAngle, player.position, map);
		hit.length *= cos(player.angle - rayAngle);
		hit.index = ray;
		drawColumn(hit);
		rayAngle += deltaAngle;
	}
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
	backgroundOffset += GetMouseDelta().x;
	if (backgroundOffset > background.width) {
		 backgroundOffset = 0;
	}
	Rectangle source = { backgroundOffset, 0, background.width, background.height };
	Rectangle dest = { 0, 0, screenWidth, halfScreenHeight };
	DrawTexturePro(background, source, dest, { 0,0 }, 0, WHITE);
	Color light = { 30, 30, 20 ,255 };
	DrawRectangleGradientV(0, halfScreenHeight, screenWidth, halfScreenHeight, BLACK, light);
}

Canvas::Canvas()
{
	screenWidth = 900;
	screenHeight = 450;
	halfScreenHeight = screenHeight / 2;
	halfScreenWidth = screenWidth / 2;

	FOV = PI / 3;
	halfFOV = FOV / 2;
	numRays = screenWidth;
	deltaAngle = FOV / numRays;
	screenDist = halfScreenWidth / tan(halfFOV);
	scale = screenWidth / numRays;

	backgroundOffset = 0;

	cellSize = screenHeight / GRID_SIZE;
}
