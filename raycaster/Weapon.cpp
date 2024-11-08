#include "Weapon.h"
#include "TextureManager.h"
#include "Player.h"

Weapon::Weapon()
{
	auto texMgr = TextureManager::getInstance();
	sprite = new Animated();
	sprite->tex = texMgr->getTexture("");
	reloading = false;
}
