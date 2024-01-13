
#include "elibc.h"
#include "PS1.h"
#include "PolySDK.h"

void PS1_SetVideoMode(uint32_t width, uint32_t height, uint32_t video_mode, uint32_t rgb24,uint32_t inter, uint32_t reverse)
{
	uint32_t mode = 0;
	
	PS1_GP1(3, 1);
	
	if(video_mode == VMODE_NTSC)
	{
		PS1_GP1(6, 0xC4E24E); // Horizontal screen range
		PS1_GP1(7, 0x040010); // Vertical screen range
	}
	else
	{
		PS1_GP1(6, 0xC62262); // Horizontal screen range
		PS1_GP1(7, 0x04B42D); // Vertical screen range
	}
		
	switch(height)
	{
		case 240:
		break;
		case 480:
			mode|=4;
		break;

	}
	
	switch(width)
	{
		case 256:
		break;
		case 320:
			mode|=1;
		break;
		case 512:
			mode|=2;
		break;
		case 640:
			mode|=3;
		break;
		case 384:
			mode|= 0x40;
		break;

	}
	
	if(video_mode)mode|= 0x08; // Set PAL
	if(rgb24)mode|= 0x10; // Set unaccellerated 24-bit mode
	if(inter)mode|= 0x20; // Set interlaced video mode
	if(reverse)mode|= 0x80; // Set reverse flag (?)
	
	PS1_GP1(8, mode);
	PS1_GP1(3, 0);
}

void PS1_SetDrawEnv(uint32_t w ,uint32_t h)
{
	PS1_GP1(5, 0); // Display offset

	PS1_GP0(0xe1, (1<<10)|(0<<9));
	PS1_GP0(0xe2, 0);
	PS1_GP0(0xe3, 0);

	PS1_GP0(0xe4, ((h-1)<<10)|(w-1));

	//#warning "Check drawing offset better."
	PS1_GP0(0xe5, 0);

	PS1_GP0(0xe6, 0);
}


void PS1_Init(uint32_t width,uint32_t height)
{
	PS1_GP1(1, 0);
	PS1_GP1(0, 0); // Reset GPU
	
	RW_REGISTER_U32(DPCR) |= (1<<0xb); // Enable dma channel 2
	PS1_GP1(4, 2); // DMA CPU->GPU mode
	
	PS1_GP1(3, 1); // Disable display
	
	PS1_GP0(1, 0); // Reset data port

	PS1_SetVideoMode(width, height, VMODE_NTSC, 0, 1, 0);

	PS1_SetDrawEnv(width ,height);

}