#include "Tile.h"

#pragma region Higgs
Tile::Tile(void) {}

//Tile::Tile(TileManager* T, int type) {}


bool Tile::initialize(Graphics* graphics, TextureManager* tileTexture, TerrainTypeEnum terrain, int x, int y, Game* game) {
	unit = nullptr;
	occupied = false;
	terrainType = terrain;
	visible = false;
	
	setX(x * TERRAIN_WIDTH);
	setY(y * TERRAIN_HEIGHT);
	setScale(TERRAIN_SCALE);

	return Entity::initialize(game, TERRAIN_WIDTH, TERRAIN_HEIGHT, 0, tileTexture);
}

#pragma endregion