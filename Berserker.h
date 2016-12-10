#pragma once
#pragma region Higgs
#include "unit.h"
class Berserker : public Unit
{
public:
	Berserker(void);
	~Berserker(void);

	bool initialize(int width, int height, int ncols, int team, TextureManager* textureM, Game* game);
	void update(float frameTime);
	void fight(Unit& opponent, float frameTime, Audio* audio);
	bool kill(float frameTime);
	bool moveUp(Audio* audio);
	bool moveDown(Audio* audio);
	bool moveLeft(Audio* audio);
	bool moveRight(Audio* audio);
	void setAttackFrames(LastDirection direction);
	void setHP(int newHP);
//private:
	//bool bloodRage;
};
#pragma endregion