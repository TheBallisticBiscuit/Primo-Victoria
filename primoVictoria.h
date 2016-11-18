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
	TextureManager backgroundTexture;
	Image background;

	TileManager tileManager;

	TextDX *unitStats;
	int currentMenu;
	UnitManager unitManager;
	Unit* fightTarget;
	bool fighting;
	int keyDownLastFrame;
	int moving;
	bool isPlayerTurn;
	bool isLevelInitialized;
	int level;
	int x1,y1,x2,y2;
public:
    // Constructor
    PrimoVictoria();

    // Destructor
    virtual ~PrimoVictoria();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
	void moveAttempt(int dir, int x, int y);
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
	int getCurrentMenu(){return currentMenu;}
	void spawnUnit(int unitType, int team);
	void levelOne();
	void levelTwo();
	void gameReset();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void playerInput();
	void endTurn();
};

#endif
