

#include "primoVictoria.h"



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
	//delete[] tileManager;
}

//=============================================================================
// Initializes the game 
// Throws GameError on error
//=============================================================================
void PrimoVictoria::initialize(HWND hwnd)
{
#pragma region Newell
	Game::initialize(hwnd); // throws GameError
	std::string s;
	mainMenu = new Menu();
	mainMenu->initialize(graphics, input);
	optionsMenu = new Menu(s);
	optionsMenu->initialize(graphics, input);
	currentMenu = 1;

#pragma region Higgs
	if (!backgroundTexture.initialize(graphics, "pictures\\background.PNG"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "BackgroundTexture init fail"));
	if (!background.initialize(graphics, 0,0,0,&backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "BackgroundImg init fail"));
	background.setScale(0.8f);

	if (!tileManager.initialize(graphics, 7,5, this))
		throw(GameError(gameErrorNS::FATAL_ERROR, "TileManager initialization failure"));
	tileManager.setTileVisibility(true);

#pragma endregion

	output = new TextDX();
	if(output->initialize(graphics, 15, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing output font"));
	unitManager.initialize(this, graphics);
	keyDownLastFrame = NULL;
	moving = NULL;
	fighting = false;
	fightTarget = nullptr;
#pragma endregion
	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void PrimoVictoria::update()
{
#pragma region Newell
	if(moving != NULL){
		switch(moving){
		case 1:
			if(unitManager.unitUp(&tileManager)){
				moving = NULL;
			}
			break;
		case 2:
			if(unitManager.unitDown(&tileManager)){
				moving = NULL;
			}
			break;
		case 3:
			if(unitManager.unitLeft(&tileManager)){
				moving = NULL;
			}
			break;
		case 4:
			if(unitManager.unitRight(&tileManager)){
				moving = NULL;
			}
			break;
		}
		mainMenu->update();
		optionsMenu->update();
		unitManager.update(frameTime);
		return;
	}
	if(input->isKeyDown(VK_ESCAPE)){
		exit(0);
	}

	if(fighting == true){
		if(unitManager.fight(*fightTarget, frameTime)){
			fighting = false;
		}
		mainMenu->update();
		optionsMenu->update();
		unitManager.update(frameTime);
		return;
	}

	if (currentMenu == 1 && mainMenu->getSelectedItem() == 0) {
		currentMenu = 0;
	}
	else if(currentMenu == 1 && mainMenu->getSelectedItem() == 1){
		currentMenu = 2;
	}
	else if(currentMenu == 2 && optionsMenu->getSelectedItem() == 2){
		currentMenu = 1;
	}
	if (currentMenu == 0) {
		if(input->isKeyDown(VK_SPACE)){
			keyDownLastFrame = VK_SPACE;
		}
		if(input->isKeyDown(VK_UP)){
			keyDownLastFrame = VK_UP;
		}
		if(input->isKeyDown(VK_DOWN)){
			keyDownLastFrame = VK_DOWN;
		}
		if(input->isKeyDown(VK_LEFT)){
			keyDownLastFrame = VK_LEFT;
		}
		if(input->isKeyDown(VK_RIGHT)){
			keyDownLastFrame = VK_RIGHT;
		}
		if(input->isKeyDown(VK_RETURN)){
			keyDownLastFrame = VK_RETURN;
		}
		if(!input->isKeyDown(VK_SPACE) && keyDownLastFrame == VK_SPACE){
			keyDownLastFrame = NULL;
			//fightTarget = unitManager.getCurrentSelection();
			spawnUnit(0);
			//fighting = true;
		}
		if(!input->isKeyDown(VK_UP) && keyDownLastFrame == VK_UP){
			keyDownLastFrame = NULL;
			if(unitManager.getCurrentSelection() == nullptr){
				unitManager.selectionUp();
			}
			else{
				moving = 1;
			}
		}
		if(!input->isKeyDown(VK_DOWN) && keyDownLastFrame == VK_DOWN){
			keyDownLastFrame = NULL;
			if(unitManager.getCurrentSelection() == nullptr){
				unitManager.selectionDown();
			}
			else{
				moving = 2;
			}
		}
		if(!input->isKeyDown(VK_LEFT) && keyDownLastFrame == VK_LEFT){
			keyDownLastFrame = NULL;
			if(unitManager.getCurrentSelection() == nullptr){
				unitManager.selectionLeft();
			}
			else{
				moving = 3;
			}
		}
		if(!input->isKeyDown(VK_RIGHT) && keyDownLastFrame == VK_RIGHT){
			keyDownLastFrame = NULL;
			if(unitManager.getCurrentSelection() == nullptr){
				unitManager.selectionRight();
			}
			else{
				moving = 4;
			}
		}
		if(!input->isKeyDown(VK_RETURN) && keyDownLastFrame == VK_RETURN){
			keyDownLastFrame = NULL;
			if(unitManager.getCurrentSelection() != nullptr){
				unitManager.setCurrentSelection(nullptr);
			}
			else{
				unitManager.selectUnit((tileManager.getTile(unitManager.getSelectionX(), unitManager.getSelectionY())->getUnit()));
			}
		}
	unitManager.update(frameTime);
	}
	else {
		mainMenu->update();
		optionsMenu->update();
	}
#pragma region Newell
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

	graphics->spriteBegin();  // begin drawing sprites
	background.draw();


	if (currentMenu == 0){
		tileManager.draw(7,5);
	}
	else if(currentMenu == 1){
		mainMenu->displayMenu();
	}
	else if(currentMenu == 2){
		optionsMenu -> displayMenu();
	}
	output->print(ss.str(), 0,0);
	unitManager.draw();
	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void PrimoVictoria::releaseAll()
{
	unitManager.onLostDevice();
	tileManager.onLostDevice();
	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void PrimoVictoria::resetAll()
{
	tileManager.onResetDevice();
	unitManager.onResetDevice();
	Game::resetAll();
	return;
}

#pragma region Newell
void PrimoVictoria::spawnUnit(int unitType){
	if(!(tileManager.getTile(0, 2)->isOccupied())){
		switch(unitType){
		case 0:
			unitManager.spawnInfantry(0, 2);
		case 1:
			unitManager.spawnInfantry(0, 2);
		case 2:
			unitManager.spawnInfantry(0, 2);

		}
		tileManager.getTile(0, 2)->occupy(unitManager.getCurrentSelection());
	}
	else if(!(tileManager.getTile(0, 1)->isOccupied())){
		switch(unitType){
		case 0:
			unitManager.spawnInfantry(0, 1);
		case 1:
			unitManager.spawnInfantry(0, 1);
		case 2:
			unitManager.spawnInfantry(0, 1);
		}
		tileManager.getTile(0, 1)->occupy(unitManager.getCurrentSelection());
	}
	else if(!(tileManager.getTile(0, 3)->isOccupied())){
		switch(unitType){
		case 0:
			unitManager.spawnInfantry(0, 3);
		case 1:
			unitManager.spawnInfantry(0, 3);
		case 2:
			unitManager.spawnInfantry(0, 3);
		}
		tileManager.getTile(0, 3)->occupy(unitManager.getCurrentSelection());
	}
	else if(!(tileManager.getTile(0, 0)->isOccupied())){
		switch(unitType){
		case 0:
			unitManager.spawnInfantry(0, 0);
		case 1:
			unitManager.spawnInfantry(0, 0);
		case 2:
			unitManager.spawnInfantry(0, 0);
		}
		tileManager.getTile(0, 0)->occupy(unitManager.getCurrentSelection());
	}
	else if(!(tileManager.getTile(0, 4)->isOccupied())){
		switch(unitType){
		case 0:
			unitManager.spawnInfantry(0, 4);
		case 1:
			unitManager.spawnInfantry(0, 4);
		case 2:
			unitManager.spawnInfantry(0, 4);
		}
		tileManager.getTile(0, 4)->occupy(unitManager.getCurrentSelection());
	}
}
#pragma endregion