
#include "elibc.h"
#include "PS1.h"
#include "PolySDK.h"

void PS1_SetVideoMode(uint32_t width, uint32_t height, uint32_t video_mode, uint32_t rgb24,uint32_t inter, uint32_t reverse)
{
	uint32_t mode = 0;
		
	PS1_GP1(6, 0xC60260); // Horizontal screen range
	PS1_GP1(7, 0x040010); // Vertical screen range
	//0x260 + 320*8
		
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
}



void PS1_Init(uint32_t width,uint32_t height)
{
	//GPU
	PS1_GP1(0, 0); //Reset GPU
	PS1_GP1(1, 0); //Clear FIFO
	PS1_GP1(2, 0); //ack irq (0)
	PS1_GP1(3, 0); //Display Enable on
	PS1_GP1(4, 0); //DMA OFF
	PS1_GP1(5, 0); //Display offset
	PS1_GP1(9, 0); //Texture disable
	
	RW_REGISTER_U32(DPCR) |= (1<<11); // Enable dma channel 2
	RW_REGISTER_U32(DPCR) |= (1<<27); // Enable dma channel 6
	
	PS1_SetVideoMode(width, height, VMODE_NTSC, 0, 1, 0);

	PS1_GP0(0xe1, 0); // Draw Mode
	PS1_GP0(0xe2, 0); // Texture Window setting
	PS1_GP0(0xe3, 0); // Set Drawing Area top left
	PS1_GP0(0xe4, ((height-1)<<10)|(width-1)); //Set Drawing Area bottom right (X2,Y2)
	PS1_GP0(0xe5, 0); // Set Drawing Offset
	PS1_GP0(0xe6, 0); // Mask Bit Setting
}


void waitForVSync(void) {
	// The GPU won't tell us directly whenever it is done sending a frame to the
	// display, but it will send a signal to another peripheral known as the
	// interrupt controller (which will be covered in a future tutorial). We can
	// thus wait until the interrupt controller's vertical blank flag gets set,
	// then reset (acknowledge) it so that it can be set again by the GPU.

	RW_REGISTER_U32(I_STAT) = ~(1 );
	while (!(RW_REGISTER_U32(I_STAT) & (1 )))
		__asm__ volatile("nop\n");

	RW_REGISTER_U32(I_STAT) = ~(1 );
}

void PS1_FlipBuffer23(int switchBuffer)
{
	uint32_t width = 320;
	uint32_t height = 240;

	if(switchBuffer == 0)
	{
		PS1_GP1(5, 0);
		PS1_GP0(0xe3, 0); // Set Drawing Area top left
		PS1_GP0(0xe4, ((height-1)<<10)|(0+width-1)); //Set Drawing Area bottom right (X2,Y2)
		PS1_GP0(0xe5, 0); // Set Drawing Offset

	}

	if(switchBuffer == 1)
	{
		PS1_GP1(5, width);
		PS1_GP0(0xe3, width); // Set Drawing Area top left
		PS1_GP0(0xe4, ((height-1)<<10)|(width+width-1)); //Set Drawing Area bottom right (X2,Y2)
		PS1_GP0(0xe5, width); // Set Drawing Offset

	}

	if(switchBuffer == 2)
	{
		PS1_GP1(5, 0);
		PS1_GP0(0xe3, width); // Set Drawing Area top left
		PS1_GP0(0xe4, ((height-1)<<10)|(width+width-1)); //Set Drawing Area bottom right (X2,Y2)
		PS1_GP0(0xe5, width); // Set Drawing Offset

	}

	
	if(switchBuffer == 3)
	{
		PS1_GP1(5, width);
		PS1_GP0(0xe3, 0); // Set Drawing Area top left
		PS1_GP0(0xe4, ((height-1)<<10)|(0+width-1)); //Set Drawing Area bottom right (X2,Y2)
		PS1_GP0(0xe5, 0); // Set Drawing Offset
	}

}

void PS1_FlipBuffer()
{
	uint32_t width = 320;
	uint32_t height = 240;

	static int switchBuffer = 0;
	if(switchBuffer != 0)
	{
		PS1_GP1(5, width);
		PS1_GP0(0xe3, width); // Set Drawing Area top left
		PS1_GP0(0xe4, ((height-1)<<10)|(width+width-1)); //Set Drawing Area bottom right (X2,Y2)
		PS1_GP0(0xe5, width); // Set Drawing Offset

	}else
	{
		PS1_GP1(5, 0);
		PS1_GP0(0xe3, 0); // Set Drawing Area top left
		PS1_GP0(0xe4, ((height-1)<<10)|(0+width-1)); //Set Drawing Area bottom right (X2,Y2)
		PS1_GP0(0xe5, 0); // Set Drawing Offset
	}
	switchBuffer = !switchBuffer;

}

void PS1_FlipBuffer2()
{
	uint32_t width = 320;
	uint32_t height = 240;

	static int switchBuffer = 0;
	if(switchBuffer == 0)
	{
		PS1_GP1(5, 0);
		PS1_GP0(0xe3, width); // Set Drawing Area top left
		PS1_GP0(0xe4, ((height-1)<<10)|(width+width-1)); //Set Drawing Area bottom right (X2,Y2)
		PS1_GP0(0xe5, width); // Set Drawing Offset

	}else
	{
		PS1_GP1(5, width);
		PS1_GP0(0xe3, 0); // Set Drawing Area top left
		PS1_GP0(0xe4, ((height-1)<<10)|(0+width-1)); //Set Drawing Area bottom right (X2,Y2)
		PS1_GP0(0xe5, 0); // Set Drawing Offset
	}
	switchBuffer = !switchBuffer;
}



void gpuSendSync0(unsigned int v)
{
  while(!(RW_REGISTER_U32(GPUSTAT) & GPUSTAT_CMD_READY)); /* is this correct? */
  RW_REGISTER_U32(GP0) = v;
}

void PS1_Upload_VRAM(void *buffer,unsigned short w,unsigned short h,int destX,int destY)
{
	unsigned int hwords_to_transfer = w*h;
	unsigned int words_to_transfer = hwords_to_transfer >> 1;
	unsigned int blocks_to_transfer = words_to_transfer >> 4; /* full blocks */

	if(blocks_to_transfer > 0xFFFF)
	{
		printf("ERR: too many blocks to transfer: %#x\n", blocks_to_transfer);
		return;
	}

	PS1_GP1(4, 2);

	gpuSendSync0(GP0_COPY_CPU_TO_VRAM<< 24);
	RW_REGISTER_U32(GP0) = (destX | (destY << 16));
	RW_REGISTER_U32(GP0) = (w | (h << 16));

	RW_REGISTER_U32(DICR) &= ~(1 << (16+2)); /* disable dma interrupts for DMA2 */
	RW_REGISTER_U32(DPCR) |= 0x800; /* enable DMA2 */

	if(blocks_to_transfer)
	{
		RW_REGISTER_U32(D2_MADR) = (unsigned int)buffer;
		RW_REGISTER_U32(D2_BCR)  = 0x10 | (blocks_to_transfer << 16);
		RW_REGISTER_U32(D2_CHCR) = D_CHCR_FROM_RAM | D_CHCR_FORWARD | D_CHCR_SYNC_DEV | D_CHCR_START;
		while( RW_REGISTER_U32(D2_CHCR) & D_CHCR_BUSY);
	}

	/* transfer remaining words in one block */
	words_to_transfer &= 0xF;
	if(words_to_transfer)
	{
		RW_REGISTER_U32(D2_MADR) = (unsigned int)buffer + (blocks_to_transfer * 0x10)*4;
		RW_REGISTER_U32(D2_BCR)  = words_to_transfer | (1 << 16);
		RW_REGISTER_U32(D2_CHCR) = D_CHCR_FROM_RAM | D_CHCR_FORWARD | D_CHCR_SYNC_DEV | D_CHCR_START;
		while( RW_REGISTER_U32(D2_CHCR) & D_CHCR_BUSY); /* wait while transfer in progress */
	}


}

