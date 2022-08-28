#pragma once

#include "field.h"				// for field class
#include "position2d.h"
#include "globals.h"

// class map represents a 2D map of tiles
// with MaxX, MaxY tiles
// a map can be loaded from a file (ascii txt)
class Map
{
public:
	Map(clan::Canvas& canvas);
	~Map(void);
	void render();									// renders a map
	
private:
	void readLevelFile(std::string file);			// read a level file from disk
	void parseTiles(char identifier, Position2D position);
	void readTiles();
	int isValid(Position2D &p);
    std::string convertPath(std::string path);          // converts a file path to windows if needed

	clan::Canvas _canvas;
    Field** _fields;									// all tiles of a map
	int _width;
	int _height;
	std::map<std::string, clan::Image*> _tilesMap;		// all images used by this map
};
