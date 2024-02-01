

#include "PS1_GTE.h"

void PS1_GTE_Init()
{
	asm  (
	SET_GTE

	// init
	"mtc0 $t0, C0_STATUS\n	"

	"li	$t1,0x40000000\n	"
	"or	$t0,$t0,$t1\n	"

	"mtc0 $t0,C0_STATUS\n	"

	"li	$t0,0\n	"

	"mtc2 $t0,VXY0\n	"
	"mtc2 $t0,VXY1\n	"
	"mtc2 $t0,VXY2\n	"
	"mtc2 $t0,VZ0\n	"
	"mtc2 $t0,VZ1\n	"
	"mtc2 $t0,VZ2\n	"

	"mtc2 $t0,IR0\n	"
	"mtc2 $t0,IR1\n	"
	"mtc2 $t0,IR2\n	"
	"mtc2 $t0,IR3\n	"

	".word CTC2+((8+0)<<16)+TRX\n	"
	".word CTC2+((8+0)<<16)+TRY\n	"
	".word CTC2+((8+0)<<16)+TRZ\n	"

	".word CTC2+((8+0)<<16)+RBK\n	"
	".word CTC2+((8+0)<<16)+GBK\n	"
	".word CTC2+((8+0)<<16)+BBK\n	"

	"li	$t0,1<<12\n	"
	".word CTC2+((8+0)<<16)+ZSF3\n	"
	".word CTC2+((8+0)<<16)+ZSF4\n	"

	 );
}

