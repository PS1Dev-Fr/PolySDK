
#include "elibc.h"
#include "PS1.h"
#include "PolySDK.h"

void PolySDKCDLoad(const char *path,void *buf,int size,int offset) // bloc = 0x800
{
	int fd = BIOS_FileOpen(path,1); //READ ONLY

	BIOS_FileSeek(fd,offset,0);

	BIOS_FileRead(fd,buf,size);

	BIOS_FileClose(fd);
}

//MEMCARD
