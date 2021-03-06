#include "cavalry.h"


Cavalry::Cavalry(void)
{
}


Cavalry::~Cavalry(void)
{
}

bool Cavalry::initialize(int width, int height, int ncols, int team, TextureManager* textureM, Game* game){
	setScale(CAVALRY_SCALING);
	setMovementPerTurn(6);
	setMovementLeft(0);
	setRange(1);
	setHP(35);
	setDef(1);
	setSpecial(0);
	setDamage(25);
	setTeam(team);
	setFrameDelay(CAVALRY_ANIMATION_DELAY);
	setFrameCounter(0);
	setVelocity(VECTOR2(0, 0));

	return Unit::initialize(width, height, ncols, team, textureM, game);
}

void Cavalry::update(float frameTime){
	if(velocity.x == 0 && velocity.y == 0 && !isAnimating()){
		switch(getLastDirection()){
		case up:
			setFrames(CAVALRY_IDLE_UP_START, CAVALRY_IDLE_UP_END);
			break;
		case left:
			setFrames(CAVALRY_IDLE_LEFT_START, CAVALRY_IDLE_LEFT_END);
			break;
		case down:
			setFrames(CAVALRY_IDLE_DOWN_START, CAVALRY_IDLE_DOWN_END);
			break;
		case right:
			setFrames(CAVALRY_IDLE_RIGHT_START, CAVALRY_IDLE_RIGHT_END);
			break;
		}
	}
	setX(getX()+getVelocity().x*CAVALRY_SPEED*frameTime);
	setY(getY()+getVelocity().y*CAVALRY_SPEED*frameTime);
	Entity::update(frameTime);
}

void Cavalry::fight(Unit& opponent, float frameTime, Audio* audio, int rangeOfAttack, ParticleManager* pm){
	switch(getLastDirection()){
	case up:
		setAttackFrames(up);
		opponent.setAttackFrames(down);
		break;
	case left:
		setAttackFrames(left);
		opponent.setAttackFrames(right);
		break;
	case down:
		setAttackFrames(down);
		opponent.setAttackFrames(up);
		break;
	case right:
		setAttackFrames(right);
		opponent.setAttackFrames(left);
		break;
	}
	setFrameCounter(getFrameCounter()+frameTime);
	if(getFrameCounter() > INFANTRY_ANIMATION_DELAY*12){
		pm->setFrames(BLOOD_SPLATTER_START, BLOOD_SPLATTER_END);
		pm->setRotation(0);
		pm->setFade(1);
		pm->createParticleEffect(VECTOR2(opponent.getX()+10, opponent.getY()+10), VECTOR2(0, 0), BLOOD_PARTICLES, true);
		pm->createParticleEffect(VECTOR2(getX()+10, getY()+10), VECTOR2(0, 0), BLOOD_PARTICLES, true);
		setFrameCounter(0);
		audio->playCue(CAVALRY_ATTACK);
		setHP(getHP()-opponent.getDamage()/getDef());
		opponent.setHP(opponent.getHP()-getDamage()/opponent.getDef());
		setAnimating(false);
		opponent.setAnimating(false);
	}

}

bool Cavalry::kill(float frameTime){
	switch(getLastDirection()){
	case up:
		setFrames(CAVALRY_DEATH_UP_START, CAVALRY_DEATH_UP_END);
		break;
	case left:
		setFrames(CAVALRY_DEATH_LEFT_START, CAVALRY_DEATH_LEFT_END);
		break;
	case down:
		setFrames(CAVALRY_DEATH_DOWN_START, CAVALRY_DEATH_DOWN_END);
		break;
	case right:
		setFrames(CAVALRY_DEATH_RIGHT_START, CAVALRY_DEATH_RIGHT_END);
		break;
	}
	if(!getActive()){
		return true;
	}
	setAnimating(true);
	if(getFrameCounter() > CAVALRY_ANIMATION_DELAY*6){
		setFrameCounter(0);
		setVisible(false);
		setActive(false);
		setAnimating(false);
		return true;
	}
	setFrameCounter(getFrameCounter()+frameTime);
	return false;
}

bool Cavalry::moveUp(Audio* audio){
	audio->playCue(CAVALRY_MOVE);
	setLastDirection(up);
	setFrames(CAVALRY_RUN_UP_START, CAVALRY_RUN_UP_END);
	setVelocity(VECTOR2(0, -1));
	if(getY() < (getTileY()-1)*TERRAIN_HEIGHT){
		setTile(getTileX(), getTileY()-1);
		setVelocity(VECTOR2(0, 0));
		setY(getTileY()*TERRAIN_HEIGHT);
		setMovementLeft(getMovementLeft()-1);
		audio->stopCue(CAVALRY_MOVE);
		return true;
	}
	return false;
}

bool Cavalry::moveDown(Audio* audio){
	audio->playCue(CAVALRY_MOVE);
	setLastDirection(down);
	setFrames(CAVALRY_RUN_DOWN_START, CAVALRY_RUN_DOWN_END);
	setVelocity(VECTOR2(0, 1));
	if(getY() > (getTileY()+1)*TERRAIN_HEIGHT){
		setTile(getTileX(), getTileY()+1);
		setVelocity(VECTOR2(0, 0));
		setY(getTileY()*TERRAIN_HEIGHT);
		setMovementLeft(getMovementLeft()-1);
		audio->stopCue(CAVALRY_MOVE);
		return true;
	}
	return false;
}

bool Cavalry::moveLeft(Audio* audio){
	audio->playCue(CAVALRY_MOVE);
	setLastDirection(left);
	setFrames(CAVALRY_RUN_LEFT_START, CAVALRY_RUN_LEFT_END);
	setVelocity(VECTOR2(-1, 0));
	if(getX() < (getTileX()-1)*TERRAIN_WIDTH){
		setTile(getTileX()-1, getTileY());
		setVelocity(VECTOR2(0, 0));
		setX(getTileX()*TERRAIN_HEIGHT);
		setMovementLeft(getMovementLeft()-1);
		audio->stopCue(CAVALRY_MOVE);
		return true;
	}
	return false;
}

bool Cavalry::moveRight(Audio* audio){
	audio->playCue(CAVALRY_MOVE);
	setLastDirection(right);
	setFrames(CAVALRY_RUN_RIGHT_START, CAVALRY_RUN_RIGHT_END);
	setVelocity(VECTOR2(1, 0));
	if(getX() > (getTileX()+1)*TERRAIN_WIDTH){
		setTile(getTileX()+1, getTileY());
		setVelocity(VECTOR2(0, 0));
		setX(getTileX()*TERRAIN_HEIGHT);
		setMovementLeft(getMovementLeft()-1);
		audio->stopCue(CAVALRY_MOVE);
		return true;
	}
	return false;
}

void Cavalry::setAttackFrames(LastDirection direction){
	if(direction == up){
		setFrames(CAVALRY_ATTACK_UP_START, CAVALRY_ATTACK_UP_END);
		setLastDirection(up);
		setAnimating(true);
	}
	else if(direction == down){
		setFrames(CAVALRY_ATTACK_DOWN_START, CAVALRY_ATTACK_DOWN_END);
		setLastDirection(down);
		setAnimating(true);
	}
	else if(direction == left){
		setFrames(CAVALRY_ATTACK_LEFT_START, CAVALRY_ATTACK_LEFT_END);
		setLastDirection(left);
		setAnimating(true);
	}
	if(direction == right){
		setFrames(CAVALRY_ATTACK_RIGHT_START, CAVALRY_ATTACK_RIGHT_END);
		setLastDirection(right);
		setAnimating(true);
	}
}