#pragma once
#include "entity.h"
#pragma region Newell
class Unit : public Entity {
public:
	Unit();
	~Unit();
	bool initialize(int height, int width, int ncols, TextureManager* textureM, Game* game);
	int getDamage(){return damage;}
	int getHP(){return HP;}
	int getRange(){return range;}
	int getMovementLeft(){return movementLeft;}
	int getMovement(){return movementPerTurn;}
	int getSpecial(){return specialAbility;}
	float getFrameCounter(){return frameCounter;}
	float getDef(){return defence;}
	enum LastDirection {up, down, left, right} getLastDirection(){return lastDirection;}
	int getTileX(){return tile.x;}
	int getTileY(){return tile.y;}
	int getTeam() {return team; };
	bool isAnimating(){return animating;}
	void setDamage(int newDamage);
	void setHP(int newHP);
	void setDef(float newDefence);
	void setMovementPerTurn(int newMovement);
	void setMovementLeft(int newMovement);
	void setSpecial(int newSpecial);
	void setRange(int newRange);
	void setTile(int x, int y);
	void setTeam(int t) {team = t; };
	void setFrameCounter(float newFrameCounter);
	void setAnimating(bool newBool);
	void setLastDirection(LastDirection newDirection);
	virtual void fight(Unit& opponent, float frameTime, Audio* audio){}
	virtual bool kill(float frameTime){return true;}
	virtual bool moveUp(Audio* audio){return false;}
	virtual bool moveDown(Audio* audio){return false;}
	virtual bool moveLeft(Audio* audio){return false;}
	virtual bool moveRight(Audio* audio){return false;}
	virtual void setAttackFrames(LastDirection direction){}
private:
	int damage;
	int HP;
	float defence;
	int range;
	int team;
	int specialAbility;
	struct pair{
		int x;
		int y;
	} tile;
	int movementPerTurn;
	int movementLeft;
	LastDirection lastDirection;
	float frameCounter;
	bool animating;
};
#pragma endregion
