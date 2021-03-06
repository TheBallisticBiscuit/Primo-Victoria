#include "unitManager.h"


UnitManager::UnitManager(void)
{
}


UnitManager::~UnitManager(void)
{
}
#pragma region Newell
void UnitManager::initialize(Game* gamePtr, Graphics* graphics){

	if (!selectionBoxTexture.initialize(graphics,"pictures\\selectionBox.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing selectionBox texture"));
	}
	selectionBox.initialize(graphics, 96, 96, 1, &selectionBoxTexture);
	selectionBox.setX(0);
	selectionBox.setY(0);
	selectionBox.setScale(SELECTION_BOX_SCALE);
	selectionBox.setFrames(0, 0);
	selectionX = 0;
	selectionY = 0;

	if(!infantryTexture.initialize(graphics,"pictures\\greenKnight.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing greenKnight texture"));
	}
	if (!infantryTexture2.initialize(graphics,"pictures\\redKnight.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing redKnight texture"));
	}
	if(!berserkerTexture.initialize(graphics,"pictures\\greenBerserker.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing greenBerserker texture"));
	}
	if (!berserkerTexture2.initialize(graphics,"pictures\\redBerserker.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing redBerserker texture"));
	}
	if (!cavalryTexture.initialize(graphics,"pictures\\greenCavalry.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing greenCavalry texture"));
	}
	if (!cavalryTexture2.initialize(graphics,"pictures\\redCavalry.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing greenCavalry texture"));
	}
	if (!hussarTexture.initialize(graphics,"pictures\\greenHussar.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing greenHussar texture"));
	}
	if (!hussarTexture2.initialize(graphics,"pictures\\greenHussar.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing greenHussar texture"));
	}
	if (!archerTexture.initialize(graphics,"pictures\\GreenArcher.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing greenArcher texture"));
	}
	if (!archerTexture2.initialize(graphics,"pictures\\RedArcher.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing redArcher texture"));
	}
	if (!longbowmanTexture.initialize(graphics,"pictures\\greenLongbowman.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing greenArcher texture"));
	}
	if (!longbowmanTexture2.initialize(graphics,"pictures\\redLongbowman.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing redArcher texture"));
	}
	player1Infantry = new Infantry[10];
	player2Infantry = new Infantry[10];
	player1Cavalry = new Cavalry[10];
	player2Cavalry = new Cavalry[10];
	player1Archers = new Archer[10];
	player2Archers = new Archer[10];
	for(int i = 0; i < 10; i++){
		player1Infantry[i].initialize(96, 96, 3, 1, &infantryTexture, gamePtr);
		player1Infantry[i].setActive(false);
		player1Infantry[i].setVisible(false);

		player2Infantry[i].initialize(96, 96, 3, 2, &infantryTexture2, gamePtr);
		player2Infantry[i].setActive(false);
		player2Infantry[i].setVisible(false);

		player1Cavalry[i].initialize(144, 144, 8, 1, &cavalryTexture, gamePtr);
		player1Cavalry[i].setActive(false);
		player1Cavalry[i].setVisible(false);

		player2Cavalry[i].initialize(144, 144, 8, 2, &cavalryTexture2, gamePtr);
		player2Cavalry[i].setActive(false);
		player2Cavalry[i].setVisible(false);

		player1Archers[i].initialize(96, 96, 5, 1, &archerTexture, gamePtr);
		player1Archers[i].setActive(false);
		player1Archers[i].setVisible(false);

		player2Archers[i].initialize(96, 96, 5, 2, &archerTexture2, gamePtr);
		player2Archers[i].setActive(false);
		player2Archers[i].setVisible(false);
	}

	currentSelection = nullptr;
	archerDamage = 0;
}

void UnitManager::draw(){
	selectionBox.draw(selectionBox.getColorFilter());
	for(int i = 0; i < 10; i++){
		player1Infantry[i].draw(player1Infantry[i].getColorFilter());
		player2Infantry[i].draw(player2Infantry[i].getColorFilter());
		player1Cavalry[i].draw();
		player2Cavalry[i].draw();
		player1Archers[i].draw();
		player2Archers[i].draw();
	}
}

void UnitManager::update(float frameTime){
	if(currentSelection != nullptr){
		if (currentSelection->getTeam() == 1)
			selectionBox.setColorFilter(graphicsNS::LIME);
		else
			selectionBox.setColorFilter(graphicsNS::RED);

		selectionBox.setX(currentSelection->getX());
		selectionBox.setY(currentSelection->getY());
		selectedTile.x = (currentSelection->getTileX());
		selectedTile.y = (currentSelection->getTileY());
	}
	else{
		selectionBox.setColorFilter(graphicsNS::BLUE);
	}
	selectionX = selectionBox.getX()/TERRAIN_WIDTH;
	selectionY = selectionBox.getY()/TERRAIN_HEIGHT;
	selectionBox.update(frameTime);
	for(int i = 0; i < 10; i++){
		player1Infantry[i].update(frameTime);
		player2Infantry[i].update(frameTime);
		player1Cavalry[i].update(frameTime);
		player2Cavalry[i].update(frameTime);
		player1Archers[i].update(frameTime);
		player2Archers[i].update(frameTime);
	}
}


void UnitManager::onResetDevice(){
	selectionBoxTexture.onResetDevice();
	infantryTexture.onResetDevice();
	infantryTexture2.onResetDevice();
	cavalryTexture.onResetDevice();
	cavalryTexture2.onResetDevice();
	berserkerTexture.onResetDevice();
	berserkerTexture2.onResetDevice();
	hussarTexture.onResetDevice();
	hussarTexture2.onResetDevice();
	longbowmanTexture.onResetDevice();
	longbowmanTexture2.onResetDevice();
	archerTexture.onResetDevice();
	archerTexture2.onResetDevice();
}
void UnitManager::onLostDevice(){
	selectionBoxTexture.onLostDevice();
	infantryTexture.onLostDevice();
	infantryTexture2.onLostDevice();
	cavalryTexture.onLostDevice();
	cavalryTexture2.onLostDevice();
	berserkerTexture.onLostDevice();
	berserkerTexture2.onLostDevice();
	hussarTexture.onLostDevice();
	hussarTexture2.onLostDevice();
	longbowmanTexture.onLostDevice();
	longbowmanTexture2.onLostDevice();
	archerTexture.onLostDevice();
	archerTexture2.onLostDevice();
}

void UnitManager::spawnInfantry(int x, int y, int team){
	if(team == 1){
		for(int i = 0; i < 10; i++){
			if(!player1Infantry[i].getActive()){
				player1Infantry[i].setActive(true);
				player1Infantry[i].setVisible(true);
				player1Infantry[i].setHP(60);
				player1Infantry[i].setTile(x, y);
				player1Infantry[i].setX(x*TERRAIN_WIDTH);
				player1Infantry[i].setY(y*TERRAIN_HEIGHT);
				selectUnit(&player1Infantry[i]);
				break;
			}
		}
	}
	else if(team == 2){
		for(int i = 0; i < 10; i++){
			if(!player2Infantry[i].getActive()){
				player2Infantry[i].setActive(true);
				player2Infantry[i].setVisible(true);
				player2Infantry[i].setHP(60);
				player2Infantry[i].setTile(x, y);
				player2Infantry[i].setX(x*TERRAIN_WIDTH);
				player2Infantry[i].setY(y*TERRAIN_HEIGHT);
				player2Infantry[i].setLastDirection(Unit::left);
				selectUnit(&player2Infantry[i]);
				break;
			}
		}

	}
}

void UnitManager::spawnCavalry(int x, int y, int team){
	if(team == 1){
		for(int i = 0; i < 10; i++){
			if(!player1Cavalry[i].getActive()){
				player1Cavalry[i].setActive(true);
				player1Cavalry[i].setVisible(true);
				player1Cavalry[i].setHP(35);
				player1Cavalry[i].setTile(x, y);
				player1Cavalry[i].setX(x*TERRAIN_WIDTH);
				player1Cavalry[i].setY(y*TERRAIN_HEIGHT);
				selectUnit(&player1Cavalry[i]);
				break;
			}
		}
	}
	else if(team == 2){
		for(int i = 0; i < 10; i++){
			if(!player2Cavalry[i].getActive()){
				player2Cavalry[i].setActive(true);
				player2Cavalry[i].setVisible(true);
				player2Cavalry[i].setHP(35);
				player2Cavalry[i].setTile(x, y);
				player2Cavalry[i].setX(x*TERRAIN_WIDTH);
				player2Cavalry[i].setY(y*TERRAIN_HEIGHT);
				player2Cavalry[i].setLastDirection(Unit::left);
				selectUnit(&player2Cavalry[i]);
				break;
			}
		}

	}
}

void UnitManager::spawnArcher(int x, int y, int team){
	if(team == 1){
		for(int i = 0; i < 10; i++){
			if(!player1Archers[i].getActive()){
				player1Archers[i].setActive(true);
				player1Archers[i].setVisible(true);
				player1Archers[i].setHP(25);
				player1Archers[i].setTile(x, y);
				player1Archers[i].setX(x*TERRAIN_WIDTH);
				player1Archers[i].setY(y*TERRAIN_HEIGHT);
				selectUnit(&player1Archers[i]);
				break;
			}
		}
	}
	else if(team == 2){
		for(int i = 0; i < 10; i++){
			if(!player2Archers[i].getActive()){
				player2Archers[i].setActive(true);
				player2Archers[i].setVisible(true);
				player2Archers[i].setHP(25);
				player2Archers[i].setTile(x, y);
				player2Archers[i].setX(x*TERRAIN_WIDTH);
				player2Archers[i].setY(y*TERRAIN_HEIGHT);
				player2Archers[i].setLastDirection(Unit::left);
				selectUnit(&player2Archers[i]);
				break;
			}
		}

	}
}

bool UnitManager::fight(Unit& opponent, float frameTime, Audio* audio, int rangeOfAttack, ParticleManager* pm){
	if(rangeOfAttack > opponent.getRange() &&
		(abs(currentSelection->getTileX()-opponent.getTileX()) > opponent.getRange() || 
		abs(currentSelection->getTileY()-opponent.getTileY()) > opponent.getRange())){
			archerDamage = opponent.getHP();
			currentSelection->fight(opponent, frameTime, audio, rangeOfAttack, pm);
			if(opponent.getHP() <= 0){
				currentSelection->setAnimating(false);
				return opponent.kill(frameTime);
			}
			else{
				if(opponent.getHP() < archerDamage){
					currentSelection->setAnimating(false);
					return true;
				}
				else{
					return false;
				}
			}
	}
	else{
		if(opponent.getHP() <= 0 && currentSelection->getHP() > 0){
			currentSelection->setAnimating(false);
			return opponent.kill(frameTime);
		}
		else if(currentSelection->getHP() <= 0 && opponent.getHP() > 0){
			opponent.setAnimating(false);
			return currentSelection->kill(frameTime);
		}
		else if(currentSelection->getHP() <= 0 && opponent.getHP() <= 0){
			bool temp = currentSelection->kill(frameTime);
			bool temp2 = opponent.kill(frameTime);
			if(temp && temp2){
				currentSelection->setAnimating(false);
				opponent.setAnimating(false);
				return true;
			}
		}
		else{
			currentSelection->fight(opponent, frameTime, audio, rangeOfAttack, pm); 
		}
		return false;
	}
	return true;
}


void UnitManager::setCurrentSelection(Unit* newSelection){
	currentSelection = newSelection;
}

void UnitManager::selectUnit(Unit* newSelection){
	currentSelection = newSelection;
	selectedTile.x = (currentSelection->getTileX());
	selectedTile.y = (currentSelection->getTileY());
}

void UnitManager::selectionRight(){
	if(selectionBox.getX()+TERRAIN_WIDTH < GAME_WIDTH){
		selectionBox.setX(selectionBox.getX()+TERRAIN_WIDTH);
		selectionX++;
	}
}

void UnitManager::selectionLeft(){
	if(selectionBox.getX()-TERRAIN_WIDTH >= 0){
		selectionBox.setX(selectionBox.getX()-TERRAIN_WIDTH);
		selectionX--;
	}
}

void UnitManager::selectionUp(){
	if(selectionBox.getY()-TERRAIN_HEIGHT >= 0){
		selectionBox.setY(selectionBox.getY()-TERRAIN_HEIGHT);
		selectionY--;
	}
}

void UnitManager::selectionDown(){
	if(selectionBox.getY()+TERRAIN_HEIGHT < GAME_HEIGHT){
		selectionBox.setY(selectionBox.getY()+TERRAIN_HEIGHT);
		selectionY++;
	}
}

bool UnitManager::unitUp(TileManager* tileManager, Audio* audio){
	if(currentSelection->moveUp(audio)){
		if (tileManager->getTile(currentSelection->getTileX(),currentSelection->getTileY())->getTerrain() == Forest
			&& currentSelection->getDef() < 5){
			currentSelection->setMovementLeft(currentSelection->getMovementLeft()-1);
			currentSelection->setDef(1.2);
		}
		else  if (currentSelection->getDef() < 5){
			currentSelection->setDef(1);
		}
		tileManager->getTile(currentSelection->getTileX(), currentSelection->getTileY()+1)->leave();
		tileManager->getTile(currentSelection->getTileX(), currentSelection->getTileY())->occupy(currentSelection);
		return true;
	}
	return false;
}

bool UnitManager::unitDown(TileManager* tileManager, Audio* audio){
	if(currentSelection->moveDown(audio)){
		if (tileManager->getTile(currentSelection->getTileX(),currentSelection->getTileY())->getTerrain() == Forest
			&& currentSelection->getDef() < 5){
			currentSelection->setMovementLeft(currentSelection->getMovementLeft()-1);
			currentSelection->setDef(1.2);
		}
		else if (currentSelection->getDef() < 5){
			currentSelection->setDef(1);
		}
		tileManager->getTile(currentSelection->getTileX(), currentSelection->getTileY()-1)->leave();
		tileManager->getTile(currentSelection->getTileX(), currentSelection->getTileY())->occupy(currentSelection);
		return true;
	}
	return false;
}

bool UnitManager::unitLeft(TileManager* tileManager, Audio* audio){
	if(currentSelection->moveLeft(audio)){
		if (tileManager->getTile(currentSelection->getTileX(),currentSelection->getTileY())->getTerrain() == Forest
			&& currentSelection->getDef() < 5){
			currentSelection->setMovementLeft(currentSelection->getMovementLeft()-1);
			currentSelection->setDef(1.2);
		}
		else if (currentSelection->getDef() < 5){
			currentSelection->setDef(1);
		}
		tileManager->getTile(currentSelection->getTileX()+1, currentSelection->getTileY())->leave();
		tileManager->getTile(currentSelection->getTileX(), currentSelection->getTileY())->occupy(currentSelection);
		return true;
	}
	return false;
}

bool UnitManager::unitRight(TileManager* tileManager, Audio* audio){
	if(currentSelection->moveRight(audio)){
		if (tileManager->getTile(currentSelection->getTileX(),currentSelection->getTileY())->getTerrain() == Forest
			&& currentSelection->getDef() < 5){
			currentSelection->setMovementLeft(currentSelection->getMovementLeft()-1);
			currentSelection->setDef(1.2);
		}
		else if (currentSelection->getDef() < 5){
			currentSelection->setDef(1);
		}

		tileManager->getTile(currentSelection->getTileX()-1, currentSelection->getTileY())->leave();
		tileManager->getTile(currentSelection->getTileX(), currentSelection->getTileY())->occupy(currentSelection);
		return true;
	}
	return false;
} 

void UnitManager::endTurn(bool isPlayerTurn){
	for(int i = 0; i < 10; i++){
		player1Infantry[i].setMovementLeft(player1Infantry[i].getMovement());
		player2Infantry[i].setMovementLeft(player2Infantry[i].getMovement());
		player1Cavalry[i].setMovementLeft(player1Cavalry[i].getMovement());
		player1Cavalry[i].setDamage(25);
		player2Cavalry[i].setMovementLeft(player2Cavalry[i].getMovement());
		player2Cavalry[i].setDamage(25);
		player1Archers[i].setMovementLeft(player1Archers[i].getMovement());
		player2Archers[i].setMovementLeft(player2Archers[i].getMovement());
	}
	if (isPlayerTurn) {
		lastX = selectionBox.getX();
		lastY = selectionBox.getY();
	}
	else {
		selectionBox.setX(lastX);
		selectionBox.setY(lastY);
	}
}
#pragma endregion

#pragma region Higgs
void UnitManager::cheats(bool isCheatingActive) {
	if (isCheatingActive) {
		for (int i = 0; i < 10; i++)
		{
			player1Archers[i].setDef(10000);
			player1Cavalry[i].setDef(10000);
			player1Infantry[i].setDef(10000);
		}
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			player1Archers[i].setDef(1);
			player1Cavalry[i].setDef(1);
			player1Infantry[i].setDef(1);
		}
	}
}
void UnitManager::resetUnits() {
	for (int i = 0; i < 10; i++)
	{
		player1Archers[i].setActive(false);
		player1Archers[i].setVisible(false);
		player1Cavalry[i].setActive(false);
		player1Cavalry[i].setVisible(false);
		player1Infantry[i].setActive(false);
		player1Infantry[i].setVisible(false);
		player2Archers[i].setActive(false);
		player2Archers[i].setVisible(false);
		player2Cavalry[i].setActive(false);
		player2Cavalry[i].setVisible(false);
		player2Infantry[i].setActive(false);
		player2Infantry[i].setVisible(false);
	}
}

//Returns number of computer's units that are active
int UnitManager::numEnemyUnits() {
	int activeUnits = 0;
	for (int i = 0; i < 10; i++)
	{
		activeUnits += player2Infantry[i].getActive();
		activeUnits += player2Cavalry[i].getActive();
		activeUnits += player2Archers[i].getActive();
	}
	return activeUnits;
}
//Returns number of player's units that are active
int UnitManager::numAlliedUnits() {
	int activeUnits = 0;
	for (int i = 0; i < 10; i++)
	{
		 activeUnits += player1Archers[i].getActive();
		 activeUnits += player1Cavalry[i].getActive();
		 activeUnits += player1Infantry[i].getActive();
	}
	return activeUnits;
}


//Returns the closest enemy to the selected AI unit
Unit* UnitManager::closestUnit(Unit* t2Unit) { 
	VECTOR2 minDistance(1000,1000);
	int closest = 0;
	int type = -1;
	for (int i = 0; i < 10; i++)	{
		if (player1Infantry[i].getActive()) {
			if (D3DXVec2LengthSq(&minDistance) > D3DXVec2LengthSq(&D3DXVECTOR2(t2Unit->getX() - player1Infantry[i].getX(), t2Unit->getY() - player1Infantry[i].getY()))) {
				minDistance = D3DXVECTOR2(t2Unit->getX() - player1Infantry[i].getX(), t2Unit->getY() - player1Infantry[i].getY());
				closest = i;
				type = 0;

			}
		}
	}
	for (int i = 0; i < 10; i++)
	{
		if (player1Cavalry[i].getActive()) {
			if (D3DXVec2LengthSq(&minDistance) > D3DXVec2LengthSq(&D3DXVECTOR2(t2Unit->getX() - player1Cavalry[i].getX(), t2Unit->getY() - player1Cavalry[i].getY()))) {
				minDistance = D3DXVECTOR2(t2Unit->getX() - player1Cavalry[i].getX(), t2Unit->getY() - player1Cavalry[i].getY());
				closest = i;
				type = 1;
			}
		}
	}
	for (int i = 0; i < 10; i++)
	{
		if (player1Archers[i].getActive()) {
			if (D3DXVec2LengthSq(&minDistance) > D3DXVec2LengthSq(&D3DXVECTOR2(t2Unit->getX() - player1Archers[i].getX(), t2Unit->getY() - player1Archers[i].getY()))) {
				minDistance = D3DXVECTOR2(t2Unit->getX() - player1Archers[i].getX(), t2Unit->getY() - player1Archers[i].getY());
				closest = i;
				type = 2;
			}
		}
	}
	if (type == 0)
		return &player1Infantry[closest];
	else if (type == 1)
		return &player1Cavalry[closest];
	else if (type == 2)
		return &player1Archers[closest];
}

//Calculates direction of movement
int UnitManager::aiAttackDirection(Unit* target, int& x, int& y) {
	x = currentSelection->getTileX();
	y = currentSelection->getTileY();

	VECTOR2 dir = D3DXVECTOR2(target->getTileX() - x, target->getTileY() - y);
	D3DXVec2Normalize(&dir, &dir);


	if (dir.x <= -0.707) 
		return 3;
	if (dir.y <= -0.707)
		return 1;
	if (dir.x >= 0.707)
		return 4;
	if (dir.y >= 0.707)
		return 2;
}

#pragma endregion

#pragma region Newell

void UnitManager::setPlayerCountries(Country player1, Country player2, Game* gamePtr){
	switch(player1){
	case Britain:
		delete [] player1Archers;
		delete [] player1Infantry;
		delete [] player1Cavalry;
		player1Archers = new Longbowman[10];
		player1Infantry = new Infantry[10];
		player1Cavalry = new Cavalry[10];
		for(int i = 0; i < 10; i ++){
			player1Infantry[i].initialize(96, 96, 3, 1, &infantryTexture, gamePtr);
			player1Infantry[i].setActive(false);
			player1Infantry[i].setVisible(false);

			player1Cavalry[i].initialize(144, 144, 8, 1, &cavalryTexture, gamePtr);
			player1Cavalry[i].setActive(false);
			player1Cavalry[i].setVisible(false);
			player1Cavalry[i].setScale(CAVALRY_SCALING);

			player1Archers[i].initialize(96, 96, 13, 1, &longbowmanTexture, gamePtr);
			player1Archers[i].setActive(false);
			player1Archers[i].setVisible(false);
		}
		break;
	case Poland:
		delete [] player1Archers;
		delete [] player1Infantry;
		delete [] player1Cavalry;
		player1Archers = new Archer[10];
		player1Infantry = new Infantry[10];
		player1Cavalry = new WingedHussar[10];
		for(int i = 0; i < 10; i ++){
			player1Infantry[i].initialize(96, 96, 3, 1, &infantryTexture, gamePtr);
			player1Infantry[i].setActive(false);
			player1Infantry[i].setVisible(false);

			player1Cavalry[i].initialize(144, 144, 8, 1, &hussarTexture, gamePtr);
			player1Cavalry[i].setActive(false);
			player1Cavalry[i].setVisible(false);
			player1Cavalry[i].setScale(CAVALRY_SCALING);

			player1Archers[i].initialize(96, 96, 5, 1, &archerTexture, gamePtr);
			player1Archers[i].setActive(false);
			player1Archers[i].setVisible(false);
		}
		break;
	case Norse:
		delete [] player1Archers;
		delete [] player1Infantry;
		delete [] player1Cavalry;
		player1Archers = new Archer[10];
		player1Infantry = new Berserker[10];
		player1Cavalry = new Cavalry[10];
		for(int i = 0; i < 10; i ++){
			player1Infantry[i].initialize(96, 96, 10, 1, &berserkerTexture, gamePtr);
			player1Infantry[i].setActive(false);
			player1Infantry[i].setVisible(false);

			player1Cavalry[i].initialize(144, 144, 8, 1, &cavalryTexture, gamePtr);
			player1Cavalry[i].setActive(false);
			player1Cavalry[i].setVisible(false);
			player1Cavalry[i].setScale(CAVALRY_SCALING);

			player1Archers[i].initialize(96, 96, 5, 1, &archerTexture, gamePtr);
			player1Archers[i].setActive(false);
			player1Archers[i].setVisible(false);
		}
		break;
	}
	switch(player2){
	case Britain:
		delete [] player2Archers;
		delete [] player2Infantry;
		delete [] player2Cavalry;
		player2Archers = new Longbowman[10];
		player2Infantry = new Infantry[10];
		player2Cavalry = new Cavalry[10];
		for(int i = 0; i < 10; i ++){
			player2Infantry[i].initialize(96, 96, 3, 2, &infantryTexture2, gamePtr);
			player2Infantry[i].setActive(false);
			player2Infantry[i].setVisible(false);

			player2Cavalry[i].initialize(144, 144, 8, 2, &cavalryTexture2, gamePtr);
			player2Cavalry[i].setActive(false);
			player2Cavalry[i].setVisible(false);
			player2Cavalry[i].setScale(CAVALRY_SCALING);

			player2Archers[i].initialize(96, 96, 13, 2, &longbowmanTexture2, gamePtr);
			player2Archers[i].setActive(false);
			player2Archers[i].setVisible(false);
		}
		break;
	case Poland:
		delete [] player2Archers;
		delete [] player2Infantry;
		delete [] player2Cavalry;
		player2Archers = new Archer[10];
		player2Infantry = new Infantry[10];
		player2Cavalry = new WingedHussar[10];
		for(int i = 0; i < 10; i ++){
			player2Infantry[i].initialize(96, 96, 3, 2, &infantryTexture2, gamePtr);
			player2Infantry[i].setActive(false);
			player2Infantry[i].setVisible(false);

			player2Cavalry[i].initialize(144, 144, 8, 2, &hussarTexture2, gamePtr);
			player2Cavalry[i].setActive(false);
			player2Cavalry[i].setVisible(false);
			player2Cavalry[i].setScale(CAVALRY_SCALING);

			player2Archers[i].initialize(96, 96, 5, 2, &archerTexture2, gamePtr);
			player2Archers[i].setActive(false);
			player2Archers[i].setVisible(false);
		}
		break;
	case Norse:
		delete [] player2Archers;
		delete [] player2Infantry;
		delete [] player2Cavalry;
		player2Archers = new Archer[10];
		player2Infantry = new Berserker[10];
		player2Cavalry = new Cavalry[10];
		for(int i = 0; i < 10; i ++){
			player2Infantry[i].initialize(96, 96, 10, 2, &berserkerTexture2, gamePtr);
			player2Infantry[i].setActive(false);
			player2Infantry[i].setVisible(false);

			player2Cavalry[i].initialize(144, 144, 8, 2, &cavalryTexture2, gamePtr);
			player2Cavalry[i].setActive(false);
			player2Cavalry[i].setVisible(false);
			player2Cavalry[i].setScale(CAVALRY_SCALING);

			player2Archers[i].initialize(96, 96, 5, 2, &archerTexture2, gamePtr);
			player2Archers[i].setActive(false);
			player2Archers[i].setVisible(false);
		}
		break;

	}
}
#pragma endregion