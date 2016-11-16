#pragma once
#include "game.h"
#include "graphics.h"
#include "textureManager.h"
#include "image.h"
#include "entity.h"
#include "constants.h"


#pragma region Higgs
class Tile : public Entity
{
public:
	Tile(void);

	bool initialize(Graphics* graphics, TextureManager* textureManager, int x, int y, Game* game);
	bool isOccupied() { return occupied; };
	
	Entity* getUnit() { return unit; };
	TerrainTypeEnum getTerrain() { return terrainType; };
	void occupy(Entity* newUnit);

private:
	Entity* unit;

	TerrainTypeEnum terrainType;

	bool occupied;
};
#pragma endregion
