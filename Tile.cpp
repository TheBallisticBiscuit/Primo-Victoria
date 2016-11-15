#include "Tile.h"

#pragma region Higgs
Tile::Tile(void) {}

//Tile::Tile(TileManager* T, int type) {}


bool Tile::initialize(Graphics* graphics, TextureManager* tileTexture, Game* game) {
	if (!tileTexture->initialize(graphics, TEMP_GRASS))
		throw (GameError(gameErrorNS::FATAL_ERROR, "Tile initialization failure"));

	unit = nullptr;
	occupied = false;
	
	return Entity::initialize(game, TERRAIN_WIDTH, TERRAIN_HEIGHT, 0, tileTexture);
}

#pragma endregion