

#include "elibc.h"
#include "PS1.h"
#include "PolySDK.h"

static char PolySDK_Page[22];
static char PolySDK_PagePal[32];

void PolySDK_ManageVRAMInit()
{
	for(int i = 0;i < 22;i++)
		PolySDK_Page[i] = 0;

	for(int i = 0;i < 32;i++)
		PolySDK_PagePal[i] = 0;
}


int PolySDK_ManageVRAM(int pitch)
{
	if(pitch == 0)
		return -1;

	int bloc = pitch>>7;
	if(bloc == 0)
		bloc = 1;

	if(bloc == 1)
	{
		for(int i = 16;i < 22;i++)
		{
			if(PolySDK_Page[i] == 0)
			{
				PolySDK_Page[i] = 1;
				return i;
			}
		}

		for(int i = 0;i < 16;i++)
		{
			if(PolySDK_Page[i] == 0)
			{
				PolySDK_Page[i] = 1;
				return i;
			}
		}
	}

	if(bloc == 2)
	{
		for(int i = 0;i < 15;i++)
		{
			if( (PolySDK_Page[i] == 0) && (PolySDK_Page[i+1] == 0) )
			{
				PolySDK_Page[i] = 2;
				PolySDK_Page[i+1] = 2;
				return i;
			}
		}

		for(int i = 16;i < 21;i++)
		{
			if( (PolySDK_Page[i] == 0) && (PolySDK_Page[i+1] == 0) )
			{
				PolySDK_Page[i] = 2;
				PolySDK_Page[i+1] = 2;
				return i;
			}
		}
	}

	if(bloc == 4)
	{
		for(int i = 0;i < 13;i++)
		{
			if( (PolySDK_Page[i] == 0) && (PolySDK_Page[i+1] == 0) && (PolySDK_Page[i+2] == 0) && (PolySDK_Page[i+3] == 0) )
			{
				PolySDK_Page[i] = 4;
				PolySDK_Page[i+1] = 4;
				PolySDK_Page[i+2] = 4;
				PolySDK_Page[i+3] = 4;
				return i;
			}
		}

		for(int i = 16;i < 19;i++)
		{
			if( (PolySDK_Page[i] == 0) && (PolySDK_Page[i+1] == 0) && (PolySDK_Page[i+2] == 0) && (PolySDK_Page[i+3] == 0) )
			{
				PolySDK_Page[i] = 4;
				PolySDK_Page[i+1] = 4;
				PolySDK_Page[i+2] = 4;
				PolySDK_Page[i+3] = 4;
				return i;
			}
		}
	}


	return -1;
}

void PolySDKManageVRAMFree(int id)
{
	if( (id >= 0) && (id < 22) )
	{
		int n = PolySDK_Page[id];

		for(int i = 0;i < n;i++)
			PolySDK_Page[id+i] = 0;
	}
		
}

void PolySDKManageVRAMFreePal(int id)
{
	if( (id >= 0) && (id < 32) )
		PolySDK_PagePal[id] = 0;
}

int PolySDK_ManageVRAMPal(int pitch)
{
	if(pitch == 0)
		return -1;

	if(pitch > 128)
	{
		for(int i = 0;i < 16;i++)
		{
			if(PolySDK_PagePal[i] == 0)
			{
				PolySDK_PagePal[i] = 1;
				return i<<8;
			}
		}
	}else
	{
		for(int i = 16;i < 32;i++)
		{
			if(PolySDK_PagePal[i] == 0)
			{
				PolySDK_PagePal[i] = 1;
				return i<<8;
			}
		}
	}

	return -1;
}


int32_t PolySDK_LoadVRAM(void *adrtigfile)
{
	TEXTURE_HEADER tigfile;

	memcpy(&tigfile,adrtigfile,0x10);

	if(strcmp("TIG",tigfile.signature) != 0)
	{
		printf("Don't TIG File\n");
		return -1;
	}

	int id = PolySDK_ManageVRAM(tigfile.pitch);
	if(id == -1)
	{
		printf("Error VRAM Fill\n");
		return -1;
	}

	int y = 256;
	int x = id<<6;

	if(id > 15)
	{
		y = 0;
		x = ( (id-16)<< 6 ) + 640;
	}

	PS1_Upload_VRAM((char*)adrtigfile+0x10,tigfile.pitch>>1,tigfile.height,x,y);

	int pitch = 0;

	if(tigfile.mode == PS1_PSM4)
		pitch = 128;

	if(tigfile.mode == PS1_PSM8)
		pitch = 512;

	int pid;

	if(pitch != 0)
	{
		int n = tigfile.pitch*tigfile.height;
		pid = PolySDK_ManageVRAMPal(pitch);

		x = (pid>>13)<<9;
		y = (pid>>8)&0x1F;

		PS1_Upload_VRAM((char*)adrtigfile+0x10+n,pitch,1,x,240+y);
	}

	id |= tigfile.mode<<16;

	return id;
}
