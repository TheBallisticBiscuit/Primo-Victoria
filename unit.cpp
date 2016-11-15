#include "unit.h"
#pragma region Newell

Unit::Unit(void)
{
}


Unit::~Unit(void)
{
}

bool Unit::initialize(int height, int width, int ncols, TextureManager* textureM, Game* game){
	setX(200);
	setY(200);
	return Entity::initialize(game, 96, 96, 3, textureM);
}

void Unit::setDamage(int newDamage){
	damage = newDamage;
}

void Unit::setHP(int newHP){
	HP = newHP;
}

void Unit::setMovementPerTurn(int newMovement){
	movementPerTurn = newMovement;
}

void Unit::setMovementLeft(int newMovement){
	movementLeft = newMovement;
}

void Unit::setRange(int newRange){
	range = newRange;
}

void Unit::setTile(int x, int y){
	tile.x = x;
	tile.y = y;
}

void Unit::fight(Unit& opponent){
	while(HP > 0 && opponent.getHP() > 0){
		HP -= opponent.getDamage();
		opponent.setHP(opponent.getHP()-damage);
	}
}
#pragma endregion