#include "unitManager.h"


UnitManager::UnitManager(void)
{
}


UnitManager::~UnitManager(void)
{
}

void UnitManager::initialize(Game *gamePtr, Graphics* graphics){
	if (!infantryTexture.initialize(graphics,"pictures\\greenKnight.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing greenKnight texture"));
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
		player1Infantry[i].setActive(false);
		player1Infantry[i].setVisible(false);
		if(i == 1){
			player1Infantry[i].setVisible(true);
		}
	}
}

void UnitManager::draw(){
	for(int i = 0; i < 10; i++){
		player1Infantry[i].draw();
		player2Infantry[i].draw();
	}
}

void UnitManager::update(float frameTime){
	for(int i = 0; i < 10; i++){
		player1Infantry[i].update(frameTime);
		player2Infantry[i].update(frameTime);
	}
}
void UnitManager::onResetDevice(){
	infantryTexture.onResetDevice();
	infantryTexture2.onResetDevice();
}
void UnitManager::onLostDevice(){
	infantryTexture.onLostDevice();
	infantryTexture2.onLostDevice();
}