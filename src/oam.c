#include "oam.h"

#define OAMBUF ((oam_entry_t*)0xC000)

extern void mem_set(unsigned char* dest, unsigned char value, unsigned int n);

void oam_init()
{
	mem_set((unsigned char*) OAMBUF, 0, 160 * sizeof(oam_entry_t));
}

oam_entry_t* oam_create()
{
	oam_entry_t* oam;
	
	for(oam = OAMBUF; oam < OAMBUF + 160; oam++)
	{
		if(oam->tile == 0)
		{
			return oam;
		}
	}
	
	// default option
	return OAMBUF;
}

void oam_destroy(oam_entry_t* oam)
{
	oam->tile = 0;
}