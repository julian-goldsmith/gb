#include "oam.h"
#include "entity.h"
#include "world.h"

extern unsigned int read_pad();

extern unsigned char worldpos;

void e_player_draw(e_generic_t *e)
{
	e_player_t *player= (e_player_t*) e;
	oam_entry_t *ship = player->oam;
	
	ship->x = player->x;
	ship->y = player->y;
	ship->tile = 0x05;
	ship->flags = 0x00;
}

void e_player_kill(e_generic_t *e)
{
	e_player_t *player = (e_player_t*) e;
	
	player->x = 0x24;
	player->y = 0x24;
	
	world_set_position(0);
}

void e_player_think(e_generic_t *e)
{
	unsigned int temp_pad;
	e_player_t *player= (e_player_t*) e;
	
	// read pad
	temp_pad = read_pad();
	
	if(temp_pad & 0x01)					// right
	{
		player->x++;
	}
	
	if(temp_pad & 0x02)					// left
	{
		player->x--;
	}
	
	if(temp_pad & 0x04)					// up
	{
		player->y--;
	}
	
	if(temp_pad & 0x08)					// down
	{
		player->y++;
	}
	
	if(world_get_collision(player->x + worldpos, player->y) == 1)
	{
		e_player_kill(e);
	}
	
	if(player->frames_since_shot < 0xff)
	{
		player->frames_since_shot++;
	}
	
	// A (?) button
	if(player->frames_since_shot > 30 && temp_pad & 0x0100)
	{
		e_projectile_t *proj = (e_projectile_t*) e_create_new(E_TYPE_PROJECTILE);
		proj->x = player->x;
		proj->y = player->y;
		proj->oam = oam_create();
		
		player->frames_since_shot = 0;
	}
}