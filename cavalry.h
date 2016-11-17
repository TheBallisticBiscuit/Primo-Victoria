#pragma once
#include "unit.h"
class Cavalry :
	public Unit
{
public:
	Cavalry(void);
	~Cavalry(void);
	bool initialize(int width, int height, int ncols, int team, TextureManager* textureM, Game* game);
	void update(float frameTime);
	void fight(Unit& opponent, float frameTime);
	bool kill(float frameTime);
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();
	void setAttackFrames(LastDirection direction);
private:
};

