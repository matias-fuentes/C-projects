//The "ctype.h" library has got functions that checks whether a character is from a determined type or not.

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    /*We use float numbers instead of integer numbers because then we'll make a division between them that, generally, returns a float value.
    Also, the wordCounter variable initializes with one because our conditional sum by one only if in the text[i] there's a space,
    and, as with the first word we don't write a space...*/
    float letterCounter = 0.0;
    float wordCounter = 1.0;
    float sentenceCounter = 0.0;

    string text = get_string("Put your text to evaluate its grade level: ");

    for (int i = 0; text[i]; i++)
    {
        //The isalpha() function checks whether a character is alphabetical, to count letters.
        if (isalpha(text[i]))
        {
            letterCounter++;
        }
        //The isblank() function checks whether a character is a space, to count words.
        if (isblank(text[i]))
        {
            wordCounter++;
        }
        /*There's an "ispunct()" function, but, that function doesn't fit well with our program, so, we've created our own conditional
        to count sentences.*/
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentenceCounter++;
        }
    }

    /*Here we use the "Coleman-Liau" index, a formula that determines the grade level of a text.

    L = the average number of letters per 100 words,
    S = the average number of sentences per 100 words, and
    floatIndex = the formula.*/
    float L = letterCounter / wordCounter * 100;
    float S = sentenceCounter / wordCounter * 100;
    float floatIndex = 0.0588 * L - 0.296 * S - 15.8;

    if (floatIndex < 0)
    {
        printf("Before Grade 1\n");
    }
    if (floatIndex >= 1 && floatIndex < 16)
    {
        floatIndex = round(floatIndex);
        printf("Grade %.0f\n", floatIndex);
    }
    if (floatIndex >= 16)
    {
        printf("Grade 16+\n");
    }
}