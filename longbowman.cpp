#include "longbowman.h"


Longbowman::Longbowman(void)
{
}


Longbowman::~Longbowman(void)
{
}

bool Longbowman::initialize(int width, int height, int ncols, int team, TextureManager* textureM, Game* game){
	setScale(LONGBOWMAN_SCALING);
	setMovementPerTurn(3);
	setMovementLeft(0);
	setRange(3);
	setHP(25);
	setDef(1);
	setDamage(30);
	setTeam(team);
	setFrameDelay(LONGBOWMAN_ANIMATION_DELAY);
	setFrameCounter(0);
	setVelocity(VECTOR2(0, 0));
	return Unit::initialize(width, height, ncols, team, textureM, game);
}

void Longbowman::update(float frameTime){
	if(velocity.x == 0 && velocity.y == 0 && !isAnimating()){
		switch(getLastDirection()){
		case up:
			setFrames(LONGBOWMAN_IDLE_UP_START, LONGBOWMAN_IDLE_UP_END);
			break;
		case left:
			setFrames(LONGBOWMAN_IDLE_LEFT_START, LONGBOWMAN_IDLE_LEFT_END);
			break;
		case down:
			setFrames(LONGBOWMAN_IDLE_DOWN_START, LONGBOWMAN_IDLE_DOWN_END);
			break;
		case right:
			setFrames(LONGBOWMAN_IDLE_RIGHT_START, LONGBOWMAN_IDLE_RIGHT_END);
			break;
		}
	}
	setX(getX()+getVelocity().x*LONGBOWMAN_SPEED*frameTime);
	setY(getY()+getVelocity().y*LONGBOWMAN_SPEED*frameTime);
	Entity::update(frameTime);
}

void Longbowman::fight(Unit& opponent, float frameTime, Audio* audio, int rangeOfAttack){

	switch(getLastDirection()){
	case up:
		setAttackFrames(up);
		if(rangeOfAttack <= opponent.getRange()){
			opponent.setAttackFrames(down);
		}
		break;
	case left:
		setAttackFrames(left);
		if(rangeOfAttack <= opponent.getRange()){
			opponent.setAttackFrames(right);
		}
		break;
	case down:
		setAttackFrames(down);
		if(rangeOfAttack <= opponent.getRange()){
			opponent.setAttackFrames(up);
		}
		break;
	case right:
		setAttackFrames(right);
		if(rangeOfAttack <= opponent.getRange()){
			opponent.setAttackFrames(left);
		}
		break;
	}
	if(getFrameCounter() > INFANTRY_ANIMATION_DELAY*12){
		audio->playCue(ARCHER_ATTACK);
		setFrameCounter(0);
		if(rangeOfAttack <= opponent.getRange()){
			setHP(getHP()-opponent.getDamage()/getDef());
		}
		opponent.setHP(opponent.getHP()-getDamage()/opponent.getDef());
		setAnimating(false);
		opponent.setAnimating(false);
	}
	setFrameCounter(getFrameCounter()+frameTime);
}

bool Longbowman::kill(float frameTime){
	setAnimating(true);
	switch(getLastDirection()){
	case up:
		setFrames(LONGBOWMAN_DEATH_UP_START, LONGBOWMAN_DEATH_UP_END);
		break;
	case left:
		setFrames(LONGBOWMAN_DEATH_LEFT_START, LONGBOWMAN_DEATH_LEFT_END);
		break;
	case down:
		setFrames(LONGBOWMAN_DEATH_DOWN_START, LONGBOWMAN_DEATH_DOWN_END);
		break;
	case right:
		setFrames(LONGBOWMAN_DEATH_RIGHT_START, LONGBOWMAN_DEATH_RIGHT_END);
		break;
	}
	if(!getActive()){
		return true;
	}
	if(getFrameCounter() > LONGBOWMAN_ANIMATION_DELAY*11){
		setFrameCounter(0);
		setVisible(false);
		setActive(false);
		setAnimating(false);
		return true;
	}
	setFrameCounter(getFrameCounter()+frameTime);
	return false;
}

bool Longbowman::moveUp(Audio* audio){
	audio->playCue(INFANTRY_MOVE);
	setLastDirection(up);
	setFrames(LONGBOWMAN_RUN_UP_START, LONGBOWMAN_RUN_UP_END);
	setVelocity(VECTOR2(0, -1));
	if(getY() < (getTileY()-1)*TERRAIN_HEIGHT){
		setTile(getTileX(), getTileY()-1);
		setVelocity(VECTOR2(0, 0));
		setY(getTileY()*TERRAIN_HEIGHT);
		setMovementLeft(getMovementLeft()-1);
		audio->stopCue(INFANTRY_MOVE);
		return true;
	}
	return false;
}
bool Longbowman::moveDown(Audio* audio){
	audio->playCue(INFANTRY_MOVE);
	setLastDirection(down);
	setFrames(LONGBOWMAN_RUN_DOWN_START, LONGBOWMAN_RUN_DOWN_END);
	setVelocity(VECTOR2(0, 1));
	if(getY() > (getTileY()+1)*TERRAIN_HEIGHT){
		setTile(getTileX(), getTileY()+1);
		setVelocity(VECTOR2(0, 0));
		setY(getTileY()*TERRAIN_HEIGHT);
		setMovementLeft(getMovementLeft()-1);
		audio->stopCue(INFANTRY_MOVE);
		return true;
	}
	return false;
}
bool Longbowman::moveLeft(Audio* audio){
	audio->playCue(INFANTRY_MOVE);
	setLastDirection(left);
	setFrames(LONGBOWMAN_RUN_LEFT_START, LONGBOWMAN_RUN_LEFT_END);
	setVelocity(VECTOR2(-1, 0));
	if(getX() < (getTileX()-1)*TERRAIN_WIDTH){
		setTile(getTileX()-1, getTileY());
		setVelocity(VECTOR2(0, 0));
		setX(getTileX()*TERRAIN_HEIGHT);
		setMovementLeft(getMovementLeft()-1);
		audio->stopCue(INFANTRY_MOVE);
		return true;
	}
	return false;
}
bool Longbowman::moveRight(Audio* audio){
	audio->playCue(INFANTRY_MOVE);
	setLastDirection(right);
	setFrames(LONGBOWMAN_RUN_RIGHT_START, LONGBOWMAN_RUN_RIGHT_END);
	setVelocity(VECTOR2(1, 0));
	if(getX() > (getTileX()+1)*TERRAIN_WIDTH){
		setTile(getTileX()+1, getTileY());
		setVelocity(VECTOR2(0, 0));
		setX(getTileX()*TERRAIN_HEIGHT);
		setMovementLeft(getMovementLeft()-1);
		audio->stopCue(INFANTRY_MOVE);
		return true;
	}
	return false;
}

void Longbowman::setAttackFrames(LastDirection direction){
	if(direction == up){
		setFrames(LONGBOWMAN_ATTACK_UP_START, LONGBOWMAN_ATTACK_UP_END);
		setLastDirection(up);
		setAnimating(true);
	}
	else if(direction == down){
		setFrames(LONGBOWMAN_ATTACK_DOWN_START, LONGBOWMAN_ATTACK_DOWN_END);
		setLastDirection(down);
		setAnimating(true);
	}
	else if(direction == left){
		setFrames(LONGBOWMAN_ATTACK_LEFT_START, LONGBOWMAN_ATTACK_LEFT_END);
		setLastDirection(left);
		setAnimating(true);
	}
	if(direction == right){
		setFrames(LONGBOWMAN_ATTACK_RIGHT_START, LONGBOWMAN_ATTACK_RIGHT_END);
		setLastDirection(right);
		setAnimating(true);
	}
}
