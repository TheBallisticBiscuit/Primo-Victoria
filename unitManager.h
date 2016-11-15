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
	void spawnInfantry();
	void fight(Unit& opponent, float frameTime);
	Unit* getCurrentSelection(){return currentSelection;}
private:
	TextureManager infantryTexture;
	TextureManager infantryTexture2;
	TextureManager selectionBoxTexture;
	Image selectionBox;
	Infantry* player1Infantry;
	Infantry* player2Infantry;
	Unit* currentSelection;
};
#pragma endregion 
