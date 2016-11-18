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
	if (!archerTexture.initialize(graphics,"pictures\\greenArcher.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing greenCavalry texture"));
	}
	if (!archerTexture2.initialize(graphics,"pictures\\greenArcher.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing greenCavalry texture"));
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

		player2Cavalry[i].initialize(144, 144, 8, 2, &cavalryTexture, gamePtr);
		player2Cavalry[i].setActive(false);
		player2Cavalry[i].setVisible(false);

		player1Archers[i].initialize(96, 96, 6, 1, &archerTexture, gamePtr);
		player1Archers[i].setActive(false);
		player1Archers[i].setVisible(false);

		player2Archers[i].initialize(96, 96, 6, 2, &archerTexture2, gamePtr);
		player2Archers[i].setActive(false);
		player2Archers[i].setVisible(false);
	}

	currentSelection = nullptr;
	archerShot = false;
}

void UnitManager::draw(){
	selectionBox.draw(selectionBox.getColorFilter());
	for(int i = 0; i < 10; i++){
		player1Infantry[i].draw();
		player2Infantry[i].draw();
		player1Cavalry[i].draw();
		player2Cavalry[i].draw();
		player1Archers[i].draw();
		player2Archers[i].draw();
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
	archerTexture.onResetDevice();
	archerTexture2.onResetDevice();
}
void UnitManager::onLostDevice(){
	selectionBoxTexture.onLostDevice();
	infantryTexture.onLostDevice();
	infantryTexture2.onLostDevice();
	cavalryTexture.onLostDevice();
	cavalryTexture2.onLostDevice();
	archerTexture.onLostDevice();
	archerTexture2.onLostDevice();
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
				player2Infantry[i].setHP(10);
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
				player2Cavalry[i].setHP(5);
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
				player1Archers[i].setHP(5);
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
				player2Archers[i].setHP(5);
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

bool UnitManager::fight(Unit& opponent, float frameTime, Audio* audio){
	if(currentSelection != nullptr){
		if(currentSelection->getRange() > opponent.getRange() &&
			(abs(currentSelection->getTileX()-opponent.getTileX()) > opponent.getRange() || 
			abs(currentSelection->getTileY()-opponent.getTileY() > opponent.getRange()))){
				if(!archerShot){
					currentSelection->fight(opponent, frameTime, audio);
					archerShot = true;
				}
				if(opponent.getHP() <= 0){
					return opponent.kill(frameTime);
				}
				else{
					archerShot = false;
					return true;
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
				currentSelection->fight(opponent, frameTime, audio); 
			}
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
bool UnitManager::unitUp(TileManager* tileManager, Audio* audio){
	if(currentSelection->moveUp(audio)){
		tileManager->getTile(currentSelection->getTileX(), currentSelection->getTileY()+1)->leave();
		tileManager->getTile(currentSelection->getTileX(), currentSelection->getTileY())->occupy(currentSelection);
		return true;
	}
	return false;
}
bool UnitManager::unitDown(TileManager* tileManager, Audio* audio){
	if(currentSelection->moveDown(audio)){
		tileManager->getTile(currentSelection->getTileX(), currentSelection->getTileY()-1)->leave();
		tileManager->getTile(currentSelection->getTileX(), currentSelection->getTileY())->occupy(currentSelection);
		return true;
	}
	return false;
}
bool UnitManager::unitLeft(TileManager* tileManager, Audio* audio){
	if(currentSelection->moveLeft(audio)){
		tileManager->getTile(currentSelection->getTileX()+1, currentSelection->getTileY())->leave();
		tileManager->getTile(currentSelection->getTileX(), currentSelection->getTileY())->occupy(currentSelection);
		return true;
	}
	return false;
}
bool UnitManager::unitRight(TileManager* tileManager, Audio* audio){
	if(currentSelection->moveRight(audio)){
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
		player1Archers[i].setMovementLeft(player1Archers[i].getMovement());
		player2Archers[i].setMovementLeft(player2Archers[i].getMovement());
	}
}
#pragma endregion

#pragma region Higgs
int UnitManager::numActiveUnits() {
	int activeUnits = 0;
	for (int i = 0; i < 10; i++)
	{
		activeUnits += player2Infantry[i].getActive();
		activeUnits += player2Cavalry[i].getActive();
	}
	return activeUnits;
}

//Returns the closest enemy to the selected AI unit
//TODO: Add archer functionality
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
int UnitManager::aiAttackDirection(Unit* target, Unit* aiUnit, int& x, int& y) {
	x = aiUnit->getTileX();
	y = aiUnit->getTileY();

	VECTOR2 dir = D3DXVECTOR2(target->getTileX() - x, target->getTileY() - y);//*aiUnit->getCenter() - *target->getCenter();
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