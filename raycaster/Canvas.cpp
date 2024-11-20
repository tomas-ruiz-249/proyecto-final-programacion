#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>
#include "Canvas.h"
#include "Drawable.h"
#include "Enemy.h"
#include "enemyManager.h"
#include "Lamp.h"
#include "RangedEnemy.h"
#include "Game.h"

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
	darkness = 0.00001;
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

	doomFont = LoadFontEx("assets/fonts/AmazDooMLeft.ttf", 500, nullptr, 0);
}
GameState Canvas::draw(const Map& map, Player& player, ObjectManager& objManager, EnemyManager& enemyManager, GameState state)
{
	GameState newState = na;
	BeginDrawing();
	ClearBackground(BLACK);

	switch (state) {
	case mainMenu:
		newState = drawMenu();
		break;

	case pause:
		newState = drawPause();
		break;

	case playing:
		DisableCursor();
		draw3D(player, map, objManager, enemyManager);
		drawHUD(player);
		break;

	case gameOver:
		DrawText("Nice Try", 250, 300, 100, RED);
		DrawText("Press Enter to reset", 250, 400, 50, RED);
		break;

	case options:
		newState = drawOptions();
		break;
	}
	EndDrawing();
	return newState;
}





void Canvas::draw3D(const Player& player, const Map& map, ObjectManager& objManager, EnemyManager& enemyManager)
{
	drawBackground(player);

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
		enemy->sprite->depth = enemy->sprite->getDistanceFromPlayer(enemy->position, player);
		enemy->sprite->position = enemy->position;
		drawQueue.push_back(enemy->sprite);
		//add projectile to draw queue if enemy can shoot projectiles
		auto ranged = dynamic_cast<RangedEnemy*>(enemy);
		if (ranged) {
			for (auto proj : ranged->getProjectiles()) {
				if (proj) {
					proj->sprite->position = proj->getPosition();
					proj->sprite->depth = proj->sprite->getDistanceFromPlayer(proj->getPosition(), player);
					drawQueue.push_back(proj->sprite);
				}
			}
		}
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
	drawBlood(player);
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

void Canvas::drawHUD(Player& player)
{
	// 1. Cargar y dibujar la textura del HUD
	Texture hudTexture = textureManager->getTexture("sprites\\static\\hudgun.png");
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	int hudWidth = 350;
	int hudHeight = 200;
	int hudPosX = screenWidth - hudWidth - 20;
	int hudPosY = screenHeight - hudHeight - 30;

	Rectangle sourceRect = { 0.0f, 0.0f, (float)hudTexture.width, (float)hudTexture.height };
	Rectangle destRect = { (float)hudPosX, (float)hudPosY, (float)hudWidth, (float)hudHeight };
	Vector2 origin = { 0.0f, 0.0f };
	DrawTexturePro(hudTexture, sourceRect, destRect, origin, 0.0f, WHITE);

	// 2. Mostrar el texto de munición restante
	int ammoCount = player.weapon->ammoCount;
	std::string ammoText = "Ammo: " + std::to_string(ammoCount);
	int ammoTextPosX = screenWidth - 300;
	int ammoTextPosY = screenHeight - 100;
	DrawTextEx(doomFont, ammoText.c_str(), { (float)ammoTextPosX, (float)ammoTextPosY }, 100, 2, WHITE);

	// 3. Dibujar el ícono de la munición
	Texture ammoIcon = textureManager->getTexture("sprites\\static\\ammodoom.png");
	Rectangle ammoIconSource = { 0.0f, 0.0f, (float)ammoIcon.width, (float)ammoIcon.height };
	Rectangle ammoIconDest = { (float)(screenWidth - 90), (float)(screenHeight - 100), 75.0f, 75.0f };
	DrawTexturePro(ammoIcon, ammoIconSource, ammoIconDest, origin, 0.0f, WHITE);

	// 4. Dibujar la barra de salud en la parte superior izquierda de la pantalla
	int health = player.getHealth();
	int totalBars = 10;
	int numBars = health / 10;

	int barWidth = 55;
	int barHeight = 40;
	int barStartX = 20;
	int barStartY = 20;
	int barSpacing = 10;

	for (int i = 0; i < totalBars; i++)
	{
		int barPosX = barStartX + i * (barWidth + barSpacing);
		Color barColor = (i < numBars) ? DARKPURPLE : DARKGRAY;
		DrawRectangle(barPosX, barStartY, barWidth, barHeight, barColor);
	}

	// 5. Dibujar el texto de salud debajo de las barras de vida
	std::string healthText = "Health: " + std::to_string(health) + "/100";
	int healthTextPosX = barStartX;
	int healthTextPosY = barStartY + barHeight + 20;
	DrawTextEx(doomFont, healthText.c_str(), { (float)healthTextPosX, (float)healthTextPosY }, 50, 2, WHITE);


	// 7. Dibujar un crosshair circular en el centro de la pantalla
	int centerX = screenWidth / 2;
	int centerY = screenHeight / 2;
	int radius = 20;
	int thickness = 3;
	DrawCircleLines(centerX, centerY, radius, WHITE);
	DrawCircleLines(centerX, centerY, radius - thickness, WHITE);

	// 8. Mostrar "Reloading" debajo del crosshair si el arma está recargando
	if (player.weapon->reloading)
	{
		std::string reloadingText = "Reloading...";
		int reloadingFontSize = 40;
		int reloadingTextWidth = MeasureTextEx(doomFont, reloadingText.c_str(), reloadingFontSize, 2).x;
		int reloadingTextPosX = (screenWidth / 2) - (reloadingTextWidth / 2);
		int reloadingTextPosY = centerY + radius + 20;
		DrawTextEx(doomFont, reloadingText.c_str(), { (float)reloadingTextPosX, (float)reloadingTextPosY }, reloadingFontSize, 2, WHITE);
	}

	//NUEVA
	// 9. Dibujar la imagen del holograma en el extremo derecho de la pantalla con color dependiente de la vida
	Texture hologramTexture = textureManager->getTexture("sprites\\static\\holograma.png");

	int hologramWidth = 200;
	int hologramHeight = 300;
	int hologramPosX = screenWidth - hologramWidth - 10;
	int hologramPosY = (screenHeight / 2) - (hologramHeight / 2);

	Rectangle hologramSource = { 0.0f, 0.0f, (float)hologramTexture.width, (float)hologramTexture.height };
	Rectangle hologramDest = { (float)hologramPosX, (float)hologramPosY, (float)hologramWidth, (float)hologramHeight };

	float healthPercentage = health / 100.0f;
	Color hologramColor = {
		(unsigned char)(255 * (1.0f - healthPercentage)),
		(unsigned char)(255 * healthPercentage),
		255,
		255
	};

	DrawTexturePro(hologramTexture, hologramSource, hologramDest, origin, 0.0f, hologramColor);
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

void Canvas::drawBackground(Player player)
{
	Texture background = textureManager->getTexture("backgrounds\\sunset.png");
	if (player.isAlive()) {
		backgroundOffset = (player.angle) / (2 * PI);
		backgroundOffset *= background.width;
	}
	if (backgroundOffset > background.width) {
		backgroundOffset = 0;
	}
	Rectangle source = { backgroundOffset, 0, background.width, background.height };
	Rectangle dest = { 0, 0, windowWidth, halfWindowHeight };
	Color shadow = { 30, 30, 20 ,255 };
	shadow.r = 225 / (1 + pow(9, 5) * darkness);
	shadow.g = 225 / (1 + pow(9,5) * darkness);
	shadow.b = 225 / (1 + pow(9,5) * darkness);
	Color grass = { 30, 30, 20 ,255 };
	DrawTexturePro(background, source, dest, { 0,0 }, 0, shadow);
	DrawRectangleGradientV(0, halfWindowHeight, windowWidth, halfWindowHeight, BLACK, grass);
}

void Canvas::drawBlood(Player player)
{
	Color tint = RED;
	tint.a = 200 * (100 - player.getHealth())/100;
	Rectangle screenTint = { 0,0,windowWidth,windowHeight };
	DrawRectangleRec(screenTint, tint);
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

GameState Canvas::drawMenu()
{
	GameState state = mainMenu;
	ShowCursor();
	std::string titleText = "The purifier of souls";
	int titleFontSize = GetScreenWidth() * 0.15;
	int titleTextWidth = MeasureTextEx(doomFont, titleText.c_str(), titleFontSize, 2).x;
	int titleTextPosX = (windowWidth/ 2) - (titleTextWidth / 2);
	int titleTextPosY = windowHeight / 8;

	DrawTextEx(doomFont, titleText.c_str(), { (float)titleTextPosX, (float)titleTextPosY }, titleFontSize, 2, RED);

	int buttonWidth = 300;
	int buttonHeight = 80;
	int buttonSpacing = 20;

	int buttonX = (windowWidth / 2) - (buttonWidth / 2);
	int buttonYPlay = (windowHeight / 2) - (buttonHeight + buttonSpacing);
	int buttonYExit = (windowHeight / 2) + buttonSpacing;

	Color playColor = WHITE;
	if (CheckCollisionPointRec(GetMousePosition(), { (float)buttonX, (float)buttonYPlay, (float)buttonWidth, (float)buttonHeight })) {
		playColor = GRAY;
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			state = playing;
			HideCursor();
			DisableCursor();
		}
	}
	DrawRectangle(buttonX, buttonYPlay, buttonWidth, buttonHeight, playColor);
	DrawText("Play", buttonX + (buttonWidth / 2) - MeasureText("Play", 40) / 2, buttonYPlay + (buttonHeight / 2) - 20, 40, BLACK);

	Color exitColor = WHITE;
	if (CheckCollisionPointRec(GetMousePosition(), { (float)buttonX, (float)buttonYExit, (float)buttonWidth, (float)buttonHeight })) {
		exitColor = GRAY;
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			return end;
		}
	}
	DrawRectangle(buttonX, buttonYExit, buttonWidth, buttonHeight, exitColor);
	DrawText("Exit", buttonX + (buttonWidth / 2) - MeasureText("Exit", 40) / 2, buttonYExit + (buttonHeight / 2) - 20, 40, BLACK);
	return state; 
}

GameState Canvas::drawPause()
{
	GameState state = pause;
	int buttonWidth = windowWidth * 0.3;
	int buttonHeight = buttonWidth / 4;
	int buttonX = windowWidth * 0.1;
	int buttonY = buttonX * 2;
	int buttonOffset = buttonWidth* 0.08;
	int fontSize = windowHeight * 0.3;
	Rectangle optionsButtonRect;
	Rectangle menuButtonRect;
	Rectangle exitButtonRect;

	optionsButtonRect = { float(buttonX), (float)buttonY, (float)buttonWidth, (float)buttonHeight};
	menuButtonRect = { float(buttonX), float(buttonY + buttonHeight + buttonOffset), (float)buttonWidth, (float)buttonHeight};
	exitButtonRect = { float(buttonX), float(buttonY + (buttonHeight + buttonOffset) * 2), (float)buttonWidth, (float)buttonHeight};

	ShowCursor();

	Vector2 textPos = { windowWidth * 0.03, windowHeight * 0.1 };
	DrawTextEx(doomFont, "PAUSED - Press p to resume", textPos, fontSize * 0.8, fontSize * 0.001, RED);

	DrawRectangleRec(optionsButtonRect, DARKGRAY);
	DrawText("Options", optionsButtonRect.x + buttonWidth * 0.1, optionsButtonRect.y + buttonHeight * 0.1, fontSize / 5, WHITE);

	DrawRectangleRec(menuButtonRect, DARKGRAY);
	DrawText("Main Menu", menuButtonRect.x + buttonWidth * 0.1, menuButtonRect.y + buttonHeight * 0.1, fontSize / 5, WHITE);

	DrawRectangleRec(exitButtonRect, DARKGRAY);
	DrawText("Exit game", exitButtonRect.x + buttonWidth * 0.1, exitButtonRect.y + buttonHeight * 0.1, fontSize / 5, WHITE);

	Vector2 mousePosition = GetMousePosition();

	if (CheckCollisionPointRec(mousePosition, optionsButtonRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		state = options;
	}
	if (CheckCollisionPointRec(mousePosition, menuButtonRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		state = mainMenu;
	}
	if (CheckCollisionPointRec(mousePosition, exitButtonRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		state = end;
	}
	return state;
}

GameState Canvas::drawOptions()
{
	GameState state = options;

	int buttonWidth = windowWidth * 0.3;
	int buttonHeight = buttonWidth / 4;
	int buttonX = windowWidth * 0.1;
	int buttonY = buttonX * 2;
	int buttonOffset = buttonWidth * 0.08;
	int fontSize = windowHeight * 0.3;

	Rectangle sizeButtonRect;
	Rectangle sensibilityButtonRect;
	Rectangle soundButtonRect;
	Rectangle brightnessButtonRect;
	std::string titleText = "Options - press p to go back";
	int titleFontSize = fontSize * 0.8;
	int titleTextPosX = windowWidth * 0.03;
	int titleTextPosY = windowHeight * 0.1;

	int	squareSide = buttonHeight;
	Rectangle plusSensibility;
	Rectangle plusSound;
	Rectangle plusDarkness;
	Rectangle minusSensibility;
	Rectangle minusSound;
	Rectangle minusDarkness;

	DrawTextEx(doomFont, titleText.c_str(), { (float)titleTextPosX, (float)titleTextPosY }, titleFontSize, 2, GREEN);

	sensibilityButtonRect = { (float)buttonX, float(buttonY), (float)buttonWidth, (float)buttonHeight};
	DrawRectangleRec(sensibilityButtonRect, WHITE);
	double sensibility = Player::getInstance()->getSensibility();
	std::string str("Sensibility: ");
	str.append(std::to_string(sensibility));
	str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
	str.erase ( str.find_last_not_of('.') + 1, std::string::npos );
	DrawText(str.c_str(), sensibilityButtonRect.x + buttonWidth * 0.1, sensibilityButtonRect.y + buttonHeight * 0.1, fontSize / 5, BLACK);

	brightnessButtonRect = { float(buttonX), float(buttonY + buttonHeight + buttonOffset), (float)buttonWidth, (float)buttonHeight};
	DrawRectangleRec(brightnessButtonRect, WHITE);
	str = std::string("Darkness: ");
	str.append(std::to_string(darkness * 10000));
	str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
	str.erase ( str.find_last_not_of('.') + 1, std::string::npos );
	DrawText(str.c_str(), brightnessButtonRect.x + buttonWidth * 0.1, brightnessButtonRect.y + buttonHeight * 0.1, fontSize / 5, BLACK);

	str = std::string("Volume: ");
	str.append(std::to_string(GetMasterVolume()));
	str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
	str.erase ( str.find_last_not_of('.') + 1, std::string::npos );
	soundButtonRect = { float(buttonX), float(buttonY + (buttonHeight + buttonOffset) * 2), (float)buttonWidth, (float)buttonHeight};
	DrawRectangleRec(soundButtonRect, WHITE);
	DrawText(str.c_str(), soundButtonRect.x + buttonWidth * 0.1, soundButtonRect.y + buttonHeight * 0.1, fontSize / 5, BLACK);

	plusSensibility.x = sensibilityButtonRect.x + sensibilityButtonRect.width + buttonOffset;
	plusSensibility.y = sensibilityButtonRect.y;
	plusSensibility.width = squareSide;
	plusSensibility.height = squareSide;
	DrawRectangleRec(plusSensibility, LIGHTGRAY);
	DrawText("+", plusSensibility.x * 1.04, plusSensibility.y, fontSize / 2, WHITE);

	minusSensibility.x = plusSensibility.x + plusSensibility.width + buttonOffset;
	minusSensibility.y = plusSensibility.y;
	minusSensibility.width = squareSide;
	minusSensibility.height = squareSide;
	DrawRectangleRec(minusSensibility, LIGHTGRAY);
	DrawText("-", minusSensibility.x * 1.04, minusSensibility.y, fontSize / 2, WHITE);

	plusDarkness.x = brightnessButtonRect.x + brightnessButtonRect.width + buttonOffset;
	plusDarkness.y = brightnessButtonRect.y;
	plusDarkness.width = squareSide;
	plusDarkness.height = squareSide;
	DrawRectangleRec(plusDarkness, LIGHTGRAY);
	DrawText("+", plusDarkness.x * 1.04, plusDarkness.y, fontSize / 2, WHITE);

	minusDarkness.x = plusDarkness.x + plusDarkness.width + buttonOffset;
	minusDarkness.y = plusDarkness.y;
	minusDarkness.width = squareSide;
	minusDarkness.height = squareSide;
	DrawRectangleRec(minusDarkness, LIGHTGRAY);
	DrawText("-", minusDarkness.x * 1.04, minusDarkness.y, fontSize / 2, WHITE);

	plusSound.x = soundButtonRect.x + soundButtonRect.width + buttonOffset;
	plusSound.y = soundButtonRect.y;
	plusSound.width = squareSide;
	plusSound.height = squareSide;
	DrawRectangleRec(plusSound, LIGHTGRAY);
	DrawText("+", plusSound.x * 1.04, plusSound.y, fontSize / 2, WHITE);

	minusSound.x = plusSound.x + plusSound.width + buttonOffset;
	minusSound.y = plusSound.y;
	minusSound.width = squareSide;
	minusSound.height = squareSide;
	DrawRectangleRec(minusSound, LIGHTGRAY);
	DrawText("-", minusSound.x * 1.04, minusSound.y, fontSize / 2, WHITE);

	Vector2 mousePos = GetMousePosition();

	if (CheckCollisionPointRec(mousePos, plusSensibility) and IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		Player* player = Player::getInstance();
		double sensibility = player->getSensibility();
		if (sensibility < 1) {
			player->setSensibility(sensibility + 0.1);
		}
	}

	if (CheckCollisionPointRec(mousePos, minusSensibility) and IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		Player* player = Player::getInstance();
		double sensibility = player->getSensibility();
		if (sensibility > 0) {
			player->setSensibility(sensibility - 0.1);
		}
	}

	if (CheckCollisionPointRec(mousePos, plusDarkness) and IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		if (darkness < 0.00020) {
			darkness += 0.00001;
		}
	}

	if (CheckCollisionPointRec(mousePos, minusDarkness) and IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		if (darkness > 0) {
			darkness -= 0.00001;
		}
	}

	if (CheckCollisionPointRec(mousePos, plusSound) and IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		float currentVol = GetMasterVolume();
		if (currentVol < 1) {
			SetMasterVolume(currentVol += 0.1);
		}
	}

	if (CheckCollisionPointRec(mousePos, minusSound) and IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		float currentVol = GetMasterVolume();
		if (currentVol > 0) {
			SetMasterVolume(currentVol -= 0.1);
		}
	}

	return state;
}
