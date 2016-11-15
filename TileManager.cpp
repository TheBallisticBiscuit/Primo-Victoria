#include "TileManager.h"

#pragma region Higgs
TileManager::TileManager(void) {
	tiles = nullptr;
}

TileManager::TileManager(Graphics* graphics, int x, int y, Game* game) {
	if (!plainsTexture.initialize(graphics, TEMP_GRASS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "PlainsTexture init failure"));
	
	tiles = new Tile*[x];
	for (int i = 0; i < x; i++) {
		tiles[i] = new Tile[y];
		for (int j = 0; j < y; j++) {
			if (tiles[i][j].initialize(graphics, plainsTexture, game)) {
				throw(GameError(gameErrorNS::FATAL_ERROR, "Tile[" + std::to_string(i) + 
				"][" + std::to_string(j) + "] init fail"));
				game->exitGame();
			}
			tiles[i][j].setX((i-1)*TERRAIN_WIDTH);
			tiles[i][j].setY((j-1)*TERRAIN_HEIGHT);
		}
	}	
}

TileManager::~TileManager(void){
}

void TileManager::onLostDevice() {
	plainsTexture.onLostDevice();
	hillsTexture.onLostDevice();
	forestTexture.onLostDevice();
}

//void TileManager::battle(Tile* t1, Tile* t2) {};

#pragma endregion