//gcc pcx.c bmp.c image2tig.c -s -O1 -lm  -o image2tig

typedef struct
{
	unsigned char *pixel,*palette;
	unsigned int size,palsize,pixelsize;
	unsigned short w,h;
	unsigned char bpp,format;
	
}Texture;

Texture *Load_bmp(const char *filename);
Texture *Load_png(const char *filename);
Texture *Load_pcx(const char *filename);
Texture *Load_image(const char *filename);

#define FORMAT_RGBA8888	0x01
#define FORMAT_RGBA1555	0x02
#define FORMAT_RGB233   0x03
#define FORMAT_RGB888   0x04
#define FORMAT_RGB8888	0x05
#define FORMAT_RGB565   0x06
#define FORMAT_RGB555   0x07
#define FORMAT_RGB4444  0x08

#define FORMAT_BGR	0x80

#define FORMAT_8BPP	0x10
#define FORMAT_4BPP	0x11
#define FORMAT_2BPP	0x12

#define FORMAT_LUM	0x20
#define FORMAT_LUMA	0x21

#define TEXTURE_SIGNATURE "TIG\0"
#define TEXTURE_PAL4 0 // 4 bit CLUT
#define TEXTURE_PAL8 1 // 8 bit CLUT
#define TEXTURE_RGB1555 2 // 16 bit Direct

typedef struct
{
    unsigned char signature[4];
    unsigned char mode, reserved;
    unsigned short width, height;

	unsigned short pitch, unk2, unk3;
} TEXTURE_HEADER;

static inline void TIG_INIT(TEXTURE_HEADER * texthead,unsigned short width,unsigned short height,char mode)
{
	texthead->signature[0] = 'T';
	texthead->signature[1] = 'I';
	texthead->signature[2] = 'G';
	texthead->signature[3] = 0;

	texthead->reserved = 0;
	texthead->pitch = width<<1;
	texthead->unk2 = 0;
	texthead->unk3 = 0;

	texthead->width  = width;
	texthead->height = height;

	texthead->mode = mode;

	if(mode == TEXTURE_PAL4)
		texthead->pitch = width>>1;

	if(mode == TEXTURE_PAL8)
		texthead->pitch = width;

	if(mode == TEXTURE_RGB1555)
		texthead->pitch = width<<1;

}
