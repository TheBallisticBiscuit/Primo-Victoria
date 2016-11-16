#include "Tile.h"

#pragma region Higgs
Tile::Tile(void) {}

//Tile::Tile(TileManager* T, int type) {}


bool Tile::initialize(Graphics* graphics, TextureManager* tileTexture, int x, int y, Game* game) {
	unit = nullptr;
	occupied = false;
	terrainType = Plains;
	visible = true;
	
	setX(x * TERRAIN_WIDTH);
	setY(y * TERRAIN_HEIGHT);
	setScale(TERRAIN_SCALE);

	return Entity::initialize(game, TERRAIN_WIDTH, TERRAIN_HEIGHT, 0, tileTexture);
}

#pragma region Newell
void Tile::occupy(Unit* newUnit){
	unit = newUnit;
	occupied = true;
}

void Tile::leave(){
	unit = nullptr;
	occupied = false;
}
#pragma endregion
#pragma endregion