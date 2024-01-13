

#include "elibc.h"
#include "PS1.h"
#include "PolySDK.h"


static PolySDK_Buffer buffer;

PolySDK_Buffer *PolySDKGetBuffer()
{
	return &buffer;
}

void PolySDKInit(const char *name,uint32_t width,uint32_t height)
{
	PS1_Init(width,height);

	buffer.width  = width;
	buffer.height = height;
	buffer.fpsm = PS1_PSM16;
	buffer.faddress1 = 0;
	buffer.faddress2 = width;

	buffer.switchBuffer = 0;
}


void PolySDKClearScreen()
{
	uint32_t list[10];

	list[0] = 3<<24;
	list[1] = GP0_CMD_COLOR(GP0_RECTANGLE_MO,128,128,128);
	list[2] = GP0_VERTEX(0,0);
	list[3] = GP0_VERTEX(320,240);
	list[4] = ((uint32_t)&list[0])&0x00ffffff;

    PS1_GP1(4,2); // dma: on, cpu to gpu
	RW_REGISTER_U32(D2_MADR) = (uint32_t)list;
	RW_REGISTER_U32(D2_BCR) = 0;
	RW_REGISTER_U32(D2_CHCR) = DMA_CHCR_SET(1,0,0,2,0,0,1,0,0,0);

	while(!(RW_REGISTER_U32(GP1) & (1<<26)));
}



void gpuSendSync0(unsigned int v)
{
  while(!(RW_REGISTER_U32(GPUSTAT) & GPUSTAT_CMD_READY)); /* is this correct? */
  RW_REGISTER_U32(GP0) = v;
}

void PS1_Upload_VRAM(unsigned int *buffer,unsigned short w,unsigned short h,int destX,int destY)
{
	unsigned int hwords_to_transfer = w*h;
	unsigned int words_to_transfer = hwords_to_transfer >> 1;
	unsigned int blocks_to_transfer = words_to_transfer >> 4; /* full blocks */

	if(blocks_to_transfer > 0xFFFF)
	{
		elibc_printf("ERR: too many blocks to transfer: \n");
		return;
	}

	RW_REGISTER_U32(GP1) = (0x04<<24)| 2; /* dma: on, cpu to gp0 */

	gpuSendSync0(GP0_COPY_CPU_TO_VRAM<< 24);
	RW_REGISTER_U32(GP0) = (destX | (destY << 16));
	RW_REGISTER_U32(GP0) = (w | (h << 16));

	RW_REGISTER_U32(DICR) &= ~(1 << (16+2)); /* disable dma interrupts for DMA2 */
	RW_REGISTER_U32(DPCR) |= 0x800; /* enable DMA2 */

	//printf("VRAM : %d   %d,%d\n",blocks_to_transfer,destX,destY);
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

	/* transfer remaining half word if necessary */
	hwords_to_transfer &= 1;
	if(hwords_to_transfer)
	{
		while(!(RW_REGISTER_U32(GPUSTAT) & GPUSTAT_DMA_READY));
		RW_REGISTER_U32(GP0) = ((unsigned int)*(unsigned short*)(buffer + (blocks_to_transfer * 0x10)*4 + words_to_transfer));
	}
}


void LMP3D_Draw_Sprite_Array(utint32_t tx,utint32_t ty,utint32_t px,utint32_t py,utint32_t rx,utint32_t ry)
{
	unsigned int linked_list[0x10];
	int flag =0;

    int flagw = 0,flagh = 0;
    //if(flag & LMP3D_FLIPH) flagw = rect.w-1;
    //if(flag & LMP3D_FLIPV) flagh = rect.h-1;

    utint32_t destX = 0;
    utint32_t destY = 0;
    uint32_t psm = 0;

    linked_list[i++] = GP0_TEXPAGE(tx,ty,0,psm,0,1,0,flag,0);
    linked_list[i++] = GP0_CMD_COLOR(GP0_RECTANGLE_TOB,sprite[l].color,0,0);
    linked_list[i++] = GP0_VERTEX(px&0xFFFF,py);
    linked_list[i++] = GP0_TEXCOORD((rect.x+flagw),(rect.y+flagh),(destX+(destY<<6)));
    linked_list[i++] = GP0_VERTEX(rw,rh);

    linked_list[0] = (i-1)<<24;
    linked_list[i] = 0x00ffffff;

    PS1_GP1(4, 2); // DMA CPU->GPU mode
    while(!(RW_REGISTER_U32(GP1) & (1<<0x1a))); /* Wait for the GPU to finish drawing primitives. */
    while(!(RW_REGISTER_U32(GP1) & (1<<0x1c))); /* Wait for the GPU to be free */

    RW_REGISTER_U32(D2_MADR) = (unsigned int)linked_list;
    RW_REGISTER_U32(D2_BCR) = 0;
    RW_REGISTER_U32(D2_CHCR) = DMA_CHCR_SET(1,0,0,2,0,0,1,0,0,0);
    while(!(RW_REGISTER_U32(GP1) & (1<<0x1a)));
	
}