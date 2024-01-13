
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int loadFile(const char* filename,void *inbuffer,int *sz)
{
	uint32_t fileSize;
    FILE* file = fopen(filename, "rb");
    if (file == NULL)
    {
        fprintf(stderr, "Impossible to open the file : %s\n", filename);
        return 0;
    }

    fseek(file, 0, SEEK_END);
	fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (fileSize <= 0)
    {
        fprintf(stderr, "Empty file: %s\n", filename);
        fclose(file);
        return 0;
    }

    char* buffer = (char*)malloc(fileSize);
    if (buffer == NULL)
    {
        fprintf(stderr, "Memory allocation error :%s /%d\n",filename,fileSize);
        fclose(file);
        return 0;
    }

    int bytesRead = fread(buffer, 1, fileSize, file);
    if(bytesRead != fileSize)
    {
        fprintf(stderr, "Error reading file : %s\n", filename);
        fclose(file);
        free(buffer);
        return 0;
    }

    fclose(file);

    inbuffer = buffer;
    *st = fileSize;

    return 1;
}
