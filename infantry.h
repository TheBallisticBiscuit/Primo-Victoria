#pragma once
#pragma region Newell
#include "unit.h"
class Infantry : public Unit
{
public:
	Infantry(void);
	~Infantry(void);
	bool initialize(int width, int height, int ncols, TextureManager* textureM, Game* game);
	void update(float frameTime);
	void fight(Unit& opponent, float frameTime);
	bool kill(float frameTime);
private:
};
#pragma endregion

