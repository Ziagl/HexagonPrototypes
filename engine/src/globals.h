#pragma once

// map params
#define TILES_SCALE_FACTOR 1
#define TILES_SCALE_FACTOR_SMALL 0.5
#define TILES_SIZE_X 70//140
#define TILES_SIZE_Y 76//160
#define TILES_OFFSET_X 35//70
#define TILES_OFFSET_Y 57//120

// HEXAGON
#define NEIGHBOURS 6

// global arrays
static const int xofs[NEIGHBOURS] = { -1, 0, -1, 1, -1, 0 };		// neighbours X
static const int xofsEven[NEIGHBOURS] = { 0, 1, -1, 1, 0, 1 };
static const int yofs[NEIGHBOURS] = { -1, -1, 0, 0, 1, 1 };			// neighbours Y
