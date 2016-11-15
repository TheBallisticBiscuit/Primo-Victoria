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
		setHP(10);
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

void Infantry::fight(Unit& opponent, float frameTime){
	setFrames(INFANTRY_ATTACK_RIGHT_START, INFANTRY_ATTACK_RIGHT_END);
	if(getFrameCounter() > INFANTRY_ANIMATION_DELAY*12){
		setFrameCounter(0);
		setHP(getHP()-opponent.getDamage());
		opponent.setHP(opponent.getHP()-getDamage());
	}
	setFrameCounter(getFrameCounter()+frameTime);
}

bool Infantry::kill(float frameTime){
	setFrames(INFANTRY_DEATH_DOWN_START, INFANTRY_DEATH_DOWN_END);
	if(getFrameCounter() > INFANTRY_ANIMATION_DELAY*6){
		setFrameCounter(0);
		setVisible(false);
		setActive(false);
		return true;
	}
	setFrameCounter(getFrameCounter()+frameTime);
	return false;
}
#pragma endregion
