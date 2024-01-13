

#define uint8_t  unsigned char
#define uint16_t unsigned short
#define uint32_t unsigned int
#define uint64_t unsigned long

#define int8_t  signed char
#define int16_t signed short
#define int32_t signed int
#define int64_t signed long

#define RW_REGISTER_FLOAT(REG) 	*((volatile float *)(REG))
#define RW_REGISTER_U8(REG) 	*((volatile uint8_t  *)(REG))
#define RW_REGISTER_U16(REG) 	*((volatile uint16_t *)(REG))
#define RW_REGISTER_U32(REG) 	*((volatile uint32_t *)(REG))
#define RW_REGISTER_U64(REG) 	*((volatile uint64_t *)(REG))

void elibc_printf(char *text);