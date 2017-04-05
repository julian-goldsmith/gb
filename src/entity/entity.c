#include "oam.h"
#include "gb.h"
#include "entity.h"

const e_drawfn_t e_drawfn_table[3] =
{
	e_generic_draw,
	e_player_draw,
	e_projectile_draw
};

const e_thinkfn_t e_thinkfn_table[3] =
{
	e_generic_think,
	e_player_think,
	e_projectile_think
};

e_generic_t entity_list[64];

e_generic_t* e_create_new(unsigned char type)
{
	int i;
	e_generic_t *e;
	
	for(i = 0; i < 64; i++)
	{
		e = &entity_list[i];
		if(e->alive == 0)
		{
			e->type = type;
			e->alive = 1;
			return e;
		}
	}
	
	while(1);
	return (e_generic_t*) 0x0000;
}

extern void mem_set(unsigned char* dest, unsigned char value, unsigned int n);

void e_init()
{
	mem_set(entity_list, 0, 64 * sizeof(e_generic_t));
}

void e_all_think()
{
	unsigned int i;
	e_generic_t *e = entity_list;
	
	for(i = 0; i < 64; i++)
	{
		if(e->alive != 0)
		{
			if(e->type > 4)
			{
				while(1);
			}
			
			e_thinkfn_table[e->type](e);
		}
		
		e++;
	}
}

void e_all_draw()
{
	unsigned int i;
	
	for(i = 0; i < 64; i++)
	{
		e_generic_t *e = &entity_list[i];
		
		if(e->alive != 0)
		{
			e_drawfn_table[e->type](e);
		}
	}
}

void e_generic_draw(e_generic_t *e)
{
	e->type;							// eat warning
}

void e_generic_think(e_generic_t *e)
{
	e->alive = 0;
}
