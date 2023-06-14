#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//Max number of candidates.
#define MAX 9

//Candidates have a structure; name and votes.
typedef struct
{
    string name;
    int votes;
}
candidate;

//We've created an array of type candidate. With this, we have two arrays in one; a candidates[].name array, and a candidates[].votes array.
candidate candidates[MAX];
int candidate_count;
int voter_count;

bool vote(string name);
void print_winner(void);

/*argc represents the number of arguments, including the command to start the program, and argv[] represents an array that contains those arguments.
If we use them, that means that we're going to put some arguments to start our program.*/
int main(int argc, string argv[])
{
    /*As this program simulates an election, and as we might use arguments to run it, if you didn't put nothing, or if you only put a single
    command-line argument, the program will enter to the conditional.*/
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    //We might declare "-1" because remember, even the "./plurality" command-line counts as an argument.
    candidate_count = argc - 1;

    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    /*candidates[i].name it's equal to the index of the argv[] of the i° argument that we input plus one (to not count the "./plurality" argument),
    and with candidates[i].votes, we set as a first instance that each candidate has 0 votes.*/
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    voter_count = get_int("Number of voters: ");

    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        /*If the value that we input in the name variable it isn't a name that it's in the candidates[i].name array,
        the program will enter to the conditional and print an error message.*/
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    //Calls the print_winner() function and, forgive the redundancy, prints the winner.
    print_winner();
}

//vote() function gives to each candidate, its/their corresponding vote/s.
bool vote(string name)
{
    //As the CS50's compiler returns an error when we declare a variable with a NULL value to then , we replace it by a -1.
    int index = -1;

    for (int i = 0; i < candidate_count; i++)
    {
        /*If the i° candidate it's comparatively equal to name, and, as consequence, returns 0 (yes, this function in particular returns 0
        if the result is true), then save the offset in index (this will help us to, at the end of the function, use it properly as an index).
        And use it as an index will alow us to add a vote by 1 to the corresponding candidate.
        Recall that to compare between strings we use strcmp() function. Basically, this's because it's not as easy as directly compare
        them with a comparator operator, due they behave in a special way.*/
        if (strcmp(candidates[i].name, name) == 0)
        {
            index = i;
        }
    }
    if (index == -1)
    {
        return false;
    }

    /*Here we add by 1 to its corresponding candidate, moving us through the array the index (or i) number of times each time
    that the function is called.*/
    candidates[index].votes += 1;
    return true;
}

void print_winner(void)
{
    int topVote = 0;
    int winnersIndexes[MAX];

    for (int i = 0; i < candidate_count; i++)
    {
        /*This case applies when the votes of the i° candidates are comparatively equal to topVote.

        Once a "-1" it's finded in the winnersIndexes[] array, if it's finded (because, again, we had to replace NULL values of the array
        into "-1" values), the j° winner it's added to the winnersIndexes[] array, and, if it's finded, also the conditional will break
        (get out of there).

        We have to do this because:

        1) if there are ties between candidates, we might consider all of them as winners.
        2) Because then we use this/these value/s to refer inside the candidates[].name array, and print its corresponding name.*/
        if (candidates[i].votes == topVote)
        {
            for (int j = 0; j < candidate_count; j++)
            {
                if (winnersIndexes[j] == -1)
                {
                    winnersIndexes[j] = i;
                    break;
                }
            }
        }
        /*This case applies when the votes of the j° candidate are greater than topVote.

        If the votes of the j° candidate are greater than topVote, then all the values that there are in the array
        (instead of "-1" that, in this case, represents NULL), are replaced by the new topVote; the votes of the i° candidate that
        have exceed the previous topVote.*/
        else if (candidates[i].votes > topVote)
        {
            for (int j = 0; j < candidate_count; j++)
            {
                winnersIndexes[j] = -1;
            }
            winnersIndexes[0] = i;
            topVote = candidates[i].votes;
        }
    }

    /*To make our lifes easier, and don't being using calculates to determine the length of the array of the winners, we've decided to
    create an array of chars with enough length.*/
    char winners[2048];

    /*Here we use a for loop that finally determines the winner(s). If winnersIndexes[i] isn't equal than "-1"
    (so that, "there isn't a NULL value"), then currentWinners it's equal to the name of the candidate of the i° winner of the
    winnersIndexes[] array. This means that, the int/s value/s that we've stored in the winnersIndexes[i] array, it's/are the index/es of
    the candidates[].name array that have winned.

    So that, if there are two candidates that have winned with the same amount of votes, by then, we'll have already stored their winnersIndexes[j]
    values (see line 103). With those values, we used them to indicate in the currentWinner variable, in what position are its names
    inside the candidates[].name array. The same thing happens if there's only a winner.

    Then, the strcat() function adds something that you want, to a variable or an array that you specify. As a first argument,
    the strcat() function takes the destination, where we want to paste the second argument. And, well, the second argument is
    what we want to copy and paste. We had to do another strcat() function to print a new line. Otherwise, we couldn't have done it.*/
    for (int i = 0; i < candidate_count; i++)
    {
        if (winnersIndexes[i] != -1)
        {
            string currentWinner = candidates[winnersIndexes[i]].name;
            strcat(winners, currentWinner);
            strcat(winners, "\n");
        }
    }
    printf("%s\n", winners);
    return;
}