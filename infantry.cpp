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
		setFrameDelay(INFANTRY_ANIMATION_DELAY);
		return Unit::initialize(width, height, ncols, textureM, game);
}

void Infantry::update(float frameTime){
	if(velocity.x == 0 && velocity.y == 0){
		setFrames(INFANTRY_DEATH_RIGHT_START, INFANTRY_DEATH_RIGHT_END);
	}
	Entity::update(frameTime);
}
#pragma endregion
