
#include "elibc.h"
#include "PolySDK.h"

/*
Contraintes

Les textures doivent avoir une taille précises :
- en 4bpp les textures doivent faire 256x256
- en 8bpp les textures doivent faire 128x256 ou 256x256
- en RGB1555 les textures doivent faire 64x256 ou 128x256 ou 256x256

Les musiques et SFX sont tous sur 16000Hz

sprintf ne prend qu 2 arguments max
snprintf qu'un seul

Pour la lecture CD , il faut obligatoirement lire par un offset de 2048 (0x800)

La résolution ne peut etre que de 320x240, 384x240 et 512x240 
*/

uint8_t cdbuffer[0x20800];
int main()
{
	PolySDKInit("game",0);

	printf("hello world2\n");

	PolySDKCDLoad("cdrom:TEST.TXT",cdbuffer,0x800,0x800);
	cdbuffer[128] = 0;
	printf("%s\n",cdbuffer);

	int x = 0;
	int y = 0;

	PolySDKCDLoad("cdrom:TEST2.TIG",cdbuffer,0x18000,0);

	int id = PolySDK_LoadVRAM(cdbuffer);

	char str[32];
	sprintf(str,"test %x %c\n",-5,'s');
	printf(str);

	int switchBuffer = 0;
	while(1)
	{
		PolySDKEvent();
        uint32_t pad = PolySDKGetEventHold(0);

		uint32_t pad2 = PolySDKGetEventPressed(0);

		if(pad & POLYSDK_PAD_LEFT)
			x -= 2;

		if(pad & POLYSDK_PAD_RIGHT)
			x += 2;

		if(pad & POLYSDK_PAD_UP)
			y -= 2;

		if(pad & POLYSDK_PAD_DOWN)
			y += 2;

		if(pad2 & POLYSDK_PAD_CROSS)
		{
			switchBuffer++;
			printf("s : %d\n",switchBuffer);
		}
			
		PolySDKClearScreen();
		PolySDKDrawSprite(id,x,y,256,256);


		waitForVSync();
		PS1_FlipBuffer();
	}

	return 0;
}
