#include "tiles.h"
#include "maps.h"
#include "gb.h"
#include "oam.h"
#include "entity.h"
#include "world.h"

const char palette = 0xE4;

void mem_copy_vram(const unsigned char* src, unsigned char* dest, int count);
void mem_copy(const char* src, char* dest, int count);
void wait_lcd_ready();
void wait_vsync();
void enable_ints();
unsigned int read_pad();

void oamdma();

volatile int vsync;

unsigned int read_pad()
{
	unsigned char temp_pad;
	unsigned int temp_ret;
	
	// read buttons
	PAD = ~(1<<5);
	temp_pad = ~PAD;
	temp_ret = (unsigned int) temp_pad;
	temp_ret <<= 8;
	
	// read directional pad
	PAD = ~(1<<4);						// dpad is bit 4, selected by a 0
	temp_pad = ~PAD;					// bits on PAD are inverted
	temp_ret |= (unsigned int) temp_pad;
	
	return temp_ret;
}

void main()
{
	e_player_t *player;
	
	oam_init();
	e_init();
	
	IE = 0x01;		// set vblank interrupt bit
	vsync = 0;
	
	// copy our vblank DMA routine
	mem_copy((const char*) oamdma, 0xFF80, 0x0B);
	
	// set LCD control
	LCDC = 0x93;
	
	// set palettes
	*BGP = palette;
	*OBP0 = palette;
	*OBP1 = palette;
	
	// copy tile data and background map
	wait_lcd_ready();
	mem_copy(TileLabel, BGTILEDATA, TileLabelLen);
	mem_copy_vram(Map, BGMAPDATA, MapWidth*MapHeight);
	
	// create player
	player = (e_player_t*) e_create_new(E_TYPE_PLAYER);
	player->x = 0x24;
	player->y = 0x24;
	player->oam = oam_create();
	player->frames_since_shot = 0xff;
	
	enable_ints();
	
	while(1)
	{
		world_think();
		e_all_think();
		wait_vsync();
		world_draw();
		e_all_draw();
	}
}

void wait_lcd_ready()
{
	while(!(*STAT) & 2);
}

void wait_vsync()
{
	while(!vsync);
	vsync = 0;
}

void mem_copy(const char* src, char* dest, int count)
{
	while(count--)
	{
		*dest++ = *src++;
	}
}

void mem_copy_vram(const unsigned char* src, unsigned char* dest, int count)
{
	while(count--)
	{
		wait_lcd_ready();
		*dest++ = *src++;
	}
}

void mem_set(unsigned char* dest, unsigned char value, unsigned int n)
{
	while(n--)
	{
		*dest++ = value;
	}
}