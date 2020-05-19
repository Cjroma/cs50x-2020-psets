#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    // Check correct usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open file
    FILE *infile = fopen(argv[1], "r");

    // Check if file is present
    if (infile == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    // Allocate memory
    unsigned char *buffer = malloc(512);
    size_t bytes;


    int i = 0;
    bool isNewJPEG = false;
    bool foundJPEG = false;
    FILE *outfile = NULL;

    // Repeat until the end of the file is reach
    while (0 < (bytes = fread(buffer, 512, 1, infile)))
    {
        // Find jpeg in file
        if ((buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF) && (buffer[3] & 0xF0) == 0xE0)
        {
            foundJPEG = true;
            isNewJPEG = true;

            // Close current open outfile if new jpeg is found
            if (outfile != NULL)
            {
                fclose(outfile);
            }
        }
        // If Jpeg is found run this
        if (foundJPEG)
        {
            // Create new jpeg file if found new jpeg
            if (isNewJPEG)
            {
                // Name of file
                char filename[3] = "000";
                sprintf(filename, "%03i.jpg", i);
                ++i;
                // Create jpg file
                outfile = fopen(filename, "w");
                isNewJPEG = false;
            }
            // Write data to created jpg file
            fwrite(buffer, 512, 1, outfile);
        }
    }
    // Close outfile
    fclose(outfile);
    // Free memory allocated
    free(buffer);
    // Close Infile
    fclose(infile);
}
