typedef struct
{
	unsigned char y;
	unsigned char x;
	unsigned char tile;
	unsigned char flags;
} oam_entry_t;

void oam_init();
oam_entry_t* oam_create();
void oam_destroy(oam_entry_t* oam);

