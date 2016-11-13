#pragma once
#include "entity.h"
#include "game.h"
#include "graphics.h"
#include "textureManager.h"
#include "image.h"
#include "Tile.h"

class TileManager :	public Entity
{
public:
	TileManager(void);
	TileManager(int x, int y);
	~TileManager(void);

	void update();

private:
	TextureManager plainsTexture;
	TextureManager hillsTexture;
	TextureManager forestTexture;	

	Tile** tiles;
};

