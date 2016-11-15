#include "TileManager.h"

#pragma region Higgs
TileManager::TileManager(void) {
	tiles = nullptr;
}

TileManager::TileManager(Graphics* graphics, int x, int y, Game* game) {
	tiles = new Tile*[x];
	for (int i = 0; i < x; i++) {
		tiles[i] = new Tile[y];
		for (int j = 0; j < y; j++) {
			tiles[i][j].initialize(graphics, &plainsTexture, game);
			tiles[i][j].setX(i*TERRAIN_WIDTH);
			tiles[i][j].setY(j*TERRAIN_HEIGHT);
		}
	}	
}

TileManager::~TileManager(void){
}

void TileManager::update() {
}

//void TileManager::battle(Tile* t1, Tile* t2) {};

#pragma endregion