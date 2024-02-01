

void PolySDKInit(const char *name,uint32_t mode);
void PS1_Upload_VRAM(void *buffer,unsigned short w,unsigned short h,int destX,int destY);

int32_t PolySDK_LoadVRAM(void *adrtigfile);

void PolySDKClearScreen();



void PolySDKEvent();
uint32_t PolySDKGetEventReleased(int32_t npad);
uint32_t PolySDKGetEventPressed(int32_t npad);
uint32_t PolySDKGetEventHold(int32_t npad);

void PolySDKCDLoad(const char *path,void *buf,int size,int offset);
void *PolySDKGetPad1();
void *PolySDKGetPad2();
void PolySDKInitPad();

typedef struct
{
	uint32_t width,height;
	
	uint8_t switchBuffer,fpsm,faddress1,faddress2;

}PolySDK_Buffer;

void LMP3D_Draw_Sprite_Array(uint32_t tx,uint32_t ty,uint32_t px,uint32_t py,uint32_t rw,uint32_t rh);
void PolySDKDrawSprite(uint32_t id,uint32_t px,uint32_t py,uint32_t rw,uint32_t rh);

#define POLYSDK_PAD_SQUARE   0x8000
#define POLYSDK_PAD_CROSS    0x4000
#define POLYSDK_PAD_CIRCLE   0x2000
#define POLYSDK_PAD_TRIANGLE 0x1000

#define POLYSDK_PAD_L2 0x0800
#define POLYSDK_PAD_L1 0x0400
#define POLYSDK_PAD_R2 0x0200
#define POLYSDK_PAD_R1 0x0100

#define POLYSDK_PAD_LEFT  0x0080
#define POLYSDK_PAD_DOWN  0x0040
#define POLYSDK_PAD_RIGHT 0x0020
#define POLYSDK_PAD_UP    0x0010

#define POLYSDK_PAD_START  0x0008
#define POLYSDK_PAD_UNK1   0x0004
#define POLYSDK_PAD_UNK2   0x0002
#define POLYSDK_PAD_SELECT 0x0001

void waitForVSync(void);

void PS1_FlipBuffer();

typedef struct
{
    char signature[4];
    unsigned char mode, reserved;
    unsigned short width, height;

	unsigned short pitch, unk2, unk3;
} TEXTURE_HEADER;
