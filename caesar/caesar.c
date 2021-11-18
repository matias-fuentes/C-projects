/*The "ctype.h" library has got functions that checks whether a character is from a determined type or not.
Thils will be very helpful to check if there are special symbols to know then if encrypt it or not.

The "string.h" library has got a function that calculates the length of a parameter. That will be useful to create arrays
and iterate them by an optimally way.

The "stdlib.h" library has got a function that turns a string into an int. With this, we'll work with the k number.*/

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*argc represents the number of arguments, including the command to start the program, and argv[] represents an array that contains those arguments.
If we use them, that means that we're going to put some arguments to start our program.*/
int main(int argc, string argv[])
{
    //This helps us to directly input the k number as a constructor.
    if (argc == 1)
    {
        return 1;
    }

    //Here we store the number of positions to shift over the alphabet. We store it as a string because the argv[] array stores it as an array.
    string k = argv[1];

    //With this, if the user doesn't input a number as an argument, the program will print a message to explain him/her how the program works.
    for (int i = 0; k[i]; i++)
    {
        if (!(isdigit(k[i])) || argc != 2)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    //plaintext it's the text to be encrypted.
    string plaintext = get_string("plaintext: ");

    /*ciphertext[] it's an array where we'll store the text already encrypted, and strlen(plaintext) means that the array will have
    the same length as its parameter, plaintext.*/
    char ciphertext[strlen(plaintext)];

    for (int j = 0; j < strlen(plaintext); j++)
    {
        /*Here startPosition will represent our actual position in the ASCII alphabet while running our program, telling us if we're dealing
        with an uppercase, or a lowercase. We'll need it to use then on the formula.*/
        int startPosition;

        //isupper() detects if the parameter it's an uppercase.
        if (isupper(plaintext[j]))
        {
            //65 represents the start code of the uppercase alphabet in ASCII ('A').
            startPosition = 65;
        }
        else
        {
            //While 97 represents the start code of the lowercase alphabet in ASCII ('a').
            startPosition = 97;
        }

        /*formula is the result of the ciphertext[j] character. The atoi() function turns its parameter from a string into an int.

        The formula is: "c° (ciphertext[j]) = (p° (plaintext[j]) + k) % 26". Where, replacing and adding a little bit by the logic of our program:

        c° = formula,
        p° = plaintext[j], and
        k = atoi(k).

        We remain because that will tell us how much remains to reach the c°, and, we remain by 26 because 26 represents
        the number of the entire alphabet, so, if we have a big number, as the remainder first DIVIDES and then return what remains,
        there should be no problem due to we won't have to count one by one until we reach that number.

        We had to replace c° for formula because we have to then assign it in the c° only if in the p° there's no a punctuation and a space,
        due they don't form part of the alphabet.

        Also we had to add the startPosition due to our start position and the remainder. You can't shift over an alphabet
        either uppercase or lowercase without setting your "start" position, because the start position of the alphabet on our devices
        it's not the same as we interpret in the reality. Since in the reality we section the different types of data, in the technology
        it's not the same. The alphabet it's not sectioned, but rather, it's part of a universified sectioning of symbols called ASCII.
        That's why the code 65 represents 'A', and the code 97 represents 'a'.

        So, if we want to move for, example, 35 positions, it doesn't make sense that our start position be zero,
        because we would be moving until we meet with the symbol with the code 35, the "#", and we don't want that.*/
        int formula = startPosition + (plaintext[j] + atoi(k) - startPosition) % 26;

        if (!ispunct(plaintext[j]) && !isspace(plaintext[j]))
        {
            ciphertext[j] = formula;
        }
        else
        {
            ciphertext[j] = plaintext[j];
        }
    }
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}