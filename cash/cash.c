#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //We use a "owe" variable to, apart from keeping the owe in it, subtract the coins in the conditionals that we're giving to the customer.
    float owe;
    int coins = 0;

    do
    {
        //Waits for an input, and stores it in the variable.
        owe = get_float("How much did I owe you?: ");
    }
    //If the input doesn't accomplish with the requirements, the do-while loop will ask for an input again.
    while (owe <= 0.009);

    //Prints how much we owe with a precission of two decimals.
    printf("Change owed: %.2f\n", owe);

    if (owe >= 0.25)
    {
        /*Here we create a repetition variable. This helps us to subtract high owes repeatedly with our highest coin: the quarter.
        With this, we minimize the amount of coins to pay.*/
        int repetition = owe / 0.25;

        /*When the while loop ends, check if our "change" variable, enters to the next conditional.
        If enters, then check the other next conditional, and so on,
        paying our owe not only with the minimal amount (all with quarters), but also with the optimal amount (dimes, nickels, and pennies).*/
        while (coins < repetition)
        {
            owe -= 0.25;
            coins++;
        }
        if (owe >= 0.1)
        {
            owe -= 0.1;
            coins++;
        }
        if (owe >= 0.05)
        {
            owe -= 0.05;
            coins++;
        }
        if (owe >= 0.009)
        {
            coins++;
        }

        printf("%i\n", coins);
    }
    //If not enters in the first conditional, then check the others, passing first by dimes, then by nickels, and finally by pennies.
    else if (owe >= 0.1)
    {
        owe -= 0.1;
        coins++;
        if (owe >= 0.05)
        {
            owe -= 0.05;
            coins++;
            if (owe >= 0.009)
            {
                coins++;
            }
        }
        printf("%i\n", coins);
    }
    else if (owe >= 0.05)
    {
        owe -= 0.05;
        coins++;
        if (owe >= 0.009)
        {
            coins++;
        }
        printf("%i\n", coins);
    }
    else if (owe <= 0.01)
    {
        coins++;
        printf("%i\n", coins);
    }
}