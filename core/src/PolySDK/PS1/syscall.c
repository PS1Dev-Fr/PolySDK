
void SYSCALL_EnterCriticalSection()
{
	asm(
	"li $a0, 1\n	"
	"syscall\n	" 
	"nop\n	"
	);
}

void SYSCALL_ExitCriticalSection()
{
	asm(
	"li $a0, 2\n	"
	"syscall\n	" 
	"nop\n	"
	);
}

void SYSCALL_ChangeThreadSubFunction(int addr)
{
	asm(
    "add $a0, $a1, $zero\n	"
	"li $a0, 3\n	"
	"syscall\n	" 
	"nop\n	"
	);
}
