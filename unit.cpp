#include "unit.h"
#pragma region Newell

Unit::Unit(void)
{
}


Unit::~Unit(void)
{
}

bool Unit::initialize(int height, int width, int ncols, TextureManager* textureM, Game* game){
	setLastDirection(right);
	animating = false;
	return Entity::initialize(game, height, width, ncols, textureM);
}

void Unit::setFrameCounter(float newFrameCounter){
	frameCounter = newFrameCounter;
}

void Unit::setDamage(int newDamage){
	damage = newDamage;
}

void Unit::setHP(int newHP){
	HP = newHP;
}

void Unit::setDef(float newDefence){
	defence = newDefence;
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

void Unit::setSpecial(int newSpecial){
	specialAbility = newSpecial;
}

void Unit::setTile(int x, int y){
	tile.x = x;
	tile.y = y;
}

void Unit::setAnimating(bool newBool){
	animating = newBool;
}

void Unit::setLastDirection(LastDirection newDirection){
	lastDirection = newDirection;
}
#pragma endregion