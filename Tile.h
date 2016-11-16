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

	bool initialize(Graphics*, TextureManager*, TerrainTypeEnum, int, int, Game*);

	Entity* getUnit() { return unit; };
	TerrainTypeEnum getTerrain() { return terrainType; };
	bool isOccupied() { return occupied; };
	
	void setVisible() { visible = true; };
	void setInvisible() { visible = false; };


private:
	Entity* unit;

	TerrainTypeEnum terrainType;

	bool occupied;
};
#pragma endregion
