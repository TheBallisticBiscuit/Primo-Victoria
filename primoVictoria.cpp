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

	mainMenu = new Menu("Main");
	mainMenu->initialize(graphics, input);
	optionsMenu = new Menu("Levels");
	optionsMenu->initialize(graphics, input);
	defeatScreen = new Menu("Defeat");
	defeatScreen->initialize(graphics, input);
	victoryScreen = new Menu("Victory");
	victoryScreen->initialize(graphics, input);
	instructionsScreen = new Menu("Instructions");
	instructionsScreen->initialize(graphics, input);
	countrySelect = new Menu ("Countries");
	countrySelect ->initialize(graphics, input);

	currentMenu = 1;

	unitStats = new TextDX();
	if(unitStats->initialize(graphics, 30, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing unit stats font"));
	spawnCooldown = new TextDX();
	if(spawnCooldown->initialize(graphics, 30, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing unit stats font"));
	unitManager.initialize(this, graphics);
	keyDownLastFrame = NULL;
	moving = NULL;
	fighting = false;
	fightTarget = nullptr;
	audio->playCue(BACKGROUND_MUSIC);
#pragma endregion

#pragma region Higgs
	isPlayerTurn = true;
	isLevelInitialized = false;
	level = 0;
	x1,y1,x2,y2 = 0;
	srand(time(0));

	pm.initialize(graphics);

	if (!backgroundTexture.initialize(graphics, "pictures\\background.PNG"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "BackgroundTexture init fail"));
	if (!background.initialize(graphics, 0,0,0,&backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "BackgroundImg init fail"));
	background.setScale(BACKGROUND_IMAGE_SCALE);
	background.setX(140.f);
#pragma endregion
#pragma region Newell
	if (!defeatScreenTexture.initialize(graphics, "pictures\\defeatScreen.PNG"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "BackgroundTexture init fail"));
	if (!defeatScreenImage.initialize(graphics, 0,0,0, &defeatScreenTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "BackgroundImg init fail"));
	if (!victoryScreenTexture.initialize(graphics, "pictures\\victoryScreen.PNG"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "BackgroundTexture init fail"));
	if (!victoryScreenImage.initialize(graphics, 0,0,0, &victoryScreenTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "BackgroundImg init fail"));
	if (!instructionsTexture.initialize(graphics, "pictures\\instructions.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "InstructionsTexture init fail"));
	if (!instructionsImage.initialize(graphics, 0,0,0,&instructionsTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "InstructionsImage failed initialization"));
	if (!britishTexture.initialize(graphics, "pictures\\britishBanner.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "britishTexture init fail"));
	if (!britishBanner.initialize(graphics, 0,0,0,&britishTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "britishBanner failed initialization"));
	if (!polishTexture.initialize(graphics, "pictures\\polishBanner.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "polishTexture init fail"));
	if (!polishBanner.initialize(graphics, 0,0,0,&polishTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "polishBanner failed initialization"));
	if (!norseTexture.initialize(graphics, "pictures\\norseBanner.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "norseTexture init fail"));
	if (!norseBanner.initialize(graphics, 0,0,0,&norseTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "norseBanner failed initialization"));
	britishBanner.setX(0);
	britishBanner.setY(0);
	norseBanner.setX(384);
	norseBanner.setY(0);
	polishBanner.setX(768);
	polishBanner.setY(0);
	if(!spawnCavalryTexture.initialize(graphics,"pictures\\spawnCavalry.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing displayBerserker texture"));
	}
	if(!spawnInfantryTexture.initialize(graphics,"pictures\\spawnInfantry.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing displayBerserker texture"));
	}
	if(!spawnArcherTexture.initialize(graphics,"pictures\\spawnArcher.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing displayBerserker texture"));
	}
	spawnCavalryDisplay.initialize(graphics, 60, 70, 1, &spawnCavalryTexture);
	spawnCavalryDisplay.setX(110);
	spawnCavalryDisplay.setY(20);
	spawnInfantryDisplay.initialize(graphics, 60, 70, 1, &spawnInfantryTexture);
	spawnInfantryDisplay.setX(50);
	spawnInfantryDisplay.setY(25); //slightly weirdly proportioned texture, needs to be lower than others
	spawnArcherDisplay.initialize(graphics, 60, 70, 1, &spawnArcherTexture);
	spawnArcherDisplay.setX(170);
	spawnArcherDisplay.setY(20);


	if(!displayBerserkerTexture.initialize(graphics,"pictures\\greenBerserker.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing displayBerserker texture"));
	}
	displayBerserker.initialize(96, 96, 10, 1, &displayBerserkerTexture, this);
	displayBerserker.setX(535);
	displayBerserker.setY(527);
	displayBerserker.setFrames(BERSERKER_ATTACK_RIGHT_START, BERSERKER_ATTACK_RIGHT_END);
	displayBerserker.setAnimating(true);
	if(!displayHussarTexture.initialize(graphics,"pictures\\greenHussar.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing displayBerserker texture"));
	}
	displayHussar.initialize(144, 144, 8, 1, &displayHussarTexture, this);
	displayHussar.setX(925);
	displayHussar.setY(500);
	displayHussar.setFrames(HUSSAR_RUN_RIGHT_START, HUSSAR_RUN_RIGHT_END);
	displayHussar.setAnimating(true);
	if(!displayLongbowmanTexture.initialize(graphics,"pictures\\greenLongbowman.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing displayBerserker texture"));
	}
	displayLongbowman.initialize(96, 96, 13, 1, &displayLongbowmanTexture, this);
	displayLongbowman.setX(150);
	displayLongbowman.setY(468);
	displayLongbowman.setFrames(LONGBOWMAN_IDLE_RIGHT_START, LONGBOWMAN_IDLE_RIGHT_END);
	displayLongbowman.setAnimating(true);

	victoryScreenImage.setScale(1.1);
	graphics->setBackColor(SETCOLOR_ARGB(0xFF, 0xAF, 0x3F, 0x2F));

	if (!tileManager.initialize(graphics, 12,7, this))
		throw(GameError(gameErrorNS::FATAL_ERROR, "TileManager initialization failure"));
	tileManager.setTileVisibility(true);
	spawnUnitCooldown = 0;
#pragma endregion
	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void PrimoVictoria::update()
{
#pragma region Newell
	if(unitManager.getCurrentSelection() != nullptr && unitManager.getCurrentSelection()->getMovementLeft() <= 0 && !fighting){
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
		defeatScreen->update();
		countrySelect->update();
		unitManager.update(frameTime);
		displayUnitsUpdate();
		pm.update(frameTime);
		return;
	}
	if(input->isKeyDown(VK_ESCAPE)){
		exit(0);
	}
	if(fighting == true){
		if(unitManager.fight(*fightTarget, frameTime, audio)){
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
		defeatScreen->update();
		victoryScreen->update();
		countrySelect->update();
		unitManager.update(frameTime);
		displayUnitsUpdate();
		pm.update(frameTime);
		return;
	}
	if(currentMenu == 0 || currentMenu == 5){
		if (isPlayerTurn == true)
			playerInput();			
	}
	else {
		mainMenu->update();
		optionsMenu->update();
		defeatScreen->update();
		victoryScreen->update();
		countrySelect->update();
		displayUnitsUpdate();
		pm.update(frameTime);
	}
	if (currentMenu == 1 && mainMenu->getSelectedItem() == 0) { //Selecting Play Game
		currentMenu = 6;
		level = 1;
	}
	else if(currentMenu == 1 && mainMenu->getSelectedItem() == 1){ //Level select
		currentMenu = 2;
	}
	else if (currentMenu == 1 && mainMenu->getSelectedItem() == 2){ //Instructions
		currentMenu = 5;
	}
	else if(currentMenu == 2 && optionsMenu->getSelectedItem() == 2){ //Back to Main Menu
		currentMenu = 1;
	}
	else if (currentMenu == 2 && optionsMenu->getSelectedItem() == 0) { //Selecting Level One
		currentMenu = 6;
		level = 1;
	}
	else if (currentMenu == 2 && optionsMenu->getSelectedItem() == 1) { //Selecting Level Two
		currentMenu = 6;
		level = 2;
	}
	else if(currentMenu == 3 && defeatScreen->getSelectedItem() == 0){ //Return to Main Menu
		currentMenu = 1;
		gameReset();
	}
	else if(currentMenu == 3 && defeatScreen->getSelectedItem() == 1){ //selecting LEVEL SELECT
		currentMenu = 2;
		gameReset();
	}
	else if(currentMenu == 3 && defeatScreen->getSelectedItem() == 2){ //selecting RETRY
		if(level == 1){
			gameReset();
			levelOne();
		}
		else if(level == 2){
			gameReset();
			levelTwo();
		}
	}
	else if(currentMenu == 4 && victoryScreen->getSelectedItem() == 0){ //Return to main menu
		currentMenu = 1;
	}
	else if(currentMenu == 4 && victoryScreen->getSelectedItem() == 1){ //Go to level select
		currentMenu = 2;
	}
	else if(currentMenu == 4 && victoryScreen->getSelectedItem() == 2){ //Restart level
		if(level == 1){
			levelOne();
			currentMenu = 0;
		}
		else if(level == 2){
			levelTwo();
			currentMenu = 0;
		}
	}
	else if(currentMenu == 6 && countrySelect->getSelectedItem() == 0){ //selecting Britain
		player1Country = Britain;
		currentMenu = 0;
		if(level == 1){
			levelOne();
		}
		else if(level == 2){
			levelTwo();
		}
	}
	else if(currentMenu == 6 && countrySelect->getSelectedItem() == 1){ //selecting Norse
		player1Country = Norse;
		currentMenu = 0;
		if(level == 1){
			levelOne();
		}
		else if(level == 2){
			levelTwo();
		}
	}
	else if(currentMenu == 6 && countrySelect->getSelectedItem() == 2){ //selecting Poland
		player1Country = Poland;
		currentMenu = 0;
		if(level == 1){
			levelOne();
		}
		else if(level == 2){
			levelTwo();
		}
	}

	if (currentMenu == 0 && level == 1 && unitManager.numEnemyUnits() == 0 && unitManager.numAlliedUnits() > 0){ //Level 1 Win con
		currentMenu = 4;
	}
	if (currentMenu == 0 && unitManager.numEnemyUnits() >= 0 && unitManager.numAlliedUnits() == 0)	{
		currentMenu = 3;
	}
	if (currentMenu == 0 && level == 2 && tileManager.getTile(x1,y1)->isOccupied() && tileManager.getTile(x2,y2)->isOccupied()){
		if (tileManager.getTile(x1,y1)->getUnit()->getTeam() == 1 && tileManager.getTile(x2,y2)->getUnit()->getTeam() == 1 && currentMenu == 0) {
			currentMenu = 4;
			gameReset();
		}

	}

	victoryScreen->update();
	defeatScreen->update();
	mainMenu->update();
	optionsMenu->update();
	instructionsScreen->update();
	countrySelect->update();
	unitManager.update(frameTime);
	displayUnitsUpdate();
	pm.update(frameTime);

#pragma endregion
}

#pragma region Higgs
void PrimoVictoria::createParticleEffect(VECTOR2 pos, VECTOR2 vel, int numParticles){

	pm.setPosition(pos);
	pm.setVelocity(vel);
	pm.setVisibleNParticles(numParticles);

}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void PrimoVictoria::ai()
{
	if (!moving && !isPlayerTurn) {
		if (level == 1) {
			levelOneAI();
		}

		if (level == 2) {
			levelTwoAI();
		}
	}
}	
void PrimoVictoria::levelOneAI() {
	int r = 0;

	if (unitManager.getCurrentSelection() == nullptr || (unitManager.getCurrentSelection() != nullptr //If no unit is 
		&& unitManager.getCurrentSelection()->getTeam() != 2)) {				   //selected, select one
			r = rand()%3;
			if (r == 0) {
				if (rand()%2) {
					for (int i = 0; i < 10; i++) //Find available unit
					{
						if (unitManager.getInfantry(i)->getActive()) { 
							unitManager.selectUnit(unitManager.getInfantry(i));
							break;
						}
					}
				}
				else {
					for (int i = 0; i < 10; i++) //Find available unit
					{
						if (unitManager.getInfantry(9-i)->getActive()) { 
							unitManager.selectUnit(unitManager.getInfantry(9-i));
							break;
						}
					}
				}
			}
			else if (r == 1) {
				if (rand()%2) {
					for (int i = 0; i < 10; i++) //Find available unit
					{
						if (unitManager.getAICavalry(i)->getActive()) {
							unitManager.selectUnit(unitManager.getAICavalry(i));
							break;
						}				
					}
				}
				else {
					for (int i = 0; i < 10; i++) //Find available unit
					{
						if (unitManager.getAICavalry(9-i)->getActive()) {
							unitManager.selectUnit(unitManager.getAICavalry(9-i));
							break;
						}				
					}
				}
			}
			else {
				if (rand()%2) {
					for (int i = 0; i < 10; i++) //Find available unit
					{
						if (unitManager.getAIArcher(i)->getActive()) {
							unitManager.selectUnit(unitManager.getAIArcher(i));
							break;
						}				
					}
				}
				else {
					for (int i = 0; i < 10; i++) //Find available unit
					{
						if (unitManager.getAIArcher(9-i)->getActive()) {
							unitManager.selectUnit(unitManager.getAIArcher(9-i));
							break;
						}				
					}
				}
			}

	}
	int dir, x, y = 0;

	if (unitManager.getCurrentSelection() != nullptr) {
		Unit* target = unitManager.closestUnit(unitManager.getCurrentSelection()); //Select closest player unit

		dir = unitManager.aiAttackDirection(target, x, y);
		if(!fighting)
			moveAttempt(dir, x, y);			

	}
}

void PrimoVictoria::levelTwoAI() {
	int spawnOrMove = rand()%2;
	int r = 0;

	if (spawnOrMove == 0 || unitManager.numEnemyUnits() <= 0){
		if(unitManager.numEnemyUnits() >= 6 || unitManager.getCurrentSelection() != nullptr){
			spawnOrMove = 1;
		}
		else{
			spawnUnit(rand()%3,2);
			spawnOrMove = 0;
		}
	}

	if ((unitManager.getCurrentSelection() == nullptr || (unitManager.getCurrentSelection() != nullptr //If no unit is selected,
		&& unitManager.getCurrentSelection()->getTeam() != 2)) && spawnOrMove == 1) {				   //select one
			r = rand()%3;
			if (r == 0) {
				if (rand()%2) {
					for (int i = 0; i < 10; i++) //Find available unit
					{
						if (unitManager.getInfantry(i)->getActive()) { 
							unitManager.selectUnit(unitManager.getInfantry(i));
							break;
						}
					}
				}
				else {
					for (int i = 0; i < 10; i++) //Find available unit
					{
						if (unitManager.getInfantry(9-i)->getActive()) { 
							unitManager.selectUnit(unitManager.getInfantry(9-i));
							break;
						}
					}
				}
			}
			else if (r == 1) {
				if (rand()%2) {
					for (int i = 0; i < 10; i++) //Find available unit
					{
						if (unitManager.getAICavalry(i)->getActive()) {
							unitManager.selectUnit(unitManager.getAICavalry(i));
							break;
						}				
					}
				}
				else {
					for (int i = 0; i < 10; i++) //Find available unit
					{
						if (unitManager.getAICavalry(9-i)->getActive()) {
							unitManager.selectUnit(unitManager.getAICavalry(9-i));
							break;
						}				
					}
				}
			}
			else {
				if (rand()%2) {
					for (int i = 0; i < 10; i++) //Find available unit
					{
						if (unitManager.getAIArcher(i)->getActive()) {
							unitManager.selectUnit(unitManager.getAIArcher(i));
							break;
						}				
					}
				}
				else {
					for (int i = 0; i < 10; i++) //Find available unit
					{
						if (unitManager.getAIArcher(9-i)->getActive()) {
							unitManager.selectUnit(unitManager.getAIArcher(9-i));
							break;
						}				
					}
				}
			}
	}
	int dir, x, y = 0;
	
	if (unitManager.getCurrentSelection() != nullptr && spawnOrMove == 1) {
		Unit* target = unitManager.closestUnit(unitManager.getCurrentSelection()); //Select closest player unit

		dir = unitManager.aiAttackDirection(target, x, y);
		if(!fighting)
			moveAttempt(dir, x, y);			

	}
}

//Changes unit direction if attempting to walk into an allied unit
void PrimoVictoria::moveAttempt(int dir, int x, int y) { //New and Improved functionality!
	while (true) {
		switch (dir) {//1 = Up, 2 = Down, 3 = Left, 4 = Right
		case 1:
			if (y > 0) {
				if (tileManager.getTile(x,y-1)->isOccupied() && tileManager.getTile(x,y-1)->getUnit()->getTeam() == 2) {
					dir = rand()%2 + 3; //Left or right
					break;
				}
				else {
					moving = 1;
					return;
				}
			}
		case 2:
			if (y < 6) {
				if (tileManager.getTile(x,y+1)->isOccupied() && tileManager.getTile(x,y+1)->getUnit()->getTeam() == 2) {
					dir = rand()%2 + 3; //Left or right
					break;
				}
				else {
					moving = 2;
					return;
				}
			}
		case 3:
			if (x > 0){
				if (tileManager.getTile(x-1,y)->isOccupied() && tileManager.getTile(x-1,y)->getUnit()->getTeam() == 2){
					dir = rand()%2 + 1; //Up or down
					break;
				}
				else {
					moving = 3;
					return;
				}
			}
		case 4:
			if (x < 11) {
				if (tileManager.getTile(x+1,y)->isOccupied() && tileManager.getTile(x+1,y)->getUnit()->getTeam() == 2) {
					dir = rand()%2 + 1; //Up or down
					break;
				}
				else {
					moving = 4;
					return;
				}
			}
		default:
			dir = rand()%4 + 1;
		}
	}
}

void PrimoVictoria::levelOne() { //Initialize level one
	gameReset();
	int newAICountry = rand()%3;
	switch(newAICountry){
	case 0:
		player2Country = Britain;
		break;
	case 1:
		player2Country = Norse;
		break;
	case 2:
		player2Country = Poland;
		break;
	}
	unitManager.setPlayerCountries(player1Country, player2Country, this);

	for (int i = 0; i < 2; i++) //Spawns player2's units
	{
		spawnUnit(rand()%3,2);
		spawnUnit(rand()%3,2);
	}
	spawnUnit(rand()%3,2);

	switch(player1Country){
	case Britain:
		spawnUnit(rand()%2,1);
		spawnUnit(2,1);
		spawnUnit(2,1);
		spawnUnit(rand()%2,1);
		break;
	case Norse:
		spawnUnit(rand()%2+1, 1);
		spawnUnit(0,1);
		spawnUnit(0,1);
		spawnUnit(rand()%2+1, 1);
		break;
	case Poland:
		spawnUnit(rand()%2*2,1);
		spawnUnit(1,1);
		spawnUnit(1,1);
		spawnUnit(rand()%2*2,1);
		break;
	}

	tileManager.setTileVisibility(true);
	isLevelInitialized = true;
	isPlayerTurn = true;
	unitManager.setCurrentSelection(nullptr);
	level = 1;
}

void PrimoVictoria::levelTwo() { //Initialize level two
	gameReset();
	int newAICountry = rand()%3;
	switch(newAICountry){
	case 0:
		player2Country = Britain;
		break;
	case 1:
		player2Country = Norse;
		break;
	case 2:
		player2Country = Poland;
		break;
	}
	unitManager.setPlayerCountries(player1Country, player2Country, this);
	for (int i = 0; i < 3; i++)
	{
		spawnUnit(rand()%3,2);
		if (i == 0)
			spawnUnit(static_cast<int>(player1Country),1);
		else
			spawnUnit(rand()%3,1);
	}
	tileManager.setTileVisibility(true);
	x1 = rand()%5 + 3;
	y1 = rand()%7;
	x2 = rand()%5 + 6;
	y2 = rand()%7;
	if (x1 == x2 && y1 == y2) {
		x2 = rand()%7 + 4;
		y2 = rand()%7;
	}

	tileManager.levelTwoSetup(graphics,x1,y1,x2,y2,this);

	isLevelInitialized = true;
	isPlayerTurn = true;
	unitManager.setCurrentSelection(nullptr);
	level = 2;
}

void PrimoVictoria::gameReset() {
	unitManager.resetUnits();
	tileManager.tilesReset();
	isLevelInitialized = false;
	level = 0;
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
	graphics->spriteBegin();  // begin drawing sprites
	background.draw();
#pragma region Newell
	if (currentMenu == 0){
		tileManager.draw();
		if (level == 2) {
			tileManager.draw(2);
		}
		pm.draw();
		unitManager.draw();
	}
	else if(currentMenu == 1){
		mainMenu->displayMenu();
	}
	else if(currentMenu == 2){
		optionsMenu -> displayMenu();
	}
	else if(currentMenu == 3){
		defeatScreenImage.draw();
		defeatScreen -> displayMenu();
	}
	else if(currentMenu == 4){
		victoryScreenImage.draw();
		victoryScreen -> displayMenu();
	}
	else if(currentMenu == 5){
		instructionsImage.draw();
		instructionsScreen->displayMenu();
	}
	else if(currentMenu == 6){
		britishBanner.setColorFilter(graphicsNS::GRAY);
		norseBanner.setColorFilter(graphicsNS::GRAY);
		polishBanner.setColorFilter(graphicsNS::GRAY);
		displayBerserker.setVisible(false);
		displayHussar.setVisible(false);
		displayLongbowman.setVisible(false);
		switch(countrySelect->getLinePtr()){
		case 0: //britain hovered
			britishBanner.setColorFilter(graphicsNS::WHITE);
			displayLongbowman.setVisible(true);
			break;
		case 1: //norse hovered
			norseBanner.setColorFilter(graphicsNS::WHITE);
			displayBerserker.setVisible(true);
			break;
		case 2: //poland hovered
			polishBanner.setColorFilter(graphicsNS::WHITE);
			displayHussar.setVisible(true);
			break;
		}
		britishBanner.draw(britishBanner.getColorFilter());
		polishBanner.draw(polishBanner.getColorFilter());
		norseBanner.draw(norseBanner.getColorFilter());
		countrySelect->displayMenu();
		displayBerserker.draw();
		displayHussar.draw();
		displayLongbowman.draw();
	}
	if (currentMenu == 0) {
		if(tileManager.getTile(unitManager.getSelectionX(), unitManager.getSelectionY())->isOccupied()){
			unitStats->setFontColor(graphicsNS::LIME);
			unitStats->print("HP: " +std::to_string(tileManager.getTile(unitManager.getSelectionX(), 
				unitManager.getSelectionY())->getUnit()->getHP())+ "          Movement Remaining: " +
				std::to_string(tileManager.getTile(unitManager.getSelectionX(), 
				unitManager.getSelectionY())->getUnit()->getMovementLeft()), 50, GAME_HEIGHT-50);
		}
		if(level == 2){
			if(spawnUnitCooldown > 0){
				spawnInfantryDisplay.setColorFilter(graphicsNS::GRAY);
				spawnCavalryDisplay.setColorFilter(graphicsNS::GRAY);
				spawnArcherDisplay.setColorFilter(graphicsNS::GRAY);
			}
			spawnArcherDisplay.draw(spawnArcherDisplay.getColorFilter());
			spawnCavalryDisplay.draw(spawnCavalryDisplay.getColorFilter());
			spawnInfantryDisplay.draw(spawnInfantryDisplay.getColorFilter());
			spawnCooldown->setFontColor(graphicsNS::RED);
			if(spawnUnitCooldown > 0){
				spawnCooldown->print(std::to_string(spawnUnitCooldown) + "       " + std::to_string(spawnUnitCooldown) + "       " 
					+ std::to_string(spawnUnitCooldown), 70, 20);
			}
		}
	}
#pragma endregion

	graphics->spriteEnd();                  // end drawing sprites
}

void PrimoVictoria::playerInput() {
	if(!input->isKeyDown(VK_RETURN) && keyDownLastFrame == VK_RETURN && currentMenu == 5){
		keyDownLastFrame = NULL;
		currentMenu = 1;
		return;
	}
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
	if(input->isKeyDown(0x31)){
		keyDownLastFrame = 0x31;
		if(spawnUnitCooldown <= 0){
			spawnInfantryDisplay.setColorFilter(graphicsNS::LIME);
		}
	}
	if(input->isKeyDown(0x32)){
		keyDownLastFrame = 0x32;
		if(spawnUnitCooldown <= 0){
			spawnCavalryDisplay.setColorFilter(graphicsNS::LIME);
		}
	}
	if(input->isKeyDown(0x33)){
		keyDownLastFrame = 0x33;
		if(spawnUnitCooldown <= 0){
			spawnArcherDisplay.setColorFilter(graphicsNS::LIME);
		}
	}
	if(!input->isKeyDown(0x31) && keyDownLastFrame == 0x31 && spawnUnitCooldown == 0){
		keyDownLastFrame = NULL;
		spawnInfantryDisplay.setColorFilter(graphicsNS::WHITE);
		spawnUnit(0, 1);
		spawnUnitCooldown += 3;
	}
	if(!input->isKeyDown(0x32) && keyDownLastFrame == 0x32 && spawnUnitCooldown == 0){
		keyDownLastFrame = NULL;
		spawnCavalryDisplay.setColorFilter(graphicsNS::WHITE);
		spawnUnit(1, 1);
		spawnUnitCooldown += 3;
	}
	if(!input->isKeyDown(0x33) && keyDownLastFrame == 0x33 && spawnUnitCooldown == 0){
		keyDownLastFrame = NULL;
		spawnArcherDisplay.setColorFilter(graphicsNS::WHITE);
		spawnUnit(2, 1);
		spawnUnitCooldown += 3;
	}
	if(!input->isKeyDown(VK_SPACE) && keyDownLastFrame == VK_SPACE){
		keyDownLastFrame = NULL;
		unitManager.setCurrentSelection(nullptr);
		endTurn();
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
			if(unitManager.getCurrentSelection()->getMovementLeft() == unitManager.getCurrentSelection()->getMovement()){
				unitManager.setCurrentSelection(nullptr);
			}
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
	//if (isPlayerTurn)
	unitManager.setCurrentSelection(nullptr);
}
#pragma endregion

#pragma region Newell
void PrimoVictoria::moveUp(){	
	VECTOR2 pos, vel;
	if (unitManager.getCurrentSelection()->getMovement() != 6) {
		pos = VECTOR2(unitManager.getCurrentSelection()->getX()+rand()%15+40, //Create dust
			unitManager.getCurrentSelection()->getCenterY()+25);
		vel = VECTOR2(0,0.3);
		createParticleEffect(pos,vel,2);
	}
	else {
		pos = VECTOR2(unitManager.getCurrentSelection()->getX()+rand()%15+40, //Create dust
			unitManager.getCurrentSelection()->getCenterY()+25);
		vel = VECTOR2(0,0.3);
		createParticleEffect(pos,vel,2);
	}

	unitManager.getCurrentSelection()->setLastDirection(Unit::up);
	if (unitManager.getCurrentSelection()->getTileY() > 0) {
		for(int i = 1; i <= unitManager.getCurrentSelection()->getRange(); i++){
			if(unitManager.getCurrentSelection()->getTileY() - i >= 0){
				if(tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()-i)->isOccupied() &&
					tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()-i)->getUnit()->getTeam()
					!= unitManager.getCurrentSelection()->getTeam()){
						fightTarget = tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()-i)->getUnit();
						fighting = true;
						moving = NULL;
						return;
				}
			}
		}
		if(!(tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()-1)
			->isOccupied())){
				if(unitManager.unitUp(&tileManager, audio)){
					moving = NULL;
				}
		}
		else{
			moving = NULL;
		}
	}
	else{
		moving = NULL;
	}
}

void PrimoVictoria::moveDown(){
	VECTOR2 pos, vel;
	if (unitManager.getCurrentSelection()->getMovement() != 6){
		pos = VECTOR2(unitManager.getCurrentSelection()->getX()+rand()%15+40, //Create dust
			unitManager.getCurrentSelection()->getY()+rand()%20+20);
		vel = VECTOR2(0,-0.3);
		createParticleEffect(pos,vel,2);
	}
	else {
		pos = VECTOR2(unitManager.getCurrentSelection()->getX()+rand()%15+40, //Create dust
			unitManager.getCurrentSelection()->getY()+rand()%40);
		vel = VECTOR2(0,-0.3);
		createParticleEffect(pos,vel,2);
	}
	unitManager.getCurrentSelection()->setLastDirection(Unit::down);
	if (unitManager.getCurrentSelection()->getTileY() < tileManager.getHeight()-1) {
		for(int i = 1; i <= unitManager.getCurrentSelection()->getRange(); i++){
			if(unitManager.getCurrentSelection()->getTileY() + i <= tileManager.getHeight()-1){
				if(tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()+i)->isOccupied() &&
					tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()+i)->getUnit()->getTeam()
					!= unitManager.getCurrentSelection()->getTeam()){
						fightTarget = tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()+i)->getUnit();
						fighting = true;
						moving = NULL;
						return;
				}
			}
		}
		if(!(tileManager.getTile(unitManager.getSelectedTileX(), unitManager.getSelectedTileY()+1)
			->isOccupied())){
				if(unitManager.unitDown(&tileManager, audio)){
					moving = NULL;
				}
		}
		else{
			moving = NULL;
		}
	}
	else{
		moving = NULL;
	}
}

void PrimoVictoria::moveLeft(){
	VECTOR2 pos, vel;
	if (unitManager.getCurrentSelection()->getMovement() != 6) {
		pos = VECTOR2(unitManager.getCurrentSelection()->getX()+rand()%25+35, //Create dust
			unitManager.getCurrentSelection()->getY()+rand()%12+60);
		vel = VECTOR2(0.2,0);
		createParticleEffect(pos,vel,1);
	}
	else {
		pos = VECTOR2(unitManager.getCurrentSelection()->getX()+rand()%30+25, //Create dust
			unitManager.getCurrentSelection()->getY()+rand()%15+48);
		vel = VECTOR2(0.2,0);
		createParticleEffect(pos,vel,1);
	}

	unitManager.getCurrentSelection()->setLastDirection(Unit::left);
	if (unitManager.getCurrentSelection()->getTileX() > 0) {
		for(int i = 1; i <= unitManager.getCurrentSelection()->getRange(); i++){
			if(unitManager.getCurrentSelection()->getTileX() - i >= 0){
				if(tileManager.getTile(unitManager.getSelectedTileX()-i, unitManager.getSelectedTileY())->isOccupied() &&
					tileManager.getTile(unitManager.getSelectedTileX()-i, unitManager.getSelectedTileY())->getUnit()->getTeam()
					!= unitManager.getCurrentSelection()->getTeam()){
						fightTarget = tileManager.getTile(unitManager.getSelectedTileX()-i, unitManager.getSelectedTileY())->getUnit();
						fighting = true;
						moving = NULL;
						return;
				}
			}
		}
		if(!(tileManager.getTile(unitManager.getSelectedTileX()-1, unitManager.getSelectedTileY())
			->isOccupied())){
				if(unitManager.unitLeft(&tileManager, audio)){
					moving = NULL;
				}
		}
		else{
			moving = NULL;
		}
	}
	else{
		moving = NULL;
	}
}

void PrimoVictoria::moveRight(){
	VECTOR2 pos, vel;
	if (unitManager.getCurrentSelection()->getMovement() != 6) {
		pos = VECTOR2(unitManager.getCurrentSelection()->getX()+rand()%25+30, //Create dust
			unitManager.getCurrentSelection()->getY()+rand()%12+60);
		vel = VECTOR2(0.2,0);
		createParticleEffect(pos,vel,1);
	}
	else {
		pos = VECTOR2(unitManager.getCurrentSelection()->getX()+rand()%30+25, //Create dust
			unitManager.getCurrentSelection()->getY()+rand()%15+48);
		vel = VECTOR2(0.2,0);
		createParticleEffect(pos,vel,1);
	}

	unitManager.getCurrentSelection()->setLastDirection(Unit::right);
	if (unitManager.getCurrentSelection()->getTileX() < tileManager.getWidth()-1) {
		for(int i = 1; i <= unitManager.getCurrentSelection()->getRange(); i++){
			if(unitManager.getCurrentSelection()->getTileX() + i <= tileManager.getWidth()-1){
				if(tileManager.getTile(unitManager.getSelectedTileX() + i, unitManager.getSelectedTileY())->isOccupied() &&
					tileManager.getTile(unitManager.getSelectedTileX() + i, unitManager.getSelectedTileY())->getUnit()->getTeam()
					!= unitManager.getCurrentSelection()->getTeam()){
						fightTarget = tileManager.getTile(unitManager.getSelectedTileX() + i, unitManager.getSelectedTileY())->getUnit();
						fighting = true;
						moving = NULL;
						return;
				}
			}
		}
		if(!(tileManager.getTile(unitManager.getSelectedTileX()+1, unitManager.getSelectedTileY())
			->isOccupied())){
				if(unitManager.unitRight(&tileManager, audio)){
					moving = NULL;
				}
		}
		else{
			moving = NULL;
		}
	}
	else{
		moving = NULL;
	}
}

void PrimoVictoria::endTurn(){
	unitManager.endTurn(isPlayerTurn);
	isPlayerTurn = !isPlayerTurn;
	if(isPlayerTurn && spawnUnitCooldown > 0){
		spawnUnitCooldown--;
	}
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
	displayBerserkerTexture.onLostDevice();
	displayHussarTexture.onLostDevice();
	displayLongbowmanTexture.onLostDevice();
	spawnCavalryTexture.onLostDevice();
	spawnInfantryTexture.onLostDevice();
	spawnArcherTexture.onLostDevice();
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
	displayBerserkerTexture.onResetDevice();
	displayHussarTexture.onResetDevice();
	displayLongbowmanTexture.onResetDevice();
	spawnCavalryTexture.onResetDevice();
	spawnInfantryTexture.onResetDevice();
	spawnArcherTexture.onResetDevice();
	Game::resetAll();
	return;
}

void PrimoVictoria::displayUnitsUpdate(){
	displayBerserker.update(frameTime);
	displayHussar.update(frameTime);
	displayLongbowman.update(frameTime);
	spawnArcherDisplay.update(frameTime);
	spawnCavalryDisplay.update(frameTime);
	spawnInfantryDisplay.update(frameTime);
}
#pragma endregion