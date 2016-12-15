/*This class handles all of the units
as well as takes care of the selection box
functions*/

#pragma once
#include "entity.h"
#include "archer.h"
#include "Berserker.h"
#include "WingedHussar.h"
#include "cavalry.h"
#include "infantry.h"
#include "longbowman.h"
#include "TileManager.h"
#include "particleManager.h"
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
	bool fight(Unit& opponent, float frameTime, Audio* audio, int rangeOfAttack, ParticleManager* pm);
	int getSelectionX(){return selectionX;}
	int getSelectionY(){return selectionY;}
	int numEnemyUnits();
	int numAlliedUnits();
	int getSelectedTileX(){return selectedTile.x;}
	int getSelectedTileY(){return selectedTile.y;}
	Unit* getCurrentSelection(){return currentSelection;}
	Unit* getInfantry(int i) { return &player2Infantry[i]; }
	Unit* getAICavalry(int i) { return &player2Cavalry[i]; }
	Unit* getAIArcher(int i) { return &player2Archers[i]; }
	Unit*closestUnit(Unit* t2Unit);
	int aiAttackDirection(Unit* target, int& x, int& y);
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
	void endTurn(bool isPlayerTurn);
	void resetUnits();
	void setPlayerCountries(Country player1, Country player2, Game* gamePtr);
	void cheats(bool isCheatingActive);
private:
	ParticleManager pm;

	TextureManager infantryTexture;
	TextureManager infantryTexture2;
	TextureManager cavalryTexture;
	TextureManager cavalryTexture2;
	TextureManager archerTexture;
	TextureManager archerTexture2;
	TextureManager hussarTexture;
	TextureManager hussarTexture2;
	TextureManager berserkerTexture;
	TextureManager berserkerTexture2;
	TextureManager longbowmanTexture;
	TextureManager longbowmanTexture2;
	TextureManager selectionBoxTexture;
	Image selectionBox;
	struct pair{
		int x;
		int y;
	} selectedTile;
	Unit* player1Infantry;
	Unit* player2Infantry;
	Unit* player1Cavalry;
	Unit* player2Cavalry;
	Unit* player1Archers;
	Unit* player2Archers;
	Unit* currentSelection;
	Unit** player2Units;
	int selectionX;
	int selectionY;
	int lastX;
	int lastY;
	int archerDamage;
};
#pragma endregion 
