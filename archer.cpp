#include "archer.h"


Archer::Archer(void)
{
}


Archer::~Archer(void)
{
}

bool Archer::initialize(int width, int height, int ncols, int team, TextureManager* textureM, Game* game){
	setScale(ARCHER_SCALING);
	setMovementPerTurn(3);
	setMovementLeft(0);
	setRange(2);
	setHP(25);
	setDef(1);
	setSpecial(0);
	setDamage(30);
	setTeam(team);
	setFrameDelay(ARCHER_ANIMATION_DELAY);
	setFrameCounter(0);
	setVelocity(VECTOR2(0, 0));
	return Unit::initialize(width, height, ncols, textureM, game);
}

void Archer::update(float frameTime){
	if(velocity.x == 0 && velocity.y == 0 && !isAnimating()){
		switch(getLastDirection()){
		case up:
			setFrames(ARCHER_IDLE_UP_START, ARCHER_IDLE_UP_END);
			break;
		case left:
			setFrames(ARCHER_IDLE_LEFT_START, ARCHER_IDLE_LEFT_END);
			break;
		case down:
			setFrames(ARCHER_IDLE_DOWN_START, ARCHER_IDLE_DOWN_END);
			break;
		case right:
			setFrames(ARCHER_IDLE_RIGHT_START, ARCHER_IDLE_RIGHT_END);
			break;
		}
	}
	setX(getX()+getVelocity().x*ARCHER_SPEED*frameTime);
	setY(getY()+getVelocity().y*ARCHER_SPEED*frameTime);
	Entity::update(frameTime);
}

void Archer::fight(Unit& opponent, float frameTime, Audio* audio){

	switch(getLastDirection()){
	case up:
		setAttackFrames(up);
		if(getRange() <= opponent.getRange()){
			opponent.setAttackFrames(down);
		}
		break;
	case left:
		setAttackFrames(left);
		if(getRange() <= opponent.getRange()){
			opponent.setAttackFrames(right);
		}
		break;
	case down:
		setAttackFrames(down);
		if(getRange() <= opponent.getRange()){
			opponent.setAttackFrames(up);
		}
		break;
	case right:
		setAttackFrames(right);
		if(getRange() <= opponent.getRange()){
			opponent.setAttackFrames(left);
		}
		break;
	}
	if(getFrameCounter() > INFANTRY_ANIMATION_DELAY*12){
		audio->playCue(ARCHER_ATTACK);
		setFrameCounter(0);
		if(getRange() <= opponent.getRange()){
			setHP(getHP()-opponent.getDamage()/getDef());
		}
		opponent.setHP(opponent.getHP()-getDamage()/opponent.getDef());
		setAnimating(false);
		opponent.setAnimating(false);
	}
	setFrameCounter(getFrameCounter()+frameTime);
}

bool Archer::kill(float frameTime){
	switch(getLastDirection()){
	case up:
		setFrames(ARCHER_DEATH_UP_START, ARCHER_DEATH_UP_END);
		break;
	case left:
		setFrames(ARCHER_DEATH_LEFT_START, ARCHER_DEATH_LEFT_END);
		break;
	case down:
		setFrames(ARCHER_DEATH_DOWN_START, ARCHER_DEATH_DOWN_END);
		break;
	case right:
		setFrames(ARCHER_DEATH_RIGHT_START, ARCHER_DEATH_RIGHT_END);
		break;
	}
	if(!getActive()){
		return true;
	}
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

bool Archer::moveUp(Audio* audio){
	audio->playCue(INFANTRY_MOVE);
	setLastDirection(up);
	setFrames(ARCHER_RUN_UP_START, ARCHER_RUN_UP_END);
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
bool Archer::moveDown(Audio* audio){
	audio->playCue(INFANTRY_MOVE);
	setLastDirection(down);
	setFrames(ARCHER_RUN_DOWN_START, ARCHER_RUN_DOWN_END);
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
bool Archer::moveLeft(Audio* audio){
	audio->playCue(INFANTRY_MOVE);
	setLastDirection(left);
	setFrames(ARCHER_RUN_LEFT_START, ARCHER_RUN_LEFT_END);
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
bool Archer::moveRight(Audio* audio){
	audio->playCue(INFANTRY_MOVE);
	setLastDirection(right);
	setFrames(ARCHER_RUN_RIGHT_START, ARCHER_RUN_RIGHT_END);
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

void Archer::setAttackFrames(LastDirection direction){
	if(direction == up){
		setFrames(ARCHER_ATTACK_UP_START, ARCHER_ATTACK_UP_END);
		setLastDirection(up);
		setAnimating(true);
	}
	else if(direction == down){
		setFrames(ARCHER_ATTACK_DOWN_START, ARCHER_ATTACK_DOWN_END);
		setLastDirection(down);
		setAnimating(true);
	}
	else if(direction == left){
		setFrames(ARCHER_ATTACK_LEFT_START, ARCHER_ATTACK_LEFT_END);
		setLastDirection(left);
		setAnimating(true);
	}
	if(direction == down){
		setFrames(ARCHER_ATTACK_DOWN_START, ARCHER_ATTACK_DOWN_END);
		setLastDirection(up);
		setAnimating(true);
	}
}