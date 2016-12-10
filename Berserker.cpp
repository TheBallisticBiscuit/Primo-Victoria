#pragma region Higgs
#include "Berserker.h"


Berserker::Berserker(void)
{
}

Berserker::~Berserker(void)
{
}

bool Berserker::initialize(int width, int height, int ncols, int team, TextureManager* textureM, Game* game){
	bool ret = Unit::initialize(height, width, ncols, team, textureM, game);
	setScale(BERSERKER_SCALING);
	setMovementPerTurn(3);
	setMovementLeft(0);
	setRange(1);
	setHP(60);
	setDef(1);
	setDamage(20);
	//bloodRage = 0;
	setTeam(team);
	setFrameDelay(BERSERKER_ANIMATION_DELAY);
	setFrameCounter(0);
	setVelocity(VECTOR2(0, 0));
	
	return ret;
}

void Berserker::update(float frameTime){
	if(velocity.x == 0 && velocity.y == 0 && !isAnimating()){
		switch(getLastDirection()){
		case up:
			setFrames(BERSERKER_IDLE_UP_START, BERSERKER_IDLE_UP_END);
			break;
		case left:
			setFrames(BERSERKER_IDLE_LEFT_START, BERSERKER_IDLE_LEFT_END);
			break;
		case down:
			setFrames(BERSERKER_IDLE_DOWN_START, BERSERKER_IDLE_DOWN_END);
			break;
		case right:
			setFrames(BERSERKER_IDLE_RIGHT_START, BERSERKER_IDLE_RIGHT_END);
			break;
		}
	}
	setX(getX()+getVelocity().x*BERSERKER_SPEED*frameTime);
	setY(getY()+getVelocity().y*BERSERKER_SPEED*frameTime);	
	Entity::update(frameTime);
}

void Berserker::fight(Unit& opponent, float frameTime, Audio* audio){
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
	if(getFrameCounter() > BERSERKER_ANIMATION_DELAY*10){
		audio->playCue(BERSERKER_ATTACK);					//TODO: Add cue
		setFrameCounter(0);
		setHP(getHP()-opponent.getDamage()/getDef());
		opponent.setHP(opponent.getHP()-getDamage()/opponent.getDef());
		setAnimating(false);
		opponent.setAnimating(false);
	}
	setFrameCounter(getFrameCounter()+frameTime);
}

bool Berserker::kill(float frameTime){
	switch(getLastDirection()){
	case up:
		setFrames(BERSERKER_DEATH_UP_START, BERSERKER_DEATH_UP_END);
		break;
	case left:
		setFrames(BERSERKER_DEATH_LEFT_START, BERSERKER_DEATH_LEFT_END);
		break;
	case down:
		setFrames(BERSERKER_DEATH_DOWN_START, BERSERKER_DEATH_DOWN_END);
		break;
	case right:
		setFrames(BERSERKER_DEATH_RIGHT_START, BERSERKER_DEATH_RIGHT_END);
		break;
	}
	if(!getActive()){
		return true;
	}
	setAnimating(true);
	if(getFrameCounter() > BERSERKER_ANIMATION_DELAY*6){
		setFrameCounter(0);
		setVisible(false);
		setActive(false);
		setAnimating(false);
		return true;
	}
	setFrameCounter(getFrameCounter()+frameTime);
	return false;
}

bool Berserker::moveUp(Audio* audio){
	setLastDirection(up);
	audio->playCue(BERSERKER_MOVE);
	setFrames(BERSERKER_RUN_UP_START, BERSERKER_RUN_UP_END);
	setVelocity(VECTOR2(0, -1));
	if(getY() < (getTileY()-1)*TERRAIN_HEIGHT){
		setTile(getTileX(), getTileY()-1);
		setVelocity(VECTOR2(0, 0));
		setY(getTileY()*TERRAIN_HEIGHT);
		setMovementLeft(getMovementLeft()-1);
		audio->stopCue(BERSERKER_MOVE);
		return true;
	}
	return false;
}
bool Berserker::moveDown(Audio* audio){
	setLastDirection(down);
	audio->playCue(BERSERKER_MOVE);
	setFrames(BERSERKER_RUN_DOWN_START, BERSERKER_RUN_DOWN_END);
	setVelocity(VECTOR2(0, 1));
	if(getY() > (getTileY()+1)*TERRAIN_HEIGHT){
		setTile(getTileX(), getTileY()+1);
		setVelocity(VECTOR2(0, 0));
		setY(getTileY()*TERRAIN_HEIGHT);
		setMovementLeft(getMovementLeft()-1);
		audio->stopCue(BERSERKER_MOVE);
		return true;
	}
	return false;
}
bool Berserker::moveLeft(Audio* audio){
	setLastDirection(left);
	audio->playCue(BERSERKER_MOVE);
	setFrames(BERSERKER_RUN_LEFT_START, BERSERKER_RUN_LEFT_END);
	setVelocity(VECTOR2(-1, 0));
	if(getX() < (getTileX()-1)*TERRAIN_WIDTH){
		setTile(getTileX()-1, getTileY());
		setVelocity(VECTOR2(0, 0));
		setX(getTileX()*TERRAIN_HEIGHT);
		setMovementLeft(getMovementLeft()-1);
		audio->stopCue(BERSERKER_MOVE);
		return true;
	}
	return false;
}
bool Berserker::moveRight(Audio* audio){
	setLastDirection(right);
	audio->playCue(BERSERKER_MOVE);
	setFrames(BERSERKER_RUN_RIGHT_START, BERSERKER_RUN_RIGHT_END);
	setVelocity(VECTOR2(1, 0));
	if(getX() > (getTileX()+1)*TERRAIN_WIDTH){
		setTile(getTileX()+1, getTileY());
		setVelocity(VECTOR2(0, 0));
		setX(getTileX()*TERRAIN_HEIGHT);
		setMovementLeft(getMovementLeft()-1);
		audio->stopCue(BERSERKER_MOVE);
		return true;
	}
	return false;
}

void Berserker::setAttackFrames(LastDirection direction){
	if(direction == up){
		setFrames(BERSERKER_ATTACK_UP_START, BERSERKER_ATTACK_UP_END);
		setLastDirection(up);
		setAnimating(true);
	}
	else if(direction == down){
		setFrames(BERSERKER_ATTACK_DOWN_START, BERSERKER_ATTACK_DOWN_END);
		setLastDirection(down);
		setAnimating(true);
	}
	else if(direction == left){
		setFrames(BERSERKER_ATTACK_LEFT_START, BERSERKER_ATTACK_LEFT_END);
		setLastDirection(left);
		setAnimating(true);
	}
	if(direction == right){
		setFrames(BERSERKER_ATTACK_RIGHT_START, BERSERKER_ATTACK_RIGHT_END);
		setLastDirection(right);
		setAnimating(true);
	}
}

void Berserker::setHP(int newHP){
	if(newHP < Unit::getHP()){ //damage being dealt
		if(getHP() > 1 && newHP <= 0){ //dying from higher than 1 HP, survives
			Unit::setHP(1);
			return;
		}
	}
	Unit::setHP(newHP);
}
#pragma endregion