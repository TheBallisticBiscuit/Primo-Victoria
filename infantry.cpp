#include "infantry.h"
#pragma region Newell

Infantry::Infantry(void)
{
}


Infantry::~Infantry(void)
{
}

bool Infantry::initialize(int width, int height, int ncols, TextureManager* textureM, Game* game){
		setScale(INFANTRY_SCALING);
		setMovementPerTurn(3);
		setMovementLeft(0);
		setRange(1);
		setHealth(10);
		setDamage(2);
		return Unit::initialize(width, height, ncols, textureM, game);
}
#pragma endregion
