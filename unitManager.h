#pragma once
#include "entity.h"
#include "infantry.h"

#pragma region Newell
class UnitManager
{
public:
	UnitManager();
	~UnitManager();
	void initialize(Game *gamePtr, Graphics* graphics);
	void draw();
	void update(float frameTime);
	void onResetDevice();
	void onLostDevice();
private:
	TextureManager infantryTexture;
	TextureManager infantryTexture2;
	Infantry* player1Infantry;
	Infantry* player2Infantry;
};
#pragma endregion
