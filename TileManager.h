#pragma once
#include "entity.h"
#include "game.h"
#include "graphics.h"
#include "textureManager.h"
#include "image.h"
#include "constants.h"
#include "Tile.h"

#pragma region Higgs
class TileManager
{
public:
	TileManager(void);
	TileManager(Graphics* graphics, int x, int y, Game* game);
	~TileManager(void);
	

	Tile* getTile(int x, int y) {return &tiles[x][y]; };
	void onLostDevice();
	//void battle(Tile* t1, Tile* t2);

private:
	TextureManager plainsTexture;
	TextureManager hillsTexture;
	TextureManager forestTexture;	

	Tile** tiles;
};

#pragma endregion