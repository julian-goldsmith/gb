#define LCDC (*(volatile unsigned char*)0xFF40)
#define STAT ((volatile unsigned char*)0xFF41)
#define BGTILEDATA ((volatile unsigned char*)0x8000)
#define BGMAPDATA ((volatile unsigned char*)0x9800)
#define BGP ((volatile unsigned char*)0xFF47)
#define OBP0 ((volatile unsigned char*)0xFF48)
#define OBP1 ((volatile unsigned char*)0xFF49)
#define IE (*(volatile unsigned char*)0xFFFF)
#define SCX (*(volatile unsigned char*)0xFF43)
#define PAD (*(volatile unsigned char*)0xFF00)