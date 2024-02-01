/*

  A(17h) strcmp(str1,str2)
  A(18h) strncmp(str1,str2,maxlen)
  A(19h) strcpy(dst,src)
  A(1Ah) strncpy(dst,src,maxlen)
  A(1Bh) strlen(src)

  A(1Eh) strchr(src,char)  ;exactly the same as "index"
  A(1Fh) strrchr(src,char) ;exactly the same as "rindex"


*/

void abs()
{
	asm(
	"li $9, 0x0e\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}

void atoi()
{
	asm(
	"li $9, 0x10\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}

void strcat()
{
	asm(
	"li $9, 0x15\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}

void strncat()
{
	asm(
	"li $9, 0x16\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}

void strcmp()
{
	asm(
	"li $9, 0x17\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}

void strncmp()
{
	asm(
	"li $9, 0x18\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}

void strcpy()
{
	asm(
	"li $9, 0x19\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}

void strncpy()
{
	asm(
	"li $9, 0x1A\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}


void strlen()
{
	asm(
	"li $9, 0x1B\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}


void memcpy()
{
	asm(
	"li $9, 0x2a\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}

void memset()
{
	asm(
	"li $9, 0x2b\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}

void memchr()
{
	asm(
	"li $9, 0x2e\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}

void rand()
{
	asm(
	"li $9, 0x2f\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}

void srand()
{
	asm(
	"li $9, 0x30\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}


void printf()
{
	asm(
	"li $9, 0x3f\n	"
	"j 0xa0\n	"
	"nop\n	"
	);
}

//----------------------------------

void BIOS_FileOpen()
{
	asm(
	"li $9, 0x00\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}

void BIOS_FileSeek()
{
	asm(
	"li $9, 0x01\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}

void BIOS_FileRead()
{
	asm(
	"li $9, 0x02\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}


void BIOS_FileWrite()
{
	asm(
	"li $9, 0x03\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}

void BIOS_FileClose()
{
	asm(
	"li $9, 0x04\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}

void BIOS_Exit()
{
	asm(
	"li $9, 0x06\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}

void BIOS_FlushCache()
{
	asm(
	"li $9, 0x44\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}

void BIOS_CdInit()
{
	asm(
	"li $9, 0x71\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}

void BIOS_CdRemove()
{
	asm(
	"li $9, 0x72\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}

//B Function

void BIOS_OpenEvent(int class,int spec,int mode, void (*func)() )
{
	asm(
	"li $9, 0x08\n	"
	"j 0xb0\n	" 
	"nop\n	"
	);
}

void BIOS_EnableEvent(int event)
{
	asm(
	"li $9, 0x0C\n	"
	"j 0xb0\n	" 
	"nop\n	"
	);
}

void BIOS_InitPad()
{
	asm(
	"li $9, 0x12\n	"
	"j 0xb0\n	" 
	"nop\n	"
	);
}

void BIOS_StartPad()
{
	asm(
	"li $9, 0x13\n	"
	"j 0xb0\n	" 
	"nop\n	"
	);
}

void BIOS_StopPad()
{
	asm(
	"li $9, 0x14\n	"
	"j 0xb0\n	" 
	"nop\n	"
	);
}



void BIOS_gpu_send_dma(int Xdst,int Ydst,int Xsiz,int Ysiz,void *src)
{
	asm(
	"li $9, 0x47\n	"
	"j 0xa0\n	" 
	"nop\n	"
	);
}

