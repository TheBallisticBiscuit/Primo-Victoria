

#include "primoVictoria.h"
#include <string>


//=============================================================================
// Constructor
//=============================================================================
PrimoVictoria::PrimoVictoria()
{
	//nothing here, move on
}

//=============================================================================
// Destructor
//=============================================================================
PrimoVictoria::~PrimoVictoria()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game 
// Throws GameError on error
//=============================================================================
void PrimoVictoria::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError
	std::string s;
	mainMenu = new Menu();
	mainMenu->initialize(graphics, input);
	optionsMenu = new Menu(s);
	optionsMenu->initialize(graphics, input);

	currentMenu = 1;
	outString = "Selected Item: ";
	output = new TextDX();
	if(output->initialize(graphics, 15, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing output font"));
    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void PrimoVictoria::update()
{
	if(input->isKeyDown(VK_ESCAPE)){
		exit(0);
	}
	if(currentMenu == 1 && mainMenu->getSelectedItem() == 1){
		currentMenu = 2;
	}
	else if(currentMenu == 2 && optionsMenu->getSelectedItem() == 0){
		currentMenu = 1;
	}
	mainMenu->update();
	optionsMenu->update();
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void PrimoVictoria::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void PrimoVictoria::collisions()
{
}

//=============================================================================
// Render game items
//=============================================================================
void PrimoVictoria::render()
{
	std::stringstream ss;
	ss << outString;
	ss << mainMenu->getSelectedItem();

    graphics->spriteBegin();                // begin drawing sprites
	if(currentMenu == 1){
		mainMenu->displayMenu();
	}
	else if(currentMenu == 2){
		optionsMenu -> displayMenu();
	}
	output->print(ss.str(), 0,0);

	
    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void PrimoVictoria::releaseAll()
{
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void PrimoVictoria::resetAll()
{
    Game::resetAll();
    return;
}
