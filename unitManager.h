/*This class handles all of the units
as well as takes care of the selection box
functions*/

#pragma once
#include "entity.h"
#include "infantry.h"
#include "TileManager.h"

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
	void spawnInfantry(int x, int y, int team);
	bool fight(Unit& opponent, float frameTime);
	Unit* getCurrentSelection(){return currentSelection;}
	int getSelectionX(){return selectionX;}
	int getSelectionY(){return selectionY;}
	void setCurrentSelection(Unit* newSelection);
	void selectUnit(Unit* newSelection);
	void selectionRight();
	void selectionLeft();
	void selectionUp();
	void selectionDown();
	bool unitUp(TileManager* tileManager);
	bool unitDown(TileManager* tileManager);
	bool unitLeft(TileManager* tileManager);
	bool unitRight(TileManager* tileManager);
private:
	TextureManager infantryTexture;
	TextureManager infantryTexture2;
	TextureManager selectionBoxTexture;
	Image selectionBox;
	struct pair{
		int x;
		int y;
	} selectedTile;
	Infantry* player1Infantry;
	Infantry* player2Infantry;
	Unit* currentSelection;
	int selectionX;
	int selectionY;
};
#pragma endregion 
