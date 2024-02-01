

#include "elibc.h"
#include "PS1.h"
#include "PolySDK.h"

void PolySDKClearScreen()
{
	uint32_t list[10];

    PS1_GP0(1, 0); // Clear Cache
    
	list[0] = 3<<24;
	list[1] = GP0_CMD_COLOR(GP0_RECTANGLE_MO,128,128,128);
	list[2] = GP0_VERTEX(0,0);
	list[3] = GP0_VERTEX(320,240);
	list[4] = ((uint32_t)&list[0])&0x00ffffff;

    PS1_GP1(4, 2); // DMA CPU->GPU mode
	RW_REGISTER_U32(D2_MADR) = (uint32_t)list;
	RW_REGISTER_U32(D2_BCR) = 0;
	RW_REGISTER_U32(D2_CHCR) = DMA_CHCR_SET(1,0,0,2,0,0,1,0,0,0);

	while(!(RW_REGISTER_U32(GP1) & (1<<26)));
}

void PolySDKDrawSprite(uint32_t id,uint32_t px,uint32_t py,uint32_t rw,uint32_t rh)
{
	unsigned int linked_list[0x10];

	int tid = id&0x1F;
	int tx = tid<<6;
	int ty = 1;

	if(tid & 0x10)
	{
		tx -= 1024;
		ty = 0;
	}

	tid = (id>>8);
		
    uint32_t destX = (tid&0x10)<<5;
    uint32_t destY = 240+(tid&0xF);
    uint32_t psm = id>>16,color = 0xFFFFFF;

	px &= 0xFFFF;
	py &= 0xFFFF;

    linked_list[1] = GP0_TEXPAGE(tx,ty,0,psm,0,1,0,0,0);
    linked_list[2] = GP0_CMD_COLOR(GP0_RECTANGLE_TOB,color,0,0);
    linked_list[3] = GP0_VERTEX(px,py);
    linked_list[4] = GP0_TEXCOORD((0),(0),(destX+(destY<<6)));
    linked_list[5] = GP0_VERTEX(rw,rh);

    linked_list[0] = (6)<<24;
    linked_list[6] = 0x00ffffff;
    
    while(!(RW_REGISTER_U32(GP1) & (1<<0x1a))); /* Wait for the GPU to finish drawing primitives. */
    while(!(RW_REGISTER_U32(GP1) & (1<<0x1c))); /* Wait for the GPU to be free */
    PS1_GP1(4, 2); // DMA CPU->GPU mode
    RW_REGISTER_U32(D2_MADR) = (unsigned int)linked_list;
    RW_REGISTER_U32(D2_BCR) = 0;
    RW_REGISTER_U32(D2_CHCR) = DMA_CHCR_SET(1,0,0,2,0,0,1,0,0,0);
    while(!(RW_REGISTER_U32(GP1) & (1<<0x1a)));
	
}
