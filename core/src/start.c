

void __start()
{
	asm(
	"li $sp, 0x801FFFF0\n	" //init sp
	"li $k1, 0x1f800000\n	" //init kernel 1 hardware

	"jal main\n	"
	"nop\n	"

	"inf_loop: j inf_loop\n	"
	"nop\n	"

	);
}
