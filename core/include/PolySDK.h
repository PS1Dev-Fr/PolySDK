

void PolySDKInit(const char *name,uint32_t width,uint32_t height);
void PS1_Upload_VRAM(unsigned int *buffer,unsigned short w,unsigned short h,int destX,int destY);

void PolySDKClearScreen();

typedef struct
{
	uint32_t width,height;
	
	uint8_t switchBuffer,fpsm,faddress1,faddress2;

}PolySDK_Buffer;