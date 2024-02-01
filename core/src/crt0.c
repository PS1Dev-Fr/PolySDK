

void __start() //begin 
{
	asm(
	"li $sp, 0x801FFFF8\n	" //init sp
	//"la $t0, _gp\n	"
	//"lui $gp, 0x8001\n	"
	//"or $gp, $gp,$t0\n	"
	"li $gp, _gp\n	"

	"jal _start\n	"
	"nop\n	"

	"__loop: j __loop\n	"
	"nop\n	"
	);
}

int main(void);
void PolySDKInitPad(void);

#include "elibc.h"
#include "PS1.h"
#define BSS_SIZE  (0x100000-0x28000-0x8000)
#define BSS_START (void*)0x80028000

void _start()
{
	memset(BSS_START, 0, BSS_SIZE);

	SYSCALL_EnterCriticalSection();
	BIOS_CdRemove();
	SYSCALL_ExitCriticalSection();

	//PS1_GTE_Init();

	BIOS_CdInit();

	PolySDKInitPad();
	BIOS_StartPad();

	main();
}


