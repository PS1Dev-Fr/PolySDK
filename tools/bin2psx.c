/*
 * bin2psx
 *
 * Converts an bin to PS-EXE
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned char psexe_magic[8] = {'P','S','-','X',' ','E','X','E'};
const char *psexe_marker_usa = "Sony Computer Entertainment Inc. for North America area";
const char *psexe_marker_jpn = "Sony Computer Entertainment Inc. for Japan area";
const char *psexe_marker_eur = "Sony Computer Entertainment Inc. for Europe area";
char *psexe_marker;

long sizebuffer = 0;
char *file_read_buffer(char *namefile)
{
    FILE *file = fopen(namefile, "rb");
    
    if (file == NULL)
	{
        fprintf(stderr, "Could not open objcopy output at %s. Check your permissions. Aborting.\n", namefile);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    sizebuffer = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(sizebuffer + 1);

    if (buffer == NULL)
	{
        fprintf(stderr, "Error malloc\n");
        fclose(file);
        return NULL;
	}

    fread(buffer, 1, sizebuffer, file);

	fclose(file);

    return buffer;
}


int main(int argc, char *argv[])
{
	FILE *objcopy_out, *psexe;
	unsigned int intbuf;
	int x;
	unsigned int gp = 0,sz;
	
	if(argc < 3)
	{
		printf("bin2psx - Converts an ELF executable to PS-EXE\n");
		printf("usage: bin2psx [elf] [ps-x exe] <options>\n");
		printf("\n");
		printf("Options:\n");
		printf("-mark_jpn           - Use Japanese ascii marker (default: USA)\n");
		printf("-mark_eur           - Use European ascii marker (default: USA)\n");
		printf("-mark=<mark>        - Use custom ascii marker <mark>\n");
		return -1;
	}
	
	psexe_marker = (char*)psexe_marker_usa;
	
	for(x = 3; x < argc; x++)
	{
		if(strcmp(argv[x], "-mark_jpn") == 0)
			psexe_marker = (char*)psexe_marker_jpn;
		
		if(strcmp(argv[x], "-mark_eur") == 0)
			psexe_marker = (char*)psexe_marker_eur;
			
		if(strncmp(argv[x], "-mark=", 6) == 0)
		{
			if(strlen(argv[x]) >= 7)
				psexe_marker = argv[x] + 6;
		}
		
		if(strncmp(argv[x], "-gp=", 4) == 0)
		{
			if(strlen(argv[x]) >= 5)
				sscanf(argv[x] + 4, "%x", &gp);
		}	
	}

	//Open objcopy output
	char *buffer = file_read_buffer(argv[1]);

	//File open
	psexe = fopen(argv[2], "wb");
	
	if(psexe == NULL)
	{
		printf("Couldn't open %s for writing. Aborting!\n", argv[2]);
		return -1;
	}

    //Write PSEXE magic string
	fwrite(psexe_magic, sizeof(char), 8, psexe);

	sz = (sizebuffer) + (sizebuffer%0x800);
	fseek(psexe, sz+0x800-4, SEEK_SET);

	intbuf = 0;
	fwrite(&intbuf, sizeof(int), 1, psexe);

	fseek(psexe, 0x10, SEEK_SET);

	//Write initial program counter = 0x80010000
	intbuf = 0x80010000;
	fwrite(&intbuf, sizeof(int), 1, psexe);

	//Global Pointer
	intbuf = gp;
	fwrite(&intbuf, sizeof(int), 1, psexe);

	//text section start address = 0
	intbuf = 0x80010000;
	fwrite(&intbuf, sizeof(int), 1, psexe);

	//Write the address of the text section in the header of the PS-X EXE
	intbuf = (sizebuffer) + (sizebuffer%0x800);
	fwrite(&intbuf, sizeof(int), 1, psexe);

    //Seek output file to 0x30, Initial Stack Pointer = 0x801FFFF0 
	fseek(psexe, 0x30, SEEK_SET);
	intbuf = 0x801FFFF0;
	fwrite(&intbuf, sizeof(int), 1, psexe);

    //Seek output to 0x4C, ASCII marker
	fseek(psexe, 0x4C, SEEK_SET);
	
	int n = strlen(psexe_marker);
	fwrite(psexe_marker, sizeof(char), n, psexe);
	
	//Seek to 0x800, Program Start and write the output of objcopy into the PS-X EXE
	fseek(psexe, 0x800, SEEK_SET);
	fwrite(buffer, sizeof(char), sizebuffer, psexe);
	
	fclose(psexe);
	
	return 0;
}
