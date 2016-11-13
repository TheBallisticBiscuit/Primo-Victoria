#include "unitManager.h"


UnitManager::UnitManager(void)
{
}


UnitManager::~UnitManager(void)
{
}

bool UnitManager::initialize(Game *gamePtr, Graphics* graphics){
	if (!infantryTexture.initialize(graphics,"pictures\\greenKnightRun.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));
	}
	player1Infantry = new Infantry[10];
	for(int i = 0; i < 10; i++){
		player1Infantry[i].initialize(96, 96, 3, &infantryTexture, gamePtr);
	}
	player2Infantry = new Infantry[10];
	for(int i = 0; i < 10; i++){
		player2Infantry[i].initialize(96, 96, 3, &infantryTexture2, gamePtr);
	}
}