#pragma once
#include "game.h"
#include "graphics.h"
#include "textureManager.h"
#include "image.h"
#include "entity.h"
#include "constants.h"
#include "unit.h"


#pragma region Higgs
class Tile : public Entity
{
public:
	Tile(void);

	bool initialize(Graphics* graphics, TextureManager* textureManager, int x, int y, Game* game);
	bool isOccupied() { return occupied; };
	
	Unit* getUnit() { return unit; };
	TerrainTypeEnum getTerrain() { return terrainType; };
	void occupy(Unit* newUnit);
	void leave();
private:
	Unit* unit;

	TerrainTypeEnum terrainType;

	bool occupied;
};
#pragma endregion
