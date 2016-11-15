#include "Tile.h"

#pragma region Higgs
Tile::Tile(void) {}

//Tile::Tile(TileManager* T, int type) {}


bool Tile::initialize(Graphics* graphics, TextureManager tileTexture, Game* game) {
	unit = nullptr;
	occupied = false;
	terrainType = Plains;

	return Entity::initialize(game, TERRAIN_WIDTH, TERRAIN_HEIGHT, 0, &tileTexture);
}

#pragma endregion