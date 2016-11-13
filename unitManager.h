#pragma once
#include "entity.h"
#include "infantry.h"

#pragma region Newell
class UnitManager
{
public:
	UnitManager();
	~UnitManager();
	bool initialize(Game *gamePtr, Graphics* graphics);
private:
	TextureManager infantryTexture;
	TextureManager infantryTexture2;
	Infantry* player1Infantry;
	Infantry* player2Infantry;
};
#pragma endregion
