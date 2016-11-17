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
	if (!cavalryTexture.initialize(graphics,"pictures\\greenCavalry.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing greenCavalry texture"));
	}
	if (!cavalryTexture2.initialize(graphics,"pictures\\greenCavalry.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing greenCavalry texture"));
	}
	player1Infantry = new Infantry[10];
	player2Infantry = new Infantry[10];
	player1Cavalry = new Cavalry[10];
	player2Cavalry = new Cavalry[10];
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

		player2Cavalry[i].initialize(144, 144, 8, 2, &cavalryTexture, gamePtr);
		player2Cavalry[i].setActive(false);
		player2Cavalry[i].setVisible(false);
	}
	currentSelection = nullptr;
}

void UnitManager::draw(){
	selectionBox.draw(selectionBox.getColorFilter());
	for(int i = 0; i < 10; i++){
		player1Infantry[i].draw();
		player2Infantry[i].draw();
		player1Cavalry[i].draw();
		player2Cavalry[i].draw();
	}
}

void UnitManager::update(float frameTime){
	if(currentSelection != nullptr){
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
	}
}

int UnitManager::numActiveUnits() {
	int activeUnits = 0;
	for (int i = 0; i < 9; i++)
	{
		activeUnits += player2Infantry[i].getActive();
	}
	return activeUnits;
}


void UnitManager::onResetDevice(){
	selectionBoxTexture.onResetDevice();
	infantryTexture.onResetDevice();
	infantryTexture2.onResetDevice();
	cavalryTexture.onResetDevice();
	cavalryTexture2.onResetDevice();
}
void UnitManager::onLostDevice(){
	selectionBoxTexture.onLostDevice();
	infantryTexture.onLostDevice();
	infantryTexture2.onLostDevice();
	cavalryTexture.onLostDevice();
	cavalryTexture2.onLostDevice();
}

void UnitManager::spawnInfantry(int x, int y, int team){
	if(team == 1){
		for(int i = 0; i < 10; i++){
			if(!player1Infantry[i].getActive()){
				player1Infantry[i].setActive(true);
				player1Infantry[i].setVisible(true);
				player1Infantry[i].setHP(10);
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
				player1Infantry[i].setHP(10);
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
				player1Cavalry[i].setHP(5);
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
				player1Cavalry[i].setHP(5);
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

bool UnitManager::fight(Unit& opponent, float frameTime){
	currentSelection->fight(opponent, frameTime); 
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
	return false;
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
	if(selectionBox.getX()+TERRAIN_WIDTH <= GAME_WIDTH){
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
	if(selectionBox.getY()+TERRAIN_HEIGHT <= GAME_HEIGHT){
		selectionBox.setY(selectionBox.getY()+TERRAIN_HEIGHT);
		selectionY++;
	}
}
bool UnitManager::unitUp(TileManager* tileManager){
	if(currentSelection->moveUp()){
		tileManager->getTile(currentSelection->getTileX(), currentSelection->getTileY()+1)->leave();
		tileManager->getTile(currentSelection->getTileX(), currentSelection->getTileY())->occupy(currentSelection);
		return true;
	}
	return false;
}
bool UnitManager::unitDown(TileManager* tileManager){
	if(currentSelection->moveDown()){
		tileManager->getTile(currentSelection->getTileX(), currentSelection->getTileY()-1)->leave();
		tileManager->getTile(currentSelection->getTileX(), currentSelection->getTileY())->occupy(currentSelection);
		return true;
	}
	return false;
}
bool UnitManager::unitLeft(TileManager* tileManager){
	if(currentSelection->moveLeft()){
		tileManager->getTile(currentSelection->getTileX()+1, currentSelection->getTileY())->leave();
		tileManager->getTile(currentSelection->getTileX(), currentSelection->getTileY())->occupy(currentSelection);
		return true;
	}
	return false;
}
bool UnitManager::unitRight(TileManager* tileManager){
	if(currentSelection->moveRight()){
		tileManager->getTile(currentSelection->getTileX()-1, currentSelection->getTileY())->leave();
		tileManager->getTile(currentSelection->getTileX(), currentSelection->getTileY())->occupy(currentSelection);
		return true;
	}
	return false;
} 

void UnitManager::endTurn(){
	for(int i = 0; i < 10; i++){
		player1Infantry[i].setMovementLeft(player1Infantry[i].getMovement());
		player2Infantry[i].setMovementLeft(player2Infantry[i].getMovement());
		player1Cavalry[i].setMovementLeft(player1Cavalry[i].getMovement());
		player2Cavalry[i].setMovementLeft(player2Cavalry[i].getMovement());
	}
}
#pragma endregion

#pragma region Higgs
//Returns the closest enemy to the selected AI unit
Unit* UnitManager::closestUnit(Unit* t2Unit) { 
	VECTOR2 minDistance(1000,1000);
	int closest;
	for (int i = 0; i < 10; i++)	{
		if (minDistance > D3DXVECTOR2(t2Unit->getX() - player1Infantry[i].getX(), t2Unit->getY() - player1Infantry[i].getY()))
			minDistance = D3DXVECTOR2(t2Unit->getX() - player1Infantry[i].getX(), t2Unit->getY() - player1Infantry[i].getY());
		closest = i;
	}
	return &player1Infantry[closest];
}
//Calculates direction of movement, calls moveAttempt for each movement step
void UnitManager::aiAttack(VECTOR2 enemyXY, Unit* aiUnit, TileManager* tileManager) {
	VECTOR2 dir = *(aiUnit->getCenter()) - enemyXY;
	D3DXVec2Normalize(&dir, &dir);
	if (dir.x < -0.707) { 
		moveAttempt(tileManager, 1);
	}

}

bool UnitManager::moveAttempt(TileManager* tileManager, int dir) { //1 = left, 2 = up, 3 = right, 4 = down
	switch (dir)
		case 1:
			if (!tileManager->getTile(currentSelection->getTileX() - 1, currentSelection->getTileY())->isOccupied()) {
				//unitLeft(tileManager);
			}
	return false;
}

#pragma endregion