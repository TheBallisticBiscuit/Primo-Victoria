#include "TileManager.h"


TileManager::TileManager(void) {
	tiles = new Tile*[5];
	for (int i = 0; i < 5; i++) {
		tiles[i] = new Tile[5];
	}

	if (!plainsTexture.initialize(graphics, TEMP_GRASS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "No Grass!"));
}

TileManager::TileManager(int x, int y) {
	tiles = new Tile*[x];
	for (int i = 0; i < y; i++) {
		tiles[i] = new Tile[y];
	}
	
}

TileManager::~TileManager(void){
}

void TileManager::update() {

}
