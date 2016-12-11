#pragma region Higgs
#include "WingedHussar.h"


WingedHussar::WingedHussar(void)
{
}


WingedHussar::~WingedHussar(void)
{
}

bool WingedHussar::initialize(int width, int height, int ncols, int team, TextureManager* textureM, Game* game){
	setScale(HUSSAR_SCALING);
	setMovementPerTurn(6);
	setMovementLeft(0);
	setRange(1);
	setHP(35);
	setDef(1);
	setSpecial(1);
	setDamage(25);
	setTeam(team);
	setFrameDelay(HUSSAR_ANIMATION_DELAY);
	setFrameCounter(0);
	setVelocity(VECTOR2(0, 0));
	return Unit::initialize(width, height, ncols, team, textureM, game);
}

void WingedHussar::update(float frameTime){
	if(velocity.x == 0 && velocity.y == 0 && !isAnimating()){
		switch(getLastDirection()){
		case up:
			setFrames(HUSSAR_IDLE_UP_START, HUSSAR_IDLE_UP_END);
			break;
		case left:
			setFrames(HUSSAR_IDLE_LEFT_START, HUSSAR_IDLE_LEFT_END);
			break;
		case down:
			setFrames(HUSSAR_IDLE_DOWN_START, HUSSAR_IDLE_DOWN_END);
			break;
		case right:
			setFrames(HUSSAR_IDLE_RIGHT_START, HUSSAR_IDLE_RIGHT_END);
			break;
		}
	}
	setX(getX()+getVelocity().x*HUSSAR_SPEED*frameTime);
	setY(getY()+getVelocity().y*HUSSAR_SPEED*frameTime);
	Entity::update(frameTime);
}

void WingedHussar::fight(Unit& opponent, float frameTime, Audio* audio){
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

	//TODO: Add in special ability

	setFrameCounter(getFrameCounter()+frameTime);
	if(getFrameCounter() > INFANTRY_ANIMATION_DELAY*12){
		setFrameCounter(0);
		audio->playCue(HUSSAR_ATTACK);
		setHP(getHP()-opponent.getDamage()/getDef());
		opponent.setHP(opponent.getHP()-getDamage()/opponent.getDef());
		setAnimating(false);
		opponent.setAnimating(false);
	}
}

void WingedHussar::fight(Unit& opponent, float frameTime, Audio* audio, TileManager* tileManager){
	//counter = 0;
	switch (getLastDirection()) {
	case up:
		if (opponent.getTileY() == 0){
			fight(opponent, frameTime, audio);
			return;
		}
		if (tileManager->getTile(opponent.getTileX(),opponent.getTileY()-1)->isOccupied()){
			fight(opponent, frameTime, audio);
			return;
		}
		else  
			break;

		/*while (opponent.getTileY() - counter > 0) {
			if (tileManager->getTile(opponent.getTileX(), opponent.getTileY() - (counter+1))->isOccupied &&
				tileManager->getTile(opponent.getTileX(), opponent.getTileY() - (counter+1))->getUnit()->getTeam() == getTeam()){
				fight(opponent, frameTime, audio);
				counter = 0;
				return;
			}
			else if (tileManager->getTile(getX()*84, opponent.getTileY() - (counter+1))->isOccupied &&
				tileManager->getTile(getX()*84, opponent.getTileY() - (counter+1))->getUnit()->getTeam() != getTeam()){
				counter++;
			}
			else
				counter++;
				break;
		}
		break;*/
	default:
		fight(opponent, frameTime, audio);
		return;
		break;
	}

	switch (getLastDirection())
	{
	case up:
		setSpecial(1);
		moveUp(audio);
		opponent.setHP(opponent.getHP() - getDamage());
	default:
		break;
	}
}


bool WingedHussar::kill(float frameTime){
	switch(getLastDirection()){
	case up:
		setFrames(HUSSAR_DEATH_UP_START, HUSSAR_DEATH_UP_END);
		break;
	case left:
		setFrames(HUSSAR_DEATH_LEFT_START, HUSSAR_DEATH_LEFT_END);
		break;
	case down:
		setFrames(HUSSAR_DEATH_DOWN_START, HUSSAR_DEATH_DOWN_END);
		break;
	case right:
		setFrames(HUSSAR_DEATH_RIGHT_START, HUSSAR_DEATH_RIGHT_END);
		break;
	}
	if(!getActive()){
		return true;
	}
	setAnimating(true);
	if(getFrameCounter() > HUSSAR_ANIMATION_DELAY*6){
		setFrameCounter(0);
		setVisible(false);
		setActive(false);
		setAnimating(false);
		return true;
	}
	setFrameCounter(getFrameCounter()+frameTime);
	return false;
}

bool WingedHussar::moveUp(Audio* audio){
	audio->playCue(HUSSAR_MOVE);
	setLastDirection(up);
	setFrames(HUSSAR_RUN_UP_START, HUSSAR_RUN_UP_END);
	setVelocity(VECTOR2(0, -1));
	if(getY() < (getTileY()-1)*TERRAIN_HEIGHT){
		setTile(getTileX(), getTileY()-1);
		setY(getTileY()*TERRAIN_HEIGHT);
		setMovementLeft(getMovementLeft()-1);
		if (getSpecial() == 1){
			setSpecial(0);
			return false;
		}
		setVelocity(VECTOR2(0, 0));
		audio->stopCue(HUSSAR_MOVE);
		return true;
	}
	return false;
}

bool WingedHussar::moveDown(Audio* audio){
	audio->playCue(HUSSAR_MOVE);
	setLastDirection(down);
	setFrames(HUSSAR_RUN_DOWN_START, HUSSAR_RUN_DOWN_END);
	setVelocity(VECTOR2(0, 1));
	if(getY() > (getTileY()+1)*TERRAIN_HEIGHT){
		setTile(getTileX(), getTileY()+1);
		setVelocity(VECTOR2(0, 0));
		setY(getTileY()*TERRAIN_HEIGHT);
		setMovementLeft(getMovementLeft()-1);
		audio->stopCue(HUSSAR_MOVE);
		return true;
	}
	return false;
}

bool WingedHussar::moveLeft(Audio* audio){
	audio->playCue(HUSSAR_MOVE);
	setLastDirection(left);
	setFrames(HUSSAR_RUN_LEFT_START, HUSSAR_RUN_LEFT_END);
	setVelocity(VECTOR2(-1, 0));
	if(getX() < (getTileX()-1)*TERRAIN_WIDTH){
		setTile(getTileX()-1, getTileY());
		setVelocity(VECTOR2(0, 0));
		setX(getTileX()*TERRAIN_HEIGHT);
		setMovementLeft(getMovementLeft()-1);
		audio->stopCue(HUSSAR_MOVE);
		return true;
	}
	return false;
}

bool WingedHussar::moveRight(Audio* audio){
	audio->playCue(HUSSAR_MOVE);
	setLastDirection(right);
	setFrames(HUSSAR_RUN_RIGHT_START, HUSSAR_RUN_RIGHT_END);
	setVelocity(VECTOR2(1, 0));
	if(getX() > (getTileX()+1)*TERRAIN_WIDTH){
		setTile(getTileX()+1, getTileY());
		setVelocity(VECTOR2(0, 0));
		setX(getTileX()*TERRAIN_HEIGHT);
		setMovementLeft(getMovementLeft()-1);
		audio->stopCue(HUSSAR_MOVE);
		return true;
	}
	return false;
}

void WingedHussar::setAttackFrames(LastDirection direction){
	if(direction == up){
		setFrames(HUSSAR_ATTACK_UP_START, HUSSAR_ATTACK_UP_END);
		setLastDirection(up);
		setAnimating(true);
	}
	else if(direction == down){
		setFrames(HUSSAR_ATTACK_DOWN_START, HUSSAR_ATTACK_DOWN_END);
		setLastDirection(down);
		setAnimating(true);
	}
	else if(direction == left){
		setFrames(HUSSAR_ATTACK_LEFT_START, HUSSAR_ATTACK_LEFT_END);
		setLastDirection(left);
		setAnimating(true);
	}
	if(direction == right){
		setFrames(HUSSAR_ATTACK_RIGHT_START, HUSSAR_ATTACK_RIGHT_END);
		setLastDirection(right);
		setAnimating(true);
	}
}
#pragma endregion