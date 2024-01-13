
void elibc_printf(char *text)
{
	asm(

	"li $9, 0x3f\n	"

	"j 0xa0\n	"
	"nop\n	"

	);
}
