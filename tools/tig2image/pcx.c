
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "texture.h"

typedef struct
{
	unsigned char manufacturer,version,encoding,bitsPerPlane;
	unsigned short Xmin,Ymin,Xmax,Ymax,VertDPI,HorzDPI;
	unsigned char palette[48];
	unsigned char reserved,colorPlanes;
	unsigned short bytesPerPlaneLine,paltype,hScrSize,vScrSize;
	char pad[54];
}PCX_Header;

Texture *Load_pcx(const char *filename)
{
	FILE *file;
	file = fopen(filename,"rb");

	if(file == NULL) return NULL;


	PCX_Header pcx;
	fread(&pcx,1,sizeof(PCX_Header),file);

	if(pcx.manufacturer != 0x0A)
	{
		fclose(file);
		return NULL;
	}

	Texture *texture = NULL;
	texture = malloc(sizeof(Texture));
	texture->pixel = NULL;
	texture->palette = NULL;

	texture->w = pcx.Xmax - pcx.Xmin + 1;
	texture->h = pcx.Ymax - pcx.Ymin + 1;

	texture->format = FORMAT_8BPP;

	texture->size = texture->w*texture->h;
	texture->pixel = malloc(texture->size);

	int i,pal1,pal2,l,psize = texture->size+0x301;

	//printf("%d\n",psize);
	unsigned char *buf = malloc(psize);
	fread(buf,1,psize,file);

	fclose(file);

	int k = 0;
	for(i = 0;i<texture->size;)
	{
		pal1 = buf[k++];
		if(pal1 <= 0xC0)
		{
			texture->pixel[i] = pal1;
			i++;
		}else
		{
			pal2 = buf[k++];
			pal1 &= 0x3F;
			for(l = 0;l < pal1;l++)
			{
				texture->pixel[i] = pal2;
				i++;
			}
		}

	}

	pal1 = buf[k++];
	if(pal1 == 0x0C)
	{
		texture->palsize = 0x300;
		texture->palette = malloc(0x300);
		memcpy(texture->palette,&buf[k],0x300);
	}

	free(buf);

	return texture;
}
