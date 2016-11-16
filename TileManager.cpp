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
	if (!grassTexture3.initialize(graphics, GRASS_3_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "GrassTexture3 init failure"));
	if (!forestTexture1.initialize(graphics, FOREST_1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "ForestTexture1 init failure"));
	if (!forestTexture2.initialize(graphics, FOREST_2_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "ForestTexture2 init failure"));
	
	int r; //What terrain type the tile will be
	int s; //What texture for that terrain
	srand(time(0));

	tiles = new Tile*[x];

	for (int i = 0; i < x; i++) {
		tiles[i] = new Tile[y];

		for (int j = 0; j < y; j++) {
			r = rand()%2; 

			if (r == 0) { //Grass
				tileTerrain = Plains;
				s = rand()%3;
				if (s == 0) {
					if (!tiles[i][j].initialize(graphics, &grassTexture1, tileTerrain, i, j, game)) 
						throw(GameError(gameErrorNS::FATAL_ERROR, "Tile[" + std::to_string(i) + "][" + std::to_string(j) + "] init fail"));
				}
				if (s == 1) {
					if (!tiles[i][j].initialize(graphics, &grassTexture2, tileTerrain, i, j, game)) 
						throw(GameError(gameErrorNS::FATAL_ERROR, "Tile[" + std::to_string(i) + "][" + std::to_string(j) + "] init fail"));
				}
				else {
					if (!tiles[i][j].initialize(graphics, &grassTexture3, tileTerrain, i, j, game)) 
						throw(GameError(gameErrorNS::FATAL_ERROR, "Tile[" + std::to_string(i) + "][" + std::to_string(j) + "] init fail"));
				}
			}

			else if (r == 1) { //Forest
				tileTerrain = Forest;
				s = rand()%2;
				if (s == 0) {
					if (!tiles[i][j].initialize(graphics, &forestTexture1, tileTerrain, i, j, game)) 
						throw(GameError(gameErrorNS::FATAL_ERROR, "Tile[" + std::to_string(i) + "][" + std::to_string(j) + "] init fail"));
				}
				else {
					if (!tiles[i][j].initialize(graphics, &forestTexture2, tileTerrain, i, j, game)) 
						throw(GameError(gameErrorNS::FATAL_ERROR, "Tile[" + std::to_string(i) + "][" + std::to_string(j) + "] init fail"));
				}
			}

			//else { //Hills
			//}
		}
	}	
	return 1;
}

void TileManager::setTileVisibility(bool isVisible) {
	if (isVisible == true) {
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 5; j++) {
				tiles[i][j].setVisible();
			}
		}
	}
	else {
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 5; j++) {
				tiles[i][j].setInvisible();
			}
		}
	}
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
	grassTexture2.onLostDevice();
	grassTexture3.onLostDevice();
	forestTexture1.onLostDevice();
	forestTexture2.onLostDevice();
	hillsTexture.onLostDevice();
}

void TileManager::onResetDevice() {
	grassTexture1.onResetDevice();
	grassTexture2.onResetDevice();
	grassTexture3.onResetDevice();
	forestTexture1.onResetDevice();
	forestTexture2.onResetDevice();
	hillsTexture.onResetDevice();
}
 
#pragma endregion