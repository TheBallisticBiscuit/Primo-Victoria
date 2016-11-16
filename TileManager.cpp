#include "TileManager.h"
#include <random>
#include <ctime>

#pragma region Higgs
TileManager::TileManager(void) { tiles = nullptr; }

TileManager::~TileManager(void){
}

bool TileManager::initialize(Graphics* graphics, int x, int y, Game* game) {
	if (!grassTexture1.initialize(graphics, GRASS_1_IMAGE)) 
		throw(GameError(gameErrorNS::FATAL_ERROR, "GrassTexture1 init failure"));
	if (!grassTexture2.initialize(graphics, GRASS_2_IMAGE)) 
		throw(GameError(gameErrorNS::FATAL_ERROR, "GrassTexture2 init failure"));
	

	
	srand(time(0));

	tiles = new Tile*[x];
	for (int i = 0; i < x; i++) {
		tiles[i] = new Tile[y];
		for (int j = 0; j < y; j++) {
			if (!tiles[i][j].initialize(graphics, &grassTexture1, i, j, game)) {
				throw(GameError(gameErrorNS::FATAL_ERROR, "Tile[" + std::to_string(i) + 
					"][" + std::to_string(j) + "] init fail"));
				return 0;
			}
			//tiles[i][j].setX((i)*TERRAIN_WIDTH);
			//tiles[i][j].setY((j)*TERRAIN_HEIGHT);
		}
	}	
	return 1;
}

void TileManager::draw(int x, int y) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			tiles[i][j].draw();
		}
	}
}


void TileManager::onLostDevice() {
	grassTexture1.onLostDevice();
	hillsTexture.onLostDevice();
	forestTexture.onLostDevice();
}

void TileManager::onResetDevice() {
	grassTexture1.onResetDevice();
	hillsTexture.onResetDevice();
	forestTexture.onResetDevice();
}

 
#pragma endregion