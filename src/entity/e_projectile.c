#include "oam.h"
#include "entity.h"

void e_projectile_draw(e_generic_t *e)
{
	e_projectile_t *proj= (e_projectile_t*) e;
	oam_entry_t *oam = proj->oam;
	
	oam->x = proj->x;
	oam->y = proj->y;
	oam->tile = 0x06;
	oam->flags = 0x00;
}

void e_projectile_think(e_generic_t *e)
{
	e_projectile_t *proj= (e_projectile_t*) e;
	
	proj->x += 2;
	
	if(proj->x > 0xA8)
	{
		proj->alive = 0;
		oam_destroy(proj->oam);
	}
}