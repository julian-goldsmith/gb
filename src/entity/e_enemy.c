#include "oam.h"
#include "entity.h"

void e_enemy_init(e_generic_t *e, unsigned int x, unsigned int y)
{
	e_enemy_t* enemy = (e_enemy_t*) e;
	enemy->x = x;
	enemy->y = y;
	enemy->oam = oam_create();
	enemy->frames_since_shot = 0;
}

void e_enemy_draw(e_generic_t *e)
{
	e_enemy_t *enemy= (e_enemy_t*) e;
	oam_entry_t *oam = enemy->oam;
	
	oam->x = enemy->x;
	oam->y = enemy->y;
	oam->tile = 0x05;
	oam->flags = 1 << 5;
}

void e_enemy_think(e_generic_t *e)
{
	e_enemy_t *enemy= (e_enemy_t*) e;
	
	if(enemy->frames_since_shot < 0xff)
	{
		enemy->frames_since_shot++;
	}
	
	// A button
	if(enemy->frames_since_shot > 30 && temp_pad & 0x0100)
	{
		e_projectile_t *proj = (e_projectile_t*) e_create_new(E_TYPE_PROJECTILE, enemy->x, enemy->y);
		
		enemy->frames_since_shot = 0;
	}
	
	if(enemy->x > 0xA8)
	{
		enemy->alive = 0;
		oam_destroy(enemy->oam);
	}
}