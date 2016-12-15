#pragma once
#pragma region Newell
#include "unit.h"
class Infantry : public Unit
{
public:
	Infantry(void);
	~Infantry(void);

	bool initialize(int width, int height, int ncols, int team, TextureManager* textureM, Game* game);
	void update(float frameTime);
	void fight(Unit& opponent, float frameTime, Audio* audio, int rangeOfAttack, ParticleManager* pm);
	bool kill(float frameTime);
	bool moveUp(Audio* audio);
	bool moveDown(Audio* audio);
	bool moveLeft(Audio* audio);
	bool moveRight(Audio* audio);
	void setAttackFrames(LastDirection direction);
private:
};
#pragma endregion

