

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
	isPlayerTurn = true;
	srand(time(0));

	if (!backgroundTexture.initialize(graphics, "pictures\\background.PNG"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "BackgroundTexture init fail"));
	if (!background.initialize(graphics, 0,0,0,&backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "BackgroundImg init fail"));
	background.setScale(BACKGROUND_IMAGE_SCALE);
	background.setX(140.f);

	graphics->setBackColor(SETCOLOR_ARGB(0xFF, 0xAF, 0x3F, 0x2F));

	if (!tileManager.initialize(graphics, 12,7, this))
		throw(GameError(gameErrorNS::FATAL_ERROR, "TileManager initialization failure"));
	tileManager.setTileVisibility(true);

#pragma endregion

	unitStats = new TextDX();
	if(unitStats->initialize(graphics, 30, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing unit stats font"));
	unitManager.initialize(this, graphics);
	keyDownLastFrame = NULL;
	moving = NULL;
	fighting = false;
	fightTarget = nullptr;
	audio->playCue(BACKGROUND_MUSIC);
#pragma endregion
	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void PrimoVictoria::update()
{
#pragma region Newell
	if(unitManager.getCurrentSelection() != nullptr && unitManager.getCurrentSelection()->getMovementLeft() == 0 && !fighting){
		unitManager.setCurrentSelection(nullptr);
		endTurn();
	}
	if(moving != NULL){
		switch(moving){
		case 1:
			moveUp();
			break;
		case 2:
			moveDown();
			break;
		case 3:
			moveLeft();
			break;
		case 4:
			moveRight();
			break;
		}
		if(input->isKeyDown(VK_ESCAPE)){
			exit(0);
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
			if(fightTarget->getHP() <= 0){
				tileManager.getTile(fightTarget->getTileX(), fightTarget->getTileY())->leave();
			}
			if(unitManager.getCurrentSelection()->getHP() <= 0){
				tileManager.getTile(unitManager.getCurrentSelection()->getTileX(), 
					unitManager.getCurrentSelection()->getTileY())->leave();
			}
			unitManager.setCurrentSelection(nullptr);
			fightTarget = nullptr;
			endTurn();
		}
		mainMenu->update();
		optionsMenu->update();
		unitManager.update(frameTime);
		return;
	}
	if(currentMenu == 0){
		if (isPlayerTurn == true)
			playerInput();			
	}
	else {
		mainMenu->update();
		optionsMenu->update();
	}
	if (currentMenu == 1 && mainMenu->getSelectedItem() == 0) {
		tileManager.setTileVisibility(true);
		currentMenu = 0;
	}
	else if(currentMenu == 1 && mainMenu->getSelectedItem() == 1){
		currentMenu = 2;
	}
	else if(currentMenu == 2 && optionsMenu->getSelectedItem() == 2){
		currentMenu = 1;
	}

	mainMenu->update();
	optionsMenu->update();
	unitManager.update(frameTime);
#pragma region Newell
}

#pragma region Higgs
//=============================================================================
// Artificial Intelligence
//=============================================================================
void PrimoVictoria::ai()
{
	if (!moving) {
		int dir, r, t, x, y = 0;
		if (!isPlayerTurn) {
			r = 2; //rand()%(#)
			if (unitManager.numActiveUnits() < r) {
				t = unitManager.numActiveUnits();
				spawnUnit(t,2);
			}
			else {
				if (unitManager.getCurrentSelection() != nullptr && unitManager.getCurrentSelection()->getTeam() != 2) {
					r = rand()%2;
					if (r == 0) {
						for (int i = 0; i < 10; i++) //Find available unit
						{
							if (unitManager.getInfantry(i)->getActive()) { 
								unitManager.selectUnit(unitManager.getInfantry(i));
								break;
							}
						}
					}
					else if (r == 1) {
						for (int i = 0; i < 10; i++) //Find available unit
						{
							if (unitManager.getAICavalry(i)->getActive()) {
								unitManager.selectUnit(unitManager.getAICavalry(i));
								break;
							}				
						}			
					}
				}
				Unit* target = unitManager.closestUnit(unitManager.getCurrentSelection()); //Select unit

				dir = unitManager.aiAttackDirection(target, unitManager.getCurrentSelection(), x, y);
				if(!fighting){
					moveAttempt(dir, x, y);
				}


			}
		}
	}
}

void PrimoVictoria::moveAttempt(int dir, int x, int y) {
	switch (dir) {//1 = Up, 2 = Down, 3 = Left, 4 = Right
	case 1:
		moving = 1;
		break;
	case 2:
		moving = 2;
		break;
	case 3:
		moving = 3;
		break;
	case 4:
		moving = 4;
		break;
	}
}

#pragma endregion

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
	//std::stringstream ss;
	graphics->spriteBegin();  // begin drawing sprites
	background.draw();
	if (currentMenu == 0){
		tileManager.draw();
		unitManager.draw();
	}
	else if(currentMenu == 1){
		mainMenu->displayMenu();
	}
	else if(currentMenu == 2){
		optionsMenu -> displayMenu();
	}
	if(tileManager.getTile(unitManager.getSelectionX(), unitManager.getSelectionY())->isOccupied()){
		unitStats->setFontColor(graphicsNS::LIME);
		unitStats->print("HP: " +std::to_string(tileManager.getTile(unitManager.getSelectionX(), 
			unitManager.getSelectionY())->getUnit()->getHP())+ "          Movement Remaining: " +
			std::to_string(tileManager.getTile(unitManager.getSelectionX(), 
			unitManager.getSelectionY())->getUnit()->getMovementLeft()), 50, GAME_HEIGHT-50);
	}
	//unitStats->print(ss.str(), 0,0);

	graphics->spriteEnd();                  // end drawing sprites
}

void PrimoVictoria::playerInput() {
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
		spawnUnit(1, 1);
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
			if(tileManager.getTile(unitManager.getSelectionX(), unitManager.getSelectionY())->isOccupied()){
				if (tileManager.getTile(unitManager.getSelectionX(), unitManager.getSelectionY())->getUnit()->getTeam() == 1)
					unitManager.selectUnit((tileManager.getTile(unitManager.getSelectionX(), unitManager.getSelectionY())->getUnit()));
			}
		}
	}
	unitManager.update(frameTime);
}


#pragma region Newell/Higgs
void PrimoVictoria::spawnUnit(int unitType, int team){
	int spawnX = 0;
	if(team == 2){
		spawnX = tileManager.getWidth()-1;
	}
	for (int i = 0; i < tileManager.getHeight(); i++) {
		if(!(tileManager.getTile(spawnX, 3 + (std::pow((-1),i)) * ((i+1)/2))->isOccupied())){
			switch(unitType){
			case 0:
				unitManager.spawnInfantry(spawnX, 3 + (std::pow((-1),i)) * ((i+1)/2), team);
				endTurn();
				break;
			case 1:
				unitManager.spawnCavalry(spawnX, 3 + (std::pow((-1),i)) * ((i+1)/2), team);
				endTurn();
				break;
			case 2:
				unitManager.spawnArcher(spawnX, 3 + (std::pow((-1),i)) * ((i+1)/2), team);
				endTurn();
				break;
			}
			tileManager.getTile(spawnX, 3 + (std::pow((-1),i)) * ((i+1)/2))->occupy(unitManager.getCurrentSelection());
			break;
		}
	}
	if (isPlayerTurn)
		unitManager.setCurrentSelection(nullptr);
}
#pragma endregion

#pragma region Newell
void PrimoVictoria::moveUp(){
	unitManager.getCurrentSelection()->setLastDirection(Unit::up);
	if (unitManager.getCurrentSelection()->getTileY() > 0) {
		/*if(tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()-unitManager.getCurrentSelection()
		-> getRange())->isOccupied()){
		if(tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()-unitManager.getCurrentSelection()
		-> getRange())->getUnit()->getTeam() == 2 && isPlayerTurn){
		fightTarget = tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()
		-unitManager.getCurrentSelection()-> getRange())->getUnit();
		fighting = true;
		}
		else if(tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()-unitManager.getCurrentSelection()
		-> getRange())->getUnit()->getTeam() == 1 && !isPlayerTurn){
		fightTarget = tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()
		-unitManager.getCurrentSelection()-> getRange())->getUnit();
		fighting = true;
		}
		}*/

		/*else*/if(!(tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()-1)
			->isOccupied())){
				if(unitManager.unitUp(&tileManager)){
					moving = NULL;
					//if(unitManager.getCurrentSelection()->getMovementLeft() <= 0){
					//	endTurn();
					//}
				}
		}
		else if(tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()-1)
			->isOccupied()){
				if(tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()-1)
					->getUnit()->getTeam() == 2 && isPlayerTurn){
						fightTarget = tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()-1)
							->getUnit();
						fighting = true;
				}
				else if(tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()-1)
					->getUnit()->getTeam() == 1 && !isPlayerTurn){
						fightTarget = tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()-1)
							->getUnit();
						fighting = true;
				}
				moving = NULL;
		}
	}
	else{
		moving = NULL;
	}
}

void PrimoVictoria::moveDown(){
	unitManager.getCurrentSelection()->setLastDirection(Unit::down);
	if (unitManager.getCurrentSelection()->getTileY() < tileManager.getHeight()-1) {
		/*if(tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()+unitManager.getCurrentSelection()
		-> getRange())->isOccupied()){
		if(tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()+unitManager.getCurrentSelection()
		-> getRange())->getUnit()->getTeam() == 2 && isPlayerTurn){
		fightTarget = tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()
		-unitManager.getCurrentSelection()-> getRange())->getUnit();
		fighting = true;
		}
		else if(tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()+unitManager.getCurrentSelection()
		-> getRange())->getUnit()->getTeam() == 1 && !isPlayerTurn){
		fightTarget = tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()
		+unitManager.getCurrentSelection()-> getRange())->getUnit();
		fighting = true;
		}
		}*/
		/*else*/ if(!(tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()+1)
			->isOccupied())){
				if(unitManager.unitDown(&tileManager)){
					moving = NULL;
					//if(unitManager.getCurrentSelection()->getMovementLeft() <= 0){
					//	endTurn();
					//}
				}
		}
		else if(tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()+1)
			->isOccupied()){
				if(tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()+1)
					->getUnit()->getTeam() == 2 && isPlayerTurn){
						fightTarget = tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()+1)
							->getUnit();
						fighting = true;
				}
				else if(tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()+1)
					->getUnit()->getTeam() == 1 && !isPlayerTurn){
						fightTarget = tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()+1)
							->getUnit();
						fighting = true;
				}
				moving = NULL;
		}
	}
	else{
		moving = NULL;
	}
}

void PrimoVictoria::moveLeft(){
	unitManager.getCurrentSelection()->setLastDirection(Unit::left);
	if (unitManager.getCurrentSelection()->getTileX() > 0) {
		/*		if(tileManager.getTile(unitManager.getSelectedTileX()-unitManager.getCurrentSelection()
		-> getRange(), unitManager.getSelectedTileY())->isOccupied()){
		if(tileManager.getTile(unitManager.getSelectedTileX()-unitManager.getCurrentSelection()
		-> getRange(), unitManager.getSelectedTileY())->getUnit()->getTeam() == 2 && isPlayerTurn){
		fightTarget = tileManager.getTile(unitManager.getSelectedTileX()-unitManager.getCurrentSelection()-> getRange(), 
		unitManager.getSelectedTileY())->getUnit();
		fighting = true;
		}
		else if(tileManager.getTile(unitManager.getSelectedTileX()-unitManager.getCurrentSelection()->getRange(), 
		unitManager.getSelectedTileY())->getUnit()->getTeam() == 1 && !isPlayerTurn){
		fightTarget = tileManager.getTile(unitManager.getSelectedTileX()-unitManager.getCurrentSelection()-> getRange(), 
		unitManager.getSelectedTileY())->getUnit();
		fighting = true;
		}
		}
		else*/if(!(tileManager.getTile(unitManager.getSelectedTileX()-1, unitManager.getSelectedTileY())
			->isOccupied())){
				if(unitManager.unitLeft(&tileManager)){
					moving = NULL;
					//if(unitManager.getCurrentSelection()->getMovementLeft() <= 0){
					//	endTurn();
					//}
				}
		}
		else if(tileManager.getTile(unitManager.getSelectedTileX()-1, unitManager.getSelectedTileY())
			->isOccupied()){
				if(tileManager.getTile(unitManager.getSelectedTileX()-1, unitManager.getSelectedTileY())
					->getUnit()->getTeam() == 2 && isPlayerTurn){
						fightTarget = tileManager.getTile(unitManager.getSelectedTileX()-1, unitManager.getSelectedTileY())
							->getUnit();
						fighting = true;
				}
				else if(tileManager.getTile(unitManager.getSelectedTileX()-1, unitManager.getSelectedTileY())
					->getUnit()->getTeam() == 1 && !isPlayerTurn){
						fightTarget = tileManager.getTile(unitManager.getSelectedTileX()-1, unitManager.getSelectedTileY())
							->getUnit();
						fighting = true;
				}
				moving = NULL;
		}
	}
	else{
		moving = NULL;
	}
}

void PrimoVictoria::moveRight(){
	unitManager.getCurrentSelection()->setLastDirection(Unit::right);
	if (unitManager.getCurrentSelection()->getTileX() < tileManager.getWidth()-1) {
		/*if(tileManager.getTile(unitManager.getSelectedTileX()+unitManager.getCurrentSelection()
		-> getRange(), unitManager.getSelectedTileY())->isOccupied()){
		if(tileManager.getTile(unitManager.getSelectedTileX()+unitManager.getCurrentSelection()
		-> getRange(), unitManager.getSelectedTileY())->getUnit()->getTeam() == 2 && isPlayerTurn){
		fightTarget = tileManager.getTile(unitManager.getSelectedTileX()+unitManager.getCurrentSelection()-> getRange(), 
		unitManager.getSelectedTileY())->getUnit();
		fighting = true;
		}
		else if(tileManager.getTile(unitManager.getSelectedTileX()+unitManager.getCurrentSelection()->getRange(), 
		unitManager.getSelectedTileY())->getUnit()->getTeam() == 1 && !isPlayerTurn){
		fightTarget = tileManager.getTile(unitManager.getSelectedTileX()+unitManager.getCurrentSelection()-> getRange(), 
		unitManager.getSelectedTileY())->getUnit();
		fighting = true;
		}
		}*/
		/*else*/if(!(tileManager.getTile(unitManager.getSelectedTileX()+1, unitManager.getSelectedTileY())
			->isOccupied())){
				if(unitManager.unitRight(&tileManager)){
					moving = NULL;
					//if(unitManager.getCurrentSelection()->getMovementLeft() <= 0){
					//	endTurn();
					//}
				}
		}
		else if(tileManager.getTile(unitManager.getSelectedTileX()+1, unitManager.getSelectedTileY())
			->isOccupied()){
				if(tileManager.getTile(unitManager.getSelectedTileX()+1, unitManager.getSelectedTileY())
					->getUnit()->getTeam() == 2 && isPlayerTurn){
						fightTarget = tileManager.getTile(unitManager.getSelectedTileX()+1, unitManager.getSelectedTileY())
							->getUnit();
						fighting = true;
				}
				else if(tileManager.getTile(unitManager.getSelectedTileX()+1, unitManager.getSelectedTileY())
					->getUnit()->getTeam() == 1 && !isPlayerTurn){
						fightTarget = tileManager.getTile(unitManager.getSelectedTileX()+1, unitManager.getSelectedTileY())
							->getUnit();
						fighting = true;
				}
				moving = NULL;
		}
	}
	else{
		moving = NULL;
	}
}

void PrimoVictoria::endTurn(){
	unitManager.endTurn();
	isPlayerTurn = !isPlayerTurn;
	moving = NULL;
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
#pragma endregion