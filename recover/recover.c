#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    uint8_t buffer[16000];
    char jpgCounter[8];
    int intCounter = 0;
    sprintf(jpgCounter, "00%i.jpg", intCounter);
    FILE *image = fopen(argv[1], "r");
    FILE *jpg = fopen(jpgCounter, "w");

    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    for (int i = 0; i < 16000; i++)
    {
        if (fread(&buffer[i], 512, 1, image))
        {
            if (buffer[i] == 255 && buffer[i + 1] == 216 && buffer[i + 2] == 255)
            {
                fclose(jpg);
                if (intCounter < 10)
                {
                    sprintf(jpgCounter, "00%i.jpg", intCounter);
                    jpg = fopen(jpgCounter, "w");
                    fwrite(&buffer[i], 512, 1, jpg);
                    intCounter++;
                }
                else
                {
                    sprintf(jpgCounter, "0%i.jpg", intCounter);
                    jpg = fopen(jpgCounter, "w");
                    fwrite(&buffer[i], 512, 1, jpg);
                    intCounter++;
                }
            }
            else
            {
                fwrite(&buffer[i], 512, 1, jpg);
            }
        }
    }
    return 0;
}