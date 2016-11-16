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
	int getMovement(){return movementLeft;}
	float getFrameCounter(){return frameCounter;}
	enum LastDirection {up, down, left, right} getLastDirection(){return lastDirection;}
	int getTileX(){return tile.x;}
	int getTileY(){return tile.y;}
	bool isAnimating(){return animating;}
	void setDamage(int newDamage);
	void setHP(int newHP);
	void setMovementPerTurn(int newMovement);
	void setMovementLeft(int newMovement);
	void setRange(int newRange);
	void setTile(int x, int y);
	void setFrameCounter(float newFrameCounter);
	void setAnimating(bool newBool);
	void setLastDirection(LastDirection newDirection);
	virtual void fight(Unit& opponent, float frameTime){}
	virtual bool kill(float frameTime){return true;}
	virtual bool moveUp(){return true;}
	virtual bool moveDown(){return true;}
	virtual bool moveLeft(){return true;}
	virtual bool moveRight(){return true;}
private:
	int damage;
	int HP;
	int range;
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
