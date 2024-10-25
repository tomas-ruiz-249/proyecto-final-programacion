#pragma once
#include "Entity.h"
class Player : public Entity {
public:
	void move(Map& map) override;
private:
};