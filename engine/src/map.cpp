#include "map.h"

Map::Map(clan::Canvas& canvas)
{
	_canvas = canvas;
	_height = 0;
	_width = 0;
	readTiles();
    readLevelFile(convertPath("./Data/Maps/map1.txt"));		    // load first map by default
	srand(clock_t(0));
}

Map::~Map(void)
{
	delete[] _fields;
}

void Map::readLevelFile(std::string file) 
{
	std::string line;
	std::ifstream iFile(file);
	int x;
	// first compute width and height
	for (int y = 0; !iFile.eof(); ++y) 
	{
		getline(iFile, line);
		x = 0;
		if(y == 0)
		{
			for (std::string::iterator it = line.begin(); it != line.end(); ++it) 
			{
				_width++;
			}
		}
		_height = y + 1;
	}
	iFile.clear();
	iFile.seekg(0);
	// read map
	_fields = new Field*[_height];
	for (int y = 0; !iFile.eof(); ++y)
	{
		_fields[y] = new Field[_width];
		getline(iFile, line);
		x = 0;
		for (std::string::iterator it = line.begin(); it != line.end(); ++it) {
			parseTiles(*it, Position2D(x++, y));
		}
	}
	iFile.close();
}

// render every tile of this map
void Map::render()
{
	clan::Image* tile;
	float x_koord;
	float y_koord;
	float scaleFactor;
#if SMALL==1
	scaleFactor = TILES_SCALE_FACTOR_SMALL;
#else
	scaleFactor = TILES_SCALE_FACTOR;
#endif

	for (int x = 0; x < _height; ++x)
	{
		for (int y = 0; y < _width; ++y)
		{
			tile = _fields[x][y].getTile();
			if (tile != NULL) 
			{
				x_koord = static_cast<float>((x*scaleFactor*TILES_SIZE_X) + ((y % 2 == 0) ? TILES_OFFSET_X * scaleFactor : 0));
				y_koord = static_cast<float>((y*scaleFactor*TILES_OFFSET_Y));
				tile->set_scale(scaleFactor, scaleFactor);
				tile->draw(_canvas, x_koord, y_koord);
			}
		}
	}
}

// create tile for given position and information from map file
void Map::parseTiles(char identifier, Position2D position) 
{
	int value = 0;
	int r = 0;

	clan::Image* surface = NULL;
	switch (identifier) {
		case '0': surface = _tilesMap["water"]; value = 0; break;
		case '1': surface = _tilesMap["sand"]; value = 1; break;
		case '2': surface = _tilesMap["gras"]; value = 2; break;
		case '3':
			r = rand() % 3;
			switch (r)
			{
			case 0: surface = _tilesMap["trees2"]; break;
			case 1: surface = _tilesMap["trees1"]; break;
			case 2: surface = _tilesMap["trees"]; break;
			}
			value = 3;
			break;
		case '5': surface = _tilesMap["mountain_s"]; value = 5; break;
		case '6': surface = _tilesMap["mountain_l"]; value = 5; break;
		default: break;				
	}

	_fields[position._y][position._x] = Field(surface, value);
}

// get all defined images for tiles, enemy, start, goal/target and path
void Map::readTiles(void)
{
    _tilesMap.insert(std::map<std::string, clan::Image*>::value_type("water", new clan::Image(_canvas, convertPath("./Data/Tiles/water.png"))));
	_tilesMap.insert(std::map<std::string, clan::Image*>::value_type("gras", new clan::Image(_canvas, convertPath("./Data/Tiles/gras.png"))));
	_tilesMap.insert(std::map<std::string, clan::Image*>::value_type("sand", new clan::Image(_canvas, convertPath("./Data/Tiles/sand.png"))));

	_tilesMap.insert(std::map<std::string, clan::Image*>::value_type("trees", new clan::Image(_canvas, convertPath("./Data/Tiles/trees_1.png"))));
	_tilesMap.insert(std::map<std::string, clan::Image*>::value_type("trees1", new clan::Image(_canvas, convertPath("./Data/Tiles/trees_2.png"))));
	_tilesMap.insert(std::map<std::string, clan::Image*>::value_type("trees2", new clan::Image(_canvas, convertPath("./Data/Tiles/trees_full.png"))));

	_tilesMap.insert(std::map<std::string, clan::Image*>::value_type("mountain_s", new clan::Image(_canvas, convertPath("./Data/Tiles/mountain_small.png"))));
	_tilesMap.insert(std::map<std::string, clan::Image*>::value_type("mountain_l", new clan::Image(_canvas, convertPath("./Data/Tiles/mountain_large.png"))));

	_tilesMap.insert(std::map<std::string, clan::Image*>::value_type("enemy", new clan::Image(_canvas, convertPath("./Data/Tiles/goblin.png"))));
	_tilesMap.insert(std::map<std::string, clan::Image*>::value_type("start", new clan::Image(_canvas, convertPath("./Data/Tiles/pirate.png"))));
	_tilesMap.insert(std::map<std::string, clan::Image*>::value_type("target", new clan::Image(_canvas, convertPath("./Data/Tiles/treasure.png"))));
	_tilesMap.insert(std::map<std::string, clan::Image*>::value_type("path", new clan::Image(_canvas, convertPath("./Data/Tiles/path.png"))));
	_tilesMap.insert(std::map<std::string, clan::Image*>::value_type("path_enemy1", new clan::Image(_canvas, convertPath("./Data/Tiles/path_enemy1.png"))));
	_tilesMap.insert(std::map<std::string, clan::Image*>::value_type("path_enemy2", new clan::Image(_canvas, convertPath("./Data/Tiles/path_enemy2.png"))));
}

int Map::isValid(Position2D &p)
{
	// check if this field is valid
	// special fields also are not valid --> 0...for water!
	if (p._x < 0 || p._x >= _width || p._y < 0 || p._y >= _height)
		return 0;
	return 1;
}

std::string Map::convertPath(std::string path)
{
#if defined(WIN32)
    std::replace(path.begin(), path.end(), '/', '\\');      // Linux to Windows
#else
    std::replace(path.begin(), path.end(), '\\', '/');      // Windows to Linux
#endif
    return path;
}
