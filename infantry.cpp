#include "infantry.h"
#pragma region Newell

Infantry::Infantry(void)
{
}


Infantry::~Infantry(void)
{
}

bool Infantry::initialize(int width, int height, int ncols, int team, TextureManager* textureM, Game* game){
	setScale(INFANTRY_SCALING);
	setMovementPerTurn(3);
	setMovementLeft(0);
	setRange(1);
	setHP(10);
	setDamage(2);
	setTeam(team);
	setFrameDelay(INFANTRY_ANIMATION_DELAY);
	setFrameCounter(0);
	setVelocity(VECTOR2(0, 0));
	return Unit::initialize(width, height, ncols, textureM, game);
}

void Infantry::update(float frameTime){
	if(velocity.x == 0 && velocity.y == 0 && !isAnimating()){
		switch(getLastDirection()){
		case up:
			setFrames(INFANTRY_IDLE_UP_START, INFANTRY_IDLE_UP_END);
			break;
		case left:
			setFrames(INFANTRY_IDLE_LEFT_START, INFANTRY_IDLE_LEFT_END);
			break;
		case down:
			setFrames(INFANTRY_IDLE_DOWN_START, INFANTRY_IDLE_DOWN_END);
			break;
		case right:
			setFrames(INFANTRY_IDLE_RIGHT_START, INFANTRY_IDLE_RIGHT_END);
			break;
		}
	}
	setX(getX()+getVelocity().x*INFANTRY_SPEED*frameTime);
	setY(getY()+getVelocity().y*INFANTRY_SPEED*frameTime);
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

bool Infantry::moveUp(){
	setLastDirection(up);
	setFrames(INFANTRY_RUN_UP_START, INFANTRY_RUN_UP_END);
	setVelocity(VECTOR2(0, -1));
	if(getY() < (getTileY()-1)*TERRAIN_HEIGHT){
		setTile(getTileX(), getTileY()-1);
		setVelocity(VECTOR2(0, 0));
		setY(getTileY()*TERRAIN_HEIGHT);
		return true;
	}
	return false;
}
bool Infantry::moveDown(){
	setLastDirection(down);
	setFrames(INFANTRY_RUN_DOWN_START, INFANTRY_RUN_DOWN_END);
	setVelocity(VECTOR2(0, 1));
	if(getY() > (getTileY()+1)*TERRAIN_HEIGHT){
		setTile(getTileX(), getTileY()+1);
		setVelocity(VECTOR2(0, 0));
		setY(getTileY()*TERRAIN_HEIGHT);
		return true;
	}
	return false;
}
bool Infantry::moveLeft(){
	setLastDirection(left);
	setFrames(INFANTRY_RUN_LEFT_START, INFANTRY_RUN_LEFT_END);
	setVelocity(VECTOR2(-1, 0));
	if(getX() < (getTileX()-1)*TERRAIN_WIDTH){
		setTile(getTileX()-1, getTileY());
		setVelocity(VECTOR2(0, 0));
		setX(getTileX()*TERRAIN_HEIGHT);
		return true;
	}
	return false;
}
bool Infantry::moveRight(){
	setLastDirection(right);
	setFrames(INFANTRY_RUN_RIGHT_START, INFANTRY_RUN_RIGHT_END);
	setVelocity(VECTOR2(1, 0));
	if(getX() > (getTileX()+1)*TERRAIN_WIDTH){
		setTile(getTileX()+1, getTileY());
		setVelocity(VECTOR2(0, 0));
		setX(getTileX()*TERRAIN_HEIGHT);
		return true;
	}
	return false;
}
#pragma endregion
