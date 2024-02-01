


#include "elibc.h"
#include "PS1.h"
#include "PolySDK.h"




enum {
	DMA_CHCR_WRITE            = 1 <<  0,
	DMA_CHCR_REVERSE          = 1 <<  1,
	DMA_CHCR_CHOPPING         = 1 <<  8,
	DMA_CHCR_MODE_BITMASK     = 3 <<  9,
	DMA_CHCR_MODE_SLICE       = 1 <<  9,
	DMA_CHCR_MODE_LIST        = 2 <<  9,
	DMA_CHCR_DMA_TIME_BITMASK = 7 << 16,
	DMA_CHCR_CPU_TIME_BITMASK = 7 << 20,
	DMA_CHCR_ENABLE           = 1 << 24,
	DMA_CHCR_TRIGGER          = 1 << 28,
	DMA_CHCR_PAUSE            = 1 << 29  // Burst mode only
};

enum {
	DMA_DPCR_PRIORITY_BITMASK = 7 << 0,
	DMA_DPCR_PRIORITY_MIN     = 7 << 0,
	DMA_DPCR_PRIORITY_MAX     = 0 << 0,
	DMA_DPCR_ENABLE           = 1 << 3
};


static uint32_t test_list[32];

void PolySDKInitOT()
{

	RW_REGISTER_U32(D6_MADR) = (uint32_t)&test_list[3];
	RW_REGISTER_U32(D6_BCR) = 3;
	RW_REGISTER_U32(D6_CHCR) = 0x11000002;
	//RW_REGISTER_U32(D2_CHCR) = DMA_CHCR_SET(0,1,0,0,0,0,0,0,0,0);

	while (RW_REGISTER_U32(D6_CHCR) & DMA_CHCR_ENABLE);

	printf("%x %x %x %x\n",&test_list[0],test_list[1],test_list[2],test_list[3]);
}

static uint32_t bufferlist1[4096];
static uint32_t bufferlist2[4096];
void PolySDKSend()
{
	RW_REGISTER_U32(D6_MADR) = (uint32_t) bufferlist1;
	RW_REGISTER_U32(D6_CHCR) = DMA_CHCR_WRITE | DMA_CHCR_MODE_LIST | DMA_CHCR_ENABLE;
}


void PolySDKadd()
{
	
}
