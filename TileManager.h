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
	~TileManager(void);
	
	bool initialize(Graphics* graphics, int x, int y, Game* game);

	void draw(int x, int y);

	Tile* getTile(int x, int y) {return &tiles[x][y];}
	void onLostDevice();
	void onResetDevice();
	//void battle(Tile* t1, Tile* t2);

private:
	TextureManager grassTexture1;
	TextureManager grassTexture2;
	TextureManager grassTexture3;
	TextureManager hillsTexture;
	TextureManager forestTexture;	

	Tile** tiles;
};

#pragma endregion