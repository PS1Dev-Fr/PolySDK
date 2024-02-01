#define TEXTURE_SIGNATURE "TIG\0"
#define TEXTURE_PAL4 0 // 4 bit CLUT
#define TEXTURE_PAL8 1 // 8 bit CLUT
#define TEXTURE_RGB1555 2 // 16 bit Direct

typedef struct
{
    unsigned char signature[4];
    unsigned char mode, reserved;
    unsigned short width, height, wVram;
} TEXTURE_HEADER;
