

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "texture.h"

void write_tig(const char *filename,Texture *texture,int *option);

int main(int argc, char** argv)
{
    int i,ok = 0;

	int option[10];
	char address[512];

	for(i = 0; i < 10;i++)
		option[i] = 0;

	address[0] = 0;

	for(i = 1; i < argc;i++)
	{
		if(argv[i][0] == '-')
		{
			if(strcmp(argv[i],"-noalpha") == 0) option[1] = 1;
			if(strcmp(argv[i],"-palette") == 0) option[2] = 1;

			if(strcmp(argv[i],"-2bpp") == 0) option[0] = 4;
			if(strcmp(argv[i],"-4bpp") == 0) option[0] = 16;
			if(strcmp(argv[i],"-8bpp") == 0) option[0] = 256;

			if(strcmp(argv[i],"-psx") == 0) option[3] = 1;

			ok = 0;


		}else
		{
			if(ok == 0) strcpy(address,argv[i]);
			if(ok == 2) option[5] = atoi(argv[i]);
			ok = 0;
		}
	}

	if(address[0] == 0)
	{
		printf("Enter a picture format  BMP , PCX , PNG\n");
		
		printf("\noption forced : -2bpp,-4bpp ,-8bpp (only if exist palette)\n");

		printf("\nExemple :\nimage2tig myimage.png\n");
		return 0;
	}

	Texture *texture = Load_image(address);
	if(texture == NULL)
	{
		printf("Unknow format\n");
		return 0;
	}

	write_tig(address,texture,option);

    return 0;
}


Texture *Load_image(const char *filename)
{
	Texture *texture;

	texture = Load_bmp(filename);
	if(texture != NULL) return texture;

	texture = Load_pcx(filename);
	if(texture != NULL) return texture;

	//texture = Load_png(filename);
	if(texture != NULL) return texture;

	return NULL;
}


void output_filename(const char *address,char *str)
{
	int l = 0;
	int i = 0;
	while(address[i] != 0 && address[i] != '.' )
	{
		str[l] = address[i];
		l++;

		if(address[i] == '/' || address[i] == '\\') l = 0;
		i++;
	}
	str[l] = 0;
}

void convertToUpperCase(char *str)
{
	int i = 0;
	char ch = str[i];
    while (ch != 0)
	{
		ch = str[i];
        if (ch >= 'a' && ch <= 'z')
            str[i] = ch - ('a' - 'A');
        i++;
    }
}

void write_file(const char *filename,Texture *texture,char mode)
{
	FILE *file;
	char fname[256];
	output_filename(filename,fname);
	strcat(fname,".tig");

	convertToUpperCase(fname);
	
	file = fopen(fname,"wb");

	if(file == NULL) return;
	TEXTURE_HEADER texturehead;

	TIG_INIT(&texturehead,texture->w,texture->h,mode);
	fwrite(&texturehead, sizeof(TEXTURE_HEADER), 1, file);


	fwrite(texture->pixel, texture->size, 1, file);

	if(texture->palsize > 0)
		fwrite(texture->palette, texture->palsize, 1, file);
}


void pixel16b(unsigned char *pixel,unsigned short *spixel,int n,int psx)
{
	unsigned short r,g,b;
	int l = 0;

	for(int i = 0;i < n;i++)
	{
		r = (pixel[l+0] >> 3);
		g = (pixel[l+1] >> 3);
		b = (pixel[l+2] >> 3);
		l += 3;

		if(psx == 1)
			spixel[i] = (b << 10) | (g << 5) | r | 0x8000;
		else
			spixel[i] = (r << 10) | (g << 5) | b;

		if( (pixel[l+0] == 255) && (pixel[l+1] == 0) && (pixel[l+2] == 255) )
			spixel[i] = 0;
	}
}

void write_tig(const char *filename,Texture *texture,int *option)
{
	unsigned char *pixel = texture->pixel;
	unsigned short *spixel,r,g,b;
	int n = texture->w*texture->h;

	if(texture->format == FORMAT_RGB888)
	{
		spixel = malloc(n*2);
		pixel16b(pixel,spixel,n,option[3]);

		free(texture->pixel);
		texture->pixel = (unsigned char *)spixel;
		texture->size = n*2;

		write_file(filename,texture,TEXTURE_RGB1555);
	}

	if(texture->format == FORMAT_8BPP)
	{
		pixel = texture->palette;
		spixel = malloc(0x200);

		pixel16b(pixel,spixel,0x100,option[3]);

		texture->palette = (unsigned char *)spixel;
		texture->palsize = 0x200;
		write_file(filename,texture,TEXTURE_PAL8);
	}
}
