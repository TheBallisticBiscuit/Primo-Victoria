// Programming 2D Games
// Copyright (c) 2011,2012 by: 
// Charles Kelly
// collisionTypes.h v1.0

#ifndef _COLLISION_TYPES_H      // Prevent multiple definitions if this 
#define _COLLISION_TYPES_H      // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

class PrimoVictoria;

#include "game.h"
#include "textDX.h"
#include "menu.h"
#include "unitManager.h"
#include "Tile.h"
#include "TileManager.h"
#include "particleManager.h"
#include <sstream>
#include <string>
#include <random>
#include <ctime>

//=============================================================================
// This class is the core of the game
//=============================================================================
class PrimoVictoria : public Game
{
private:
	Menu *mainMenu;
	Menu* optionsMenu;
	Menu* defeatScreen;
	Menu* victoryScreen;
	Menu* instructionsScreen;
	Menu* countrySelect;
	TextureManager backgroundTexture;
	Image background;
	TextureManager defeatScreenTexture;
	Image defeatScreenImage;
	TextureManager victoryScreenTexture;
	Image victoryScreenImage;
	TextureManager instructionsTexture;
	Image instructionsImage;
	TextureManager britishTexture;
	Image britishBanner;
	TextureManager polishTexture;
	Image polishBanner;
	TextureManager norseTexture;
	Image norseBanner;
	TextureManager displayBerserkerTexture;
	Berserker displayBerserker;
	TextureManager displayHussarTexture;
	Cavalry displayHussar;
	TextureManager displayLongbowmanTexture;
	Archer displayLongbowman;
	TextureManager spawnCavalryTexture;
	Image spawnCavalryDisplay;
	TextureManager spawnInfantryTexture;
	Image spawnInfantryDisplay;
	TextureManager spawnArcherTexture;
	Image spawnArcherDisplay;

	TextDX *unitStats;
	TextDX *spawnCooldown;
	int currentMenu;
	TileManager tileManager;
	UnitManager unitManager;
	ParticleManager pm;
	Unit* fightTarget;
	bool fighting;
	int keyDownLastFrame;
	int moving;
	bool isPlayerTurn;
	bool isLevelInitialized;
	int level;
	int lastLevel;
	int rangeOfAttack;
	int x1,y1,x2,y2;
	int spawnUnitCooldown;
	Country player1Country;
	Country player2Country;
public:
    // Constructor
    PrimoVictoria();

    // Destructor
    virtual ~PrimoVictoria();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
	void displayUnitsUpdate(); //updates the sprites for the country selection menu
    void ai();          // "
	void moveAttempt(int dir, int x, int y);
    void collisions();  // "
    void render();      // "
	void createParticleEffect(VECTOR2 pos, VECTOR2 vel, int numParticles);
	int getCurrentMenu(){return currentMenu;}
	void spawnUnit(int unitType, int team);
	void levelOneAI();
	void levelTwoAI();
	void levelOne();
	void levelTwo();
	void gameReset();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void playerInput();
	void endTurn();
    void releaseAll();
    void resetAll();
};

#endif
