
#include "elibc.h"
#include "PolySDK.h"

int test(void);
void elibc_printf(char *text);

char tab[64];
const unsigned char psexe_magic[8] = {'P','S','-','X',' ','E','X','E'};
char *hello = "hello";

uint8_t cdb1[0x10000];
uint8_t cdb2[0x20000];

int main()
{
	PolySDKInit("game",320,240);

	PolySDKClearScreen();

	elibc_printf("hello world");

	return 0;
}
