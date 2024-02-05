#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tig2image/texture.h"

typedef struct
{
	unsigned short type;
	unsigned int size;
	unsigned short reserved1;
	unsigned short reserved2;
	unsigned int offset;
} BITMAPFILEHEADER;
// Attention : sizeof(BITMAPFILEHEADER) est arondi de 14 à 16 pour cause d'alignement à 4

typedef struct
{
	unsigned int size;
	int width;
	int height;
	unsigned short planes;
	unsigned short bitCount;
	unsigned int compression;
	unsigned int sizeImage;
	int xPelsPerMeter;
	int yPelsPerMeter;
	unsigned int clrUsed;
	unsigned int clrImportant;
} BITMAPINFOHEADER;

typedef struct
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;
} RGBQUAD;

unsigned short getCol(unsigned char r, unsigned char g, unsigned char b)
{
	r = (r & 0xf8) >> 3;
	g = (g & 0xf8) >> 3;
	b = (b & 0xf8) >> 3;
	unsigned short val = (r << 10) | (g << 5) | b;
	return val;
}

#define PALasRGB 0

int main(int argc, char **argv)
{
	if (argc <= 2)
	{
		return 0;
	}

	FILE *fi = fopen(argv[1], "rb");
	if (fi != NULL)
	{
		BITMAPFILEHEADER bmpf;
		fread(&bmpf.type, 2, 1, fi);
		fread(&bmpf.size, 4, 1, fi);
		fread(&bmpf.reserved1, 2, 1, fi);
		fread(&bmpf.reserved2, 2, 1, fi);
		fread(&bmpf.offset, 4, 1, fi);
		BITMAPINFOHEADER bmp;
		fread(&bmp, sizeof(BITMAPINFOHEADER), 1, fi);

		if ((bmpf.type == 0x4D42) && (bmp.compression == 0))
		{
			TEXTURE_HEADER th;
			strcpy(th.signature, TEXTURE_SIGNATURE);

			th.width = bmp.width;
			th.height = bmp.height;
			th.reserved = 0;
			th.unk2 = 0;
			th.unk3 = 0;

			FILE *fo = fopen(argv[2], "wb");
			if (fo != NULL)
			{
				switch (bmp.bitCount)
				{
				case 4:
#if PALasRGB
					th.mode = TEXTURE_RGB5;
#else
					th.mode = TEXTURE_PAL4;
					th.pitch = th.width << 1;
#endif
					fwrite(&th, sizeof(TEXTURE_HEADER), 1, fo);
					{
						RGBQUAD pal[16];
						fseek(fi, 14 + bmp.size, SEEK_SET);
						fread(&pal, sizeof(RGBQUAD), 16, fi);
						unsigned short cols[16];
						for (int c = 0; c < 16; c++)
						{
							cols[c] = getCol(pal[c].red, pal[c].green, pal[c].blue);
						}
						for (int y = bmp.height - 1; y >= 0; y--)
						{
							fseek(fi, bmpf.offset + y * bmp.width / 2, SEEK_SET);
							for (int x = 0; x < bmp.width / 2; x++)
							{
								unsigned char idx;
								fread(&idx, 1, 1, fi);
#if PALasRGB
								unsigned short val = cols[idx >> 4];
								fwrite(&val, 2, 1, fo);
								val = cols[idx & 0x0f];
								fwrite(&val, 2, 1, fo);
#else
								idx = (idx >> 4) | ((idx & 0x0f) << 4);
								fwrite(&idx, 1, 1, fo);
#endif
							}
						}
#if PALasRGB
#else
						fwrite(&cols, 2, 16, fo);
#endif
					}
					break;
				case 8:
#if PALasRGB
					th.mode = TEXTURE_RGB5;
#else
					th.mode = TEXTURE_PAL8;
					th.pitch = th.width;
#endif
					fwrite(&th, sizeof(TEXTURE_HEADER), 1, fo);
					{
						RGBQUAD pal[256];
						fseek(fi, 14 + bmp.size, SEEK_SET);
						fread(&pal, sizeof(RGBQUAD), 256, fi);
						unsigned short cols[256];
						for (int c = 0; c < 256; c++)
						{
							cols[c] = getCol(pal[c].red, pal[c].green, pal[c].blue);
						}
						for (int y = bmp.height - 1; y >= 0; y--)
						{
							fseek(fi, bmpf.offset + y * bmp.width, SEEK_SET);
							for (int x = 0; x < bmp.width; x++)
							{
								unsigned char idx;
								fread(&idx, 1, 1, fi);
#if PALasRGB
								unsigned short val = cols[idx];
								fwrite(&val, 2, 1, fo);
#else
								fwrite(&idx, 1, 1, fo);
#endif
							}
						}
#if PALasRGB
#else
						fwrite(&cols, 2, 256, fo);
#endif
					}
					break;
				case 24:
					th.mode = TEXTURE_RGB1555;
					th.pitch = th.width >> 1;
					fwrite(&th, sizeof(TEXTURE_HEADER), 1, fo);
					{
						unsigned char col[3];
						for (int y = bmp.height - 1; y >= 0; y--)
						{
							fseek(fi, bmpf.offset + y * 3 * bmp.width, SEEK_SET);
							for (int x = 0; x < bmp.width; x++)
							{
								fread(&col, 1, 3, fi);
								unsigned short val = getCol(col[0], col[1], col[2]);
								fwrite(&val, 2, 1, fo);
							}
						}
					}
					break;
				default:
					th.mode = -1;
					break;
				}

				fclose(fo);
			}
		}
		else
		{
			printf("error: unsupported format %04x %x\n", bmpf.type, bmp.compression);
		}

		fclose(fi);
	}
	else
	{
		printf("error: can't open file %s\n", argv[1]);
	}

	return 0;
}
