/*This class handles all of the units
as well as takes care of the selection box
functions*/

#pragma once
#include "entity.h"
#include "infantry.h"
#include "cavalry.h"
#include "archer.h"
#include "TileManager.h"
#include "audio.h"

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
	void spawnCavalry(int x, int y, int team);
	void spawnArcher(int x, int y, int team);
	bool fight(Unit& opponent, float frameTime, Audio* audio);
	int getSelectionX(){return selectionX;}
	int getSelectionY(){return selectionY;}
	int numActiveUnits();
	int getSelectedTileX(){return selectedTile.x;}
	int getSelectedTileY(){return selectedTile.y;}
	Unit* getCurrentSelection(){return currentSelection;}
	Infantry* getInfantry(int i) { return &player2Infantry[i]; }
	Unit* getAICavalry(int i) { return &player2Cavalry[i]; }
	Unit*closestUnit(Unit* t2Unit);
	int aiAttackDirection(Unit* target, Unit* aiUnit, int& x, int& y);
	void setCurrentSelection(Unit* newSelection);
	void selectUnit(Unit* newSelection);
	void selectionRight();
	void selectionLeft();
	void selectionUp();
	void selectionDown();
	bool unitUp(TileManager* tileManager, Audio* audio);
	bool unitDown(TileManager* tileManager, Audio* audio);
	bool unitLeft(TileManager* tileManager, Audio* audio);
	bool unitRight(TileManager* tileManager, Audio* audio);
	void endTurn();
private:
	TextureManager infantryTexture;
	TextureManager infantryTexture2;
	TextureManager cavalryTexture;
	TextureManager cavalryTexture2;
	TextureManager archerTexture;
	TextureManager archerTexture2;
	TextureManager selectionBoxTexture;
	Image selectionBox;
	struct pair{
		int x;
		int y;
	} selectedTile;
	Infantry* player1Infantry;
	Infantry* player2Infantry;
	Cavalry* player1Cavalry;
	Cavalry* player2Cavalry;
	Archer* player1Archers;
	Archer* player2Archers;
	Unit* currentSelection;
	Unit** player2Units;
	int selectionX;
	int selectionY;
	int archerDamage;
};
#pragma endregion 
