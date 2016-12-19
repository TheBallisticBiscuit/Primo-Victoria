#include "TileManager.h"
#include <random>
#include <ctime>

#pragma region Higgs
TileManager::TileManager(void) { tiles = nullptr; }

TileManager::~TileManager(void){
	for (int i = 0; i < 12; i++)
	{
		delete[] tiles[i];
	}
	delete[] tiles;
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
	if (!forestTexture3.initialize(graphics, FOREST_3_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "ForestTexture3 init failure"));
	if (!forestTexture4.initialize(graphics, FOREST_4_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "ForestTexture4 init failure"));
	if (!cPoint1Texture.initialize(graphics, CAPTURE_POINT_1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "CapturePoint1 init failure"));
	if (!cPoint2Texture.initialize(graphics, CAPTURE_POINT_2))
		throw(GameError(gameErrorNS::FATAL_ERROR, "CapturePoint2 init failure"));
	
	width = x;
	height = y;

	int r; //What terrain type the tile will be
	int s; //What texture for that terrain
	srand(time(0));

	tiles = new Tile*[x];

	for (int i = 0; i < x; i++) {
		tiles[i] = new Tile[y];

		for (int j = 0; j < y; j++) {
			r = rand()%2; 

			if (r == 0) { //Grass
				s = rand()%3;
				if (s == 0) {
					if (!tiles[i][j].initialize(graphics, &grassTexture1, Plains, i, j, game)) 
						throw(GameError(gameErrorNS::FATAL_ERROR, "Plains1 tile initialize failure"));
				}
				if (s == 1) {
					if (!tiles[i][j].initialize(graphics, &grassTexture2, Plains, i, j, game)) 
						throw(GameError(gameErrorNS::FATAL_ERROR, "Plains2 tile initialize failure"));
				}
				else {
					if (!tiles[i][j].initialize(graphics, &grassTexture3, Plains, i, j, game)) 
						throw(GameError(gameErrorNS::FATAL_ERROR, "Plains3 tile initialize failure"));
				}
			}

			else if (r == 1) { //Forest
				s = rand()%4;
				if (s == 0) {
					if (!tiles[i][j].initialize(graphics, &forestTexture1, Forest, i, j, game)) 
						throw(GameError(gameErrorNS::FATAL_ERROR, "Forest1 tile initialize failure"));
				}
				else if (s == 1){
					if (!tiles[i][j].initialize(graphics, &forestTexture2, Forest, i, j, game)) 
						throw(GameError(gameErrorNS::FATAL_ERROR, "Forest2 tile initialize failure"));
				}
				else if (s == 2) {
					if (!tiles[i][j].initialize(graphics, &forestTexture3, Forest, i, j, game))
						throw(GameError(gameErrorNS::FATAL_ERROR, "Forest3 tile initialize failure"));
				}
				else {
					if (!tiles[i][j].initialize(graphics, &forestTexture4, Forest, i, j, game))
						throw(GameError(gameErrorNS::FATAL_ERROR, "Forest3 tile initialize failure"));
				}
			}
		}
	}	
	return 1;
}

void TileManager::levelTwoSetup(Graphics* graphics, int x1, int y1, int x2, int y2, Game* game) {
	//if (!tiles[x1][y1].initialize(graphics, &cPoint1Texture, CapturePoint, x1, y1, game))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Tile[" + std::to_string(x1) + "][" + std::to_string(y1) + "] init fail"));
	//if (!tiles[x2][y2].initialize(graphics, &cPoint2Texture, CapturePoint, x2, y2, game))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Tile[" + std::to_string(x2) + "][" + std::to_string(y2) + "] init fail"));
	if (!cPoint1Image.initialize(graphics, 0,0,0,&cPoint1Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "CapturePoint1 init failure"));
	cPoint1Image.setX(x1*TERRAIN_WIDTH);
	cPoint1Image.setY(y1*TERRAIN_HEIGHT);
	if (!cPoint2Image.initialize(graphics, 0,0,0,&cPoint2Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "CapturePoint2 init failure"));
	cPoint2Image.setX(x2*TERRAIN_WIDTH);
	cPoint2Image.setY(y2*TERRAIN_HEIGHT);
}


void TileManager::tilesReset(){
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			tiles[i][j].leave();
		}
	}
	setTileVisibility(false);
}

void TileManager::setTileVisibility(bool isVisible) {
	if (isVisible == true) {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				tiles[i][j].setVisible();
			}
		}
	}
	else {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				tiles[i][j].setInvisible();
			}
		}
	}
}

void TileManager::draw() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			tiles[i][j].draw();
		}
	}
}

void TileManager::draw(int level) {
	if (level == 2) {
		cPoint1Image.draw();
		cPoint2Image.draw();
	}
}


void TileManager::onLostDevice() {
	grassTexture1.onLostDevice();
	grassTexture2.onLostDevice();
	grassTexture3.onLostDevice();
	forestTexture1.onLostDevice();
	forestTexture2.onLostDevice();
	forestTexture3.onLostDevice();
	forestTexture4.onLostDevice();
	hillsTexture.onLostDevice();
	cPoint1Texture.onLostDevice();
	cPoint2Texture.onLostDevice();
}

void TileManager::onResetDevice() {
	grassTexture1.onResetDevice();
	grassTexture2.onResetDevice();
	grassTexture3.onResetDevice();
	forestTexture1.onResetDevice();
	forestTexture2.onResetDevice();
	forestTexture3.onResetDevice();
	forestTexture4.onResetDevice();
	hillsTexture.onResetDevice();
	cPoint1Texture.onResetDevice();
	cPoint2Texture.onResetDevice();
}
 
#pragma endregion