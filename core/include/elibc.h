

#define uint8_t  unsigned char
#define uint16_t unsigned short
#define uint32_t unsigned int
#define uint64_t unsigned long

#define int8_t  signed char
#define int16_t signed short
#define int32_t signed int
#define int64_t signed long

#define size_t unsigned int

#define RW_REGISTER_FLOAT(REG) 	*((volatile float *)(REG))
#define RW_REGISTER_U8(REG) 	*((volatile uint8_t  *)(REG))
#define RW_REGISTER_U16(REG) 	*((volatile uint16_t *)(REG))
#define RW_REGISTER_U32(REG) 	*((volatile uint32_t *)(REG))
#define RW_REGISTER_U64(REG) 	*((volatile uint64_t *)(REG))

int printf ( const char * format, ... );
int snprintf ( char * s, size_t n, const char * format, ... );
int sprintf ( char * str, const char * format, ... );

int atoi (const char * str);
int rand (void);
void srand (unsigned int seed);
void exit (int status);
int abs (int n);

void * memcpy ( void * destination, const void * source, size_t num );
char * strcpy ( char * destination, const char * source );
char * strncpy ( char * destination, const char * source, size_t num );

char * strcat ( char * destination, const char * source );
char * strncat ( char * destination, const char * source, size_t num );

int strcmp ( const char * str1, const char * str2 );
int strncmp ( const char * str1, const char * str2, size_t num );
int memcmp ( const void * ptr1, const void * ptr2, size_t num );

char * strchr ( char * str, int character );
char * strrchr ( char * str, int character );

void * memchr ( void * ptr, int value, size_t num );
void * memset ( void * ptr, int value, size_t num );
size_t strlen ( const char * str );
