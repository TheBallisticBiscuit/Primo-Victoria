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
#include <sstream>
#include <string>

//=============================================================================
// This class is the core of the game
//=============================================================================
class PrimoVictoria : public Game
{
private:
	Menu *mainMenu;
	Menu* optionsMenu;
	TextDX *output;
	std::string outString;
	int currentMenu;
	UnitManager unitManager;
public:
    // Constructor
    PrimoVictoria();

    // Destructor
    virtual ~PrimoVictoria();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
	int getCurrentMenu(){return currentMenu;}
};

#endif
