#pragma once
#include "tilemanager.h"
#include "graphics.h"
#include "image.h"
#include "entity.h"
#include "game.h"
#include "textureManager.h"


#pragma region Higgs
class Tile : public Game
{
public:
	Tile(void);
	Tile(TileManager*, int);
	~Tile(void);

	void battle();


private:
	Entity* unit;

	Image terrainImg;
	TerrainTypeEnum terrainType;

	bool isOccupied;
};
#pragma endregion
