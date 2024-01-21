#include <stdio.h>
#include <string.h>

#include "upng.h"
#include "../../core/include/texture.h"

unsigned short getCol(unsigned char r, unsigned char g, unsigned b)
{
	r = (r & 0xf8) >> 3;
	g = (g & 0xf8) >> 3;
	b = (b & 0xf8) >> 3;
	unsigned short val = (r << 10) | (g << 5) | b;
}

int main(int argc, char **argv)
{
	if (argc <= 2)
	{
		return 0;
	}

	upng_t *upng = upng_new_from_file(argv[1]);
	if (upng_get_error(upng) != UPNG_EOK)
	{
		printf("error: %u %u\n", upng_get_error(upng), upng_get_error_line(upng));
		return 0;
	}

	upng_decode(upng);
	if (upng_get_error(upng) != UPNG_EOK)
	{
		printf("error: %u %u\n", upng_get_error(upng), upng_get_error_line(upng));
		return 0;
	}

	//printf("size:	%ux%ux%u (%u)\n", upng_get_width(upng), upng_get_height(upng), upng_get_bpp(upng), upng_get_size(upng));
	//printf("format:	%u\n", upng_get_format(upng));

	TEXTURE_HEADER th;
	strcpy(th.signature, TEXTURE_SIGNATURE);

	th.width = upng_get_width(upng);
	th.height = upng_get_height(upng);
	th.wVram = th.width;

	switch (upng_get_format(upng))
	{
	case UPNG_RGB8:
	case UPNG_RGBA8:
		th.mode = TEXTURE_RGB5;
		break;
	default:
		th.mode = -1;
		break;
	}

	if (th.mode == TEXTURE_RGB5)
	{
		FILE *fo = fopen(argv[2], "wb");
		fwrite(&th, sizeof(TEXTURE_HEADER), 1, fo);

		unsigned int w = upng_get_width(upng);
		unsigned int h = upng_get_height(upng);
		const unsigned char *buf = upng_get_buffer(upng);
		for (unsigned int y = 0; y < h; y++)
		{
			for (unsigned int x = 0; x < w; x++)
			{
				unsigned short val = getCol(*buf++, *buf++, *buf++);
				fwrite(&val, 2, 1, fo);
			}
		}
		fclose(fo);
	}

	upng_free(upng);
	return 0;
}
