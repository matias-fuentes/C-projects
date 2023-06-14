#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int pyramidSize;

    do
    {
        //Waits for an input, and stores it in the variable.
        pyramidSize = get_int("Size of the pyramid? Please, input a number between one and eight: ");
    }
    //If the input doesn't accomplish with the requirements, the do-while loop will ask for an input again.
    while (pyramidSize < 1 || pyramidSize > 8);

    //The for-loops iterates over the size of the pyramid. Since one iterates over the height, the other iterates over the width.
    for (int i = pyramidSize; i > 0; i--)
    {
        for (int j = 0; j < pyramidSize; j++)
        {
            if (i <= j + 1)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}