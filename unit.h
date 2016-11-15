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
	void setDamage(int newDamage);
	void setHP(int newHP);
	void setMovementPerTurn(int newMovement);
	void setMovementLeft(int newMovement);
	void setRange(int newRange);
	void setTile(int x, int y);
	void setFrameCounter(float newFrameCounter);
	virtual void fight(Unit& opponent, float frameTime){}
	virtual bool kill(float frameTime){return true;}
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
	float frameCounter;
};
#pragma endregion
