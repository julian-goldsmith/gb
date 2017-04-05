#include "gb.h"
#include "oam.h"
#include "world.h"
#include "maps.h"

unsigned char worldpos;		// this is used in start.asm to set SCX

void world_draw()
{
	worldpos++;
}

void world_think()
{
}

void world_set_position(unsigned char new_pos)
{
	worldpos = new_pos;
}

unsigned int world_get_collision(unsigned int x, unsigned int y)
{
	unsigned int tilex = x / 8;
	unsigned int tiley = y / 8 - 1;
	unsigned int tileidx = tiley * MapWidth + tilex;
	
	return MapPLN1[tileidx];
}