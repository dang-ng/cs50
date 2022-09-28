#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Pls try again\n");
        return 1;
    }
// Open memory card **********************
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("File is invalid\n");
        return 1;
    }
    // FILE* img = fopen(filename, "w");
// Repeat until end of card ************
    // while fread == 255
    FILE *outptr = NULL;
    int BLOCK_SIZE = 512;
    unsigned char buffer[BLOCK_SIZE];

    int count = 0;
    int jpg = 0;
// int* buffer[512];
// Read 512 bytes into buffer ***********
    // fread(buffer, sizeof(buffer), 1, inptr);
    while (fread(buffer, BLOCK_SIZE, 1, inptr) == 1)
    {
        //{
        // for (int i = 0;i<999;i++)
        // {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
        {
// if start of new JPG *****************
// if first JPG ********************
            if (jpg)
            {
                fclose(outptr);
            }
            //else ****************************
            // if already found JPG *************
            else
            {
                jpg = 1;
            }
            char filename[8];
            sprintf(filename, "%03d.jpg", count);
            outptr = fopen(filename, "a");
            count++;
        }
        if (jpg == 1)
        {
            fwrite(&buffer, BLOCK_SIZE, 1, outptr);
        }
    }

// Close any remaining files ************
    fclose(inptr);
    fclose(outptr);
    // }
    return 0;
}