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
	//x & y correspond to grid coordinates, not screen coordinates
	Tile* getTile(int x, int y) {return &tiles[x][y]; };

	//Width of grid, in tiles
	int getWidth() { return width; };
	//Height of grid, in tiles
	int getHeight() { return height; };

	void levelTwoSetup(Graphics* graphics, int x1, int y1, int x2, int y2, Game* game);
	void tilesReset();
	void setTileVisibility(bool);
	void draw(); 
	void draw(int);
	void onLostDevice();
	void onResetDevice();
	

private:
	int width;
	int height;

	Image cPoint1Image;
	Image cPoint2Image;

	TextureManager grassTexture1;
	TextureManager grassTexture2;
	TextureManager grassTexture3;
	TextureManager forestTexture1;
	TextureManager forestTexture2;
	TextureManager cPoint1Texture;
	TextureManager cPoint2Texture;
	TextureManager hillsTexture;

	TerrainTypeEnum tileTerrain;

	Tile** tiles;
};

#pragma endregion