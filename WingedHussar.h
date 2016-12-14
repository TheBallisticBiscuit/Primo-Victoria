#pragma once
#pragma region Higgs
#include "unit.h"
class WingedHussar : public Unit
{
public:
	WingedHussar(void);
	~WingedHussar(void);

	bool initialize(int width, int height, int ncols, int team, TextureManager* textureM, Game* game);
	void update(float frameTime);
	void fight(Unit& opponent, float frameTime, Audio* audio, int rangeOfAttack);
	bool kill(float frameTime);
	bool moveUp(Audio* audio);
	bool moveDown(Audio* audio);
	bool moveLeft(Audio* audio);
	bool moveRight(Audio* audio);
	void setAttackFrames(LastDirection direction);
};
#pragma endregion