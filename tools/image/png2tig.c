#include <stdio.h>
#include <string.h>

#include "upng.h"
#include "../tig2image/texture.h"

unsigned short getCol(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	r = (r & 0xf8) >> 3;
	g = (g & 0xf8) >> 3;
	b = (b & 0xf8) >> 3;
	a = (a & 0x80);
	unsigned short val = (a << 8) | (r << 10) | (g << 5) | b;
		return val;
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

	// printf("size:	%ux%ux%u (%u)\n", upng_get_width(upng), upng_get_height(upng), upng_get_bpp(upng), upng_get_size(upng));
	// printf("format:	%u\n", upng_get_format(upng));

	TEXTURE_HEADER th;
	strcpy(th.signature, TEXTURE_SIGNATURE);

	th.width = upng_get_width(upng);
	th.height = upng_get_height(upng);
	th.reserved = 0;
	th.unk2 = 0;
	th.unk3 = 0;

	switch (upng_get_format(upng))
	{
	case UPNG_RGB8:
	case UPNG_RGBA8:
		th.mode = TEXTURE_RGB1555;
		th.pitch = th.width << 1;
		break;
	case UPNG_PALETTE8:
	case UPNG_PALETTEA8:
		th.mode = TEXTURE_PAL8;
		th.pitch = th.width;
		break;
	case UPNG_PALETTE4:
	case UPNG_PALETTEA4:
		th.mode = TEXTURE_PAL4;
		th.pitch = th.width >> 1;
		break;
	default:
		th.mode = -1;
		break;
	}

	if (th.mode != -1)
	{
		FILE *fo = fopen(argv[2], "wb");
		fwrite(&th, sizeof(TEXTURE_HEADER), 1, fo);

		unsigned int w = upng_get_width(upng);
		unsigned int h = upng_get_height(upng);
		const unsigned char *buf = upng_get_buffer(upng);
		unsigned char r, g, b, alpha = 0;
		switch (th.mode)
		{
		case TEXTURE_RGB1555:
			for (unsigned int y = 0; y < h; y++)
			{
				for (unsigned int x = 0; x < w; x++)
				{
					r = *buf++;
					g = *buf++;
					b = *buf++;
					if (upng_get_format(upng) == UPNG_RGBA8)
					{
						alpha = 255 - *buf++;
					}
					unsigned short val = getCol(r, g, b, alpha);
					fwrite(&val, 2, 1, fo);
				}
			}
			break;
		case TEXTURE_PAL8:
			for (unsigned int y = 0; y < h; y++)
			{
				fwrite(buf, 1, w, fo);
				buf += w;
			}
			{
				const unsigned char *pal = upng_get_palette(upng);
				unsigned short nbc = upng_get_palsize(upng);
				unsigned short cols[256];
				for (int c = 0; c < nbc; c++)
				{
					r = *pal++;
					g = *pal++;
					b = *pal++;
					if (upng_get_format(upng) == UPNG_PALETTEA8)
					{
						alpha = 255 - *pal++;
					}
					cols[c] = getCol(r, g, b, alpha);
				}
				fwrite(&cols, 2, 256, fo);
			}
			break;
		case TEXTURE_PAL4:
			for (unsigned int y = 0; y < h; y++)
			{
				for (unsigned int x = 0; x < w / 2; x++)
				{
					unsigned char idx = *buf++;
					idx = (idx >> 4) | ((idx & 0x0f) << 4);
					fwrite(&idx, 1, 1, fo);
				}
			}
			{
				const unsigned char *pal = upng_get_palette(upng);
				unsigned short nbc = upng_get_palsize(upng);
				unsigned short cols[16];
				for (int c = 0; c < nbc; c++)
				{
					r = *pal++;
					g = *pal++;
					b = *pal++;
					if (upng_get_format(upng) == UPNG_PALETTEA4)
					{
						alpha = 255 - *pal++;
					}
					cols[c] = getCol(r, g, b, alpha);
				}
				fwrite(&cols, 2, 16, fo);
			}
			break;
		}

		fclose(fo);
	}
	upng_free(upng);
	return 0;
}
