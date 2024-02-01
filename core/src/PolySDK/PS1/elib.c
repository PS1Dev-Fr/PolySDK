
#include "elibc.h"

static int intToAscii(int number, char *result)
{
    if (number == 0) {
        result[0] = '0';
        result[1] = '\0';
        return 1;
    }

    int isNegative = 0;
    if (number < 0) {
        isNegative = 1;
        number = -number;
    }

    int index = 0;
    while (number > 0) {
        int digit = number % 10;
        result[index++] = digit + '0';
        number /= 10;
    }

    if (isNegative) {
        result[index++] = '-';
    }

    result[index] = '\0';
    int length = index;
    for (int i = 0; i < length / 2; i++) {
        char temp = result[i];
        result[i] = result[length - i - 1];
        result[length - i - 1] = temp;
    }

	return length;
}

static int intToAsciiu(unsigned int number, char *result)
{
    if (number == 0) {
        result[0] = '0';
        result[1] = '\0';
        return 1;
    }

    int index = 0;
    while (number > 0) {
        unsigned int digit = number % 10;
        result[index++] = digit + '0';
        number /= 10;
    }

    result[index] = '\0';
    int length = index;
    for (int i = 0; i < length / 2; i++) {
        char temp = result[i];
        result[i] = result[length - i - 1];
        result[length - i - 1] = temp;
    }

	return length;
}

static void hexToAscii(int number, char *result,char hex)
{
	int shift = 28;

	result[0] = '0';
	result[1] = 'x';
	for(int i = 0;i < 8;i++)
	{
		 int digit = (number>>shift)&0xF;

		 if(digit < 10)
		 	result[i+2] = '0' + digit;
		else
		 	result[i+2] = hex + digit - 10;

		shift -= 4;
	}

	result[11] = 0;
}



static int _n_snprintf = 0;
static int _i_snprintf = 0;
int snprintf( char * s, unsigned int n, const char * format,...)
{
	_n_snprintf = n;
	_i_snprintf = 1;
	sprintf(s,format);

	return 0;
}

int sprintf( char * str, const char * format,...)
{
	int arg1,arg2;
	asm (
        "move %0,$a2"
        : "=r" (arg1)
    );
	asm (
        "move %0,$a3"
        : "=r" (arg2)
    );

	int arg[2];
	arg[0] = arg1;
	arg[1] = arg2;

	char result[16];

	int i = 0,l = 0;
	char ch1 = format[0],ch2;
	int id = _i_snprintf;

	while(ch1 != 0)
	{
		ch1 = format[i+0];
		ch2 = format[i+1];

		if(ch1 == '%')
		{
			str[l] = 0;
			
			if( (ch2 == 'd') || (ch2 == 'i') )
			{
				l += intToAscii(arg[id],result);
				strcat(str,result);
				
				i++;
				id++;
			}

			if(ch2 == 'u')
			{
				l += intToAsciiu(arg[id],result);
				strcat(str,result);
				
				i++;
				id++;
			}

			if(ch2 == 'x')
			{
				hexToAscii(arg[id],result,'a');
				strcat(str,result);
				l += 10;
				i++;
				id++;
			}

			if(ch2 == 'X')
			{
				hexToAscii(arg[id],result,'A');
				strcat(str,result);
				l += 10;
				i++;
				id++;
			}

			if(ch2 == 'c')
			{
				str[l] = arg[id];
				l++;
				
				i++;
				id++;
			}

			if(ch2 == 's')
			{
				char *adrstr =(char*)arg[id];
				strcat(str,adrstr);
				l += strlen(adrstr);
				i++;
			}

			i++;
		}
		else
		{
			if( (ch1 == '\\') && (ch2 == 'n') )
			{
				str[l] = 0xA;
				i += 2;
			}
			else
			{
				str[l] = ch1;
				i++;
			}
			l++;
		}

		
	}

	_n_snprintf = 0;
	_i_snprintf = 0;

	return l;
}
