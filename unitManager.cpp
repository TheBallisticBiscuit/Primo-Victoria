#include "unitManager.h"


UnitManager::UnitManager(void)
{
}


UnitManager::~UnitManager(void)
{
}
#pragma region Newell
void UnitManager::initialize(Game *gamePtr, Graphics* graphics){

	if (!selectionBoxTexture.initialize(graphics,"pictures\\selectionBox.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing selectionBox texture"));
	}
	selectionBox.initialize(graphics, 96, 96, 1, &selectionBoxTexture);
	selectionBox.setX(0);
	selectionBox.setY(0);
	selectionBox.setScale(SELECTION_BOX_SCALE);
	selectionX = 0;
	selectionY = 0;

	if(!infantryTexture.initialize(graphics,"pictures\\greenKnight.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing greenKnight texture"));
	}
	if (!infantryTexture2.initialize(graphics,"pictures\\greenKnight.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing redKnight texture"));
	}
	player1Infantry = new Infantry[10];
	for(int i = 0; i < 10; i++){
		player1Infantry[i].initialize(96, 96, 3, &infantryTexture, gamePtr);
		player1Infantry[i].setActive(false);
		player1Infantry[i].setVisible(false);
	}
	player2Infantry = new Infantry[10];
	for(int i = 0; i < 10; i++){
		player2Infantry[i].initialize(96, 96, 3, &infantryTexture2, gamePtr);
		player2Infantry[i].setActive(false);
		player2Infantry[i].setVisible(false);
	}
	currentSelection = nullptr;
}

void UnitManager::draw(){
	selectionBox.draw();
	for(int i = 0; i < 10; i++){
		player1Infantry[i].draw();
		player2Infantry[i].draw();
	}
}

void UnitManager::update(float frameTime){
	if(currentSelection != nullptr){
		selectionBox.setX(currentSelection->getX());
		selectionBox.setY(currentSelection->getY());
		selectedTile.x = (currentSelection->getTileX());
		selectedTile.y = (currentSelection->getTileY());
	}
	selectionX = selectionBox.getX()/TERRAIN_WIDTH;
	selectionY = selectionBox.getY()/TERRAIN_HEIGHT;
	selectionBox.update(frameTime);
	for(int i = 0; i < 10; i++){
		player1Infantry[i].update(frameTime);
		player2Infantry[i].update(frameTime);
	}

}
void UnitManager::onResetDevice(){
	selectionBoxTexture.onResetDevice();
	infantryTexture.onResetDevice();
	infantryTexture2.onResetDevice();
}
void UnitManager::onLostDevice(){
	selectionBoxTexture.onLostDevice();
	infantryTexture.onLostDevice();
	infantryTexture2.onLostDevice();
}

void UnitManager::spawnInfantry(int x, int y){
	for(int i = 0; i < 10; i++){
		if(!player1Infantry[i].getActive()){
			player1Infantry[i].setActive(true);
			player1Infantry[i].setVisible(true);
			player1Infantry[i].setTile(x, y);
			player1Infantry[i].setX(x*TERRAIN_WIDTH);
			player1Infantry[i].setY(y*TERRAIN_HEIGHT);
			selectUnit(&player1Infantry[i]);
			break;
		}
	}
}

bool UnitManager::fight(Unit& opponent, float frameTime){
	currentSelection->fight(opponent, frameTime); 
	if(opponent.getHP() <= 0 && currentSelection->getHP() > 0){
		return opponent.kill(frameTime);
	}
	else if(currentSelection->getHP() <= 0 && opponent.getHP() > 0){
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
	if(!(tileManager->getTile(selectedTile.x, selectedTile.y-1)->isOccupied())){
		if(currentSelection->moveUp()){
			tileManager->getTile(currentSelection->getTileX(), currentSelection->getTileY()+1)->leave();
			tileManager->getTile(currentSelection->getTileX(), currentSelection->getTileY())->occupy(currentSelection);
			return true;
		}
	}
	else if(tileManager->getTile(selectedTile.x, selectedTile.y-1)->isOccupied()){
		return true;
	}
	return false;
}
bool UnitManager::unitDown(TileManager* tileManager){
	if(!(tileManager->getTile(selectedTile.x, selectedTile.y+1)->isOccupied())){
		if(currentSelection->moveDown()){
			tileManager->getTile(currentSelection->getTileX(), currentSelection->getTileY()-1)->leave();
			tileManager->getTile(currentSelection->getTileX(), currentSelection->getTileY())->occupy(currentSelection);
			return true;
		}
	}
		else if(tileManager->getTile(selectedTile.x, selectedTile.y+1)->isOccupied()){
		return true;
	}
	return false;
}
bool UnitManager::unitLeft(TileManager* tileManager){
	if(!(tileManager->getTile(selectedTile.x-1, selectedTile.y)->isOccupied())){
		if(currentSelection->moveLeft()){
			tileManager->getTile(currentSelection->getTileX()+1, currentSelection->getTileY())->leave();
			tileManager->getTile(currentSelection->getTileX(), currentSelection->getTileY())->occupy(currentSelection);
			return true;
		}
	}
		else if(tileManager->getTile(selectedTile.x-1, selectedTile.y)->isOccupied()){
		return true;
	}
	return false;
}
bool UnitManager::unitRight(TileManager* tileManager){
	if(!(tileManager->getTile(selectedTile.x+1, selectedTile.y)->isOccupied())){
		if(currentSelection->moveRight()){
			tileManager->getTile(currentSelection->getTileX()-1, currentSelection->getTileY())->leave();
			tileManager->getTile(currentSelection->getTileX(), currentSelection->getTileY())->occupy(currentSelection);
			return true;
		}
	}
		else if(tileManager->getTile(selectedTile.x+1, selectedTile.y)->isOccupied()){
		return true;
	}
	return false;
} 
#pragma endregion