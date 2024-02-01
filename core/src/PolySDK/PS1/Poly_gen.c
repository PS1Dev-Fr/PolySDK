

#include "elibc.h"
#include "PS1.h"
#include "PolySDK.h"


static PolySDK_Buffer buffer;

PolySDK_Buffer *PolySDKGetBuffer()
{
	return &buffer;
}

enum {
	DMA_CHCR_READ             = 0 <<  0,
	DMA_CHCR_WRITE            = 1 <<  0,
	DMA_CHCR_REVERSE          = 1 <<  1,
	DMA_CHCR_CHOPPING         = 1 <<  8,
	DMA_CHCR_MODE_BITMASK     = 3 <<  9,
	DMA_CHCR_MODE_BURST       = 0 <<  9,
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

void PolySDKInit(const char *name,uint32_t mode)
{
	uint32_t width = 320;
	uint32_t height = 240;
	PS1_Init(width,height);

	buffer.width  = width;
	buffer.height = height;
	buffer.fpsm = PS1_PSM16;
	buffer.faddress1 = 0;
	buffer.faddress2 = width;

	buffer.switchBuffer = 0;

	PolySDKInitOT();
}












