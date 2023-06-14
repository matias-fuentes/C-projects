#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Waits for an input, and stores it in the variable.
    string name = get_string("What's your name?\n");

    //Prints that value that has stored, concatenated with a "hello" before it.
    printf("hello, %s\n", name);
}