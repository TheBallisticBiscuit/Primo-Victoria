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
		setFrameCounter(0);
		return Unit::initialize(width, height, ncols, textureM, game);
}

void Infantry::update(float frameTime){
	if(velocity.x == 0 && velocity.y == 0 && !isAnimating()){
		switch(getLastDirection()){
		case up:
			setFrames(INFANTRY_IDLE_UP_START, INFANTRY_IDLE_UP_END);
		case left:
			setFrames(INFANTRY_IDLE_LEFT_START, INFANTRY_IDLE_LEFT_END);
		case down:
			setFrames(INFANTRY_IDLE_DOWN_START, INFANTRY_IDLE_DOWN_END);
		case right:
			setFrames(INFANTRY_IDLE_RIGHT_START, INFANTRY_IDLE_RIGHT_END);
		}
	}
	Entity::update(frameTime);
}

void Infantry::fight(Unit& opponent, float frameTime){
	setFrames(INFANTRY_ATTACK_RIGHT_START, INFANTRY_ATTACK_RIGHT_END);
	setAnimating(true);
	opponent.setFrames(INFANTRY_ATTACK_LEFT_START, INFANTRY_ATTACK_LEFT_END);
	opponent.setAnimating(true);
	if(getFrameCounter() > INFANTRY_ANIMATION_DELAY*12){
		setFrameCounter(0);
		setHP(getHP()-opponent.getDamage());
		opponent.setHP(opponent.getHP()-getDamage());
		setAnimating(false);
		opponent.setAnimating(false);
	}
	setFrameCounter(getFrameCounter()+frameTime);
}

bool Infantry::kill(float frameTime){
	setFrames(INFANTRY_DEATH_DOWN_START, INFANTRY_DEATH_DOWN_END);
	if(getFrameCounter() > INFANTRY_ANIMATION_DELAY*6){
		setFrameCounter(0);
		setVisible(false);
		setActive(false);
		setAnimating(false);
		return true;
	}
	setFrameCounter(getFrameCounter()+frameTime);
	return false;
}
#pragma endregion
