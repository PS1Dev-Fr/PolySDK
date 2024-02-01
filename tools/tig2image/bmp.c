#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "texture.h"

typedef struct
{
	unsigned short signature;
	unsigned int sizefile;
	unsigned short reserved[2];
	unsigned int offset,BITMAPINFOHEADER,width,height;
	unsigned short nplanes,nbits;
	unsigned int compression,size,hpixel,vpixel,noclors,ncolorsi;
}BMP_Header;

Texture *Load_bmp(const char *filename)
{
	FILE *file;
	file = fopen(filename,"rb");

	if(file == NULL) return NULL;


	BMP_Header bmp;
	fread(&bmp.signature,1,sizeof(unsigned short),file);

	if(bmp.signature != 0x4D42)
	{
		fclose(file);
		return NULL;
	}

	fread(&bmp.sizefile,1,sizeof(BMP_Header)-2,file);

	Texture *texture = NULL;
	texture = malloc(sizeof(Texture));
	texture->pixel = NULL;
	texture->palette = NULL;

	texture->w = bmp.width;
	texture->h = bmp.height;

	if(bmp.nbits == 8)
		texture->format = FORMAT_8BPP;

	if(bmp.nbits == 16)
		texture->format = FORMAT_RGBA1555;

	if(bmp.nbits == 24)
		texture->format = FORMAT_RGB888;

	if(bmp.nbits == 32)
		texture->format = FORMAT_RGBA8888;

	texture->pixelsize = (bmp.nbits>>3);

	texture->size = texture->w*texture->h*(bmp.nbits>>3);
	texture->pixel = malloc(texture->size);

	fseek(file, bmp.offset, SEEK_SET);

	if(bmp.nbits == 8)
	{
		texture->palsize = 0x300;
		texture->palette = malloc(0x300);
		fread(texture->palette,1,0x300,file);
	}

	int i,x,y,pitch,n = texture->w*texture->pixelsize;
	if(bmp.nbits >= 24)
	{
		unsigned char *buf = malloc(texture->size);
		fread(buf,1,texture->size,file);
		int k = 0;

		for(y = texture->h-1;y > 0;y--)
		{
			pitch = y*n;
			for(x = 0;x < n;x += texture->pixelsize )
			{
				i = x + pitch;
				texture->pixel[i+2]= buf[k+0];
				texture->pixel[i+1]= buf[k+1];
				texture->pixel[i+0]= buf[k+2];
				k+=3;

				if(bmp.nbits == 32)
				{
					texture->pixel[i+3]= buf[k];
					k++;
				}
			}
		}

		free(buf);

	}else
		fread(texture->pixel,1,texture->size,file);

	fclose(file);


	return texture;
}

