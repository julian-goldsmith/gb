// entities
// full length is 16
// type 0x00 is invalid
typedef struct e_generic_s
{
	unsigned char type;
	unsigned char alive;
	char padding[14];
} e_generic_t;

// type 0x01
typedef struct e_player_s
{
	unsigned char type;
	unsigned char alive;
	unsigned char x;
	unsigned char y;
	oam_entry_t *oam;
	unsigned char frames_since_shot;
	char padding[9];
} e_player_t;

// type 0x02
typedef struct e_projectile_s
{
	unsigned char type;
	unsigned char alive;
	unsigned char x;
	unsigned char y;
	oam_entry_t *oam;
	char padding[10];
} e_projectile_t;

typedef void (*e_drawfn_t) (e_generic_t *e);
typedef void (*e_thinkfn_t) (e_generic_t *e);

void e_init();
void e_generic_draw(e_generic_t *e);
void e_generic_think(e_generic_t *e);
void e_player_draw(e_generic_t *e);
void e_player_think(e_generic_t *e);
void e_projectile_draw(e_generic_t *e);
void e_projectile_think(e_generic_t *e);
e_generic_t* e_create_new(unsigned char type);
void e_all_think();
void e_all_draw();

#define E_TYPE_GENERIC		0
#define E_TYPE_PLAYER		1
#define E_TYPE_PROJECTILE	2

