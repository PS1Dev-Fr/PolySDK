

#include "elibc.h"
#include "PS1.h"
#include "PolySDK.h"

static uint32_t padbuf,new_pad = 0,end_pad = 0,old_pad = 0;
static uint32_t padbuf2,new_pad2 = 0,end_pad2 = 0,old_pad2 = 0;
static char pad_buf1[0x22],pad_buf2[0x22];

void PolySDKInitPad()
{
	BIOS_InitPad(pad_buf1,0x22,pad_buf2,0x22);
}

void *PolySDKGetPad1()
{
	return pad_buf1;
}
void *PolySDKGetPad2()
{
	return pad_buf2;
}

void PolySDKEvent()
{
	unsigned int *buf = PolySDKGetPad1();

	padbuf = (buf[0]>>16)^0xFFFF;
	new_pad = padbuf & ~old_pad;
	end_pad = (padbuf^old_pad)^new_pad;
	old_pad = padbuf;

	buf = PolySDKGetPad2();

	padbuf2 = (buf[0]>>16)^0xFFFF;
	new_pad2 = padbuf2 & ~old_pad2;
	end_pad2 = (padbuf2^old_pad2)^new_pad2;
	old_pad2 = padbuf2;

}

uint32_t PolySDKGetEventReleased(int32_t npad)
{
	if(npad == 0)
		return end_pad;

	return end_pad2;
}

uint32_t PolySDKGetEventPressed(int32_t npad)
{
	if(npad == 0)
		return new_pad;

	return new_pad2;
}

uint32_t PolySDKGetEventHold(int32_t npad)
{
	if(npad == 0)
		return padbuf;

	return padbuf2;
}

