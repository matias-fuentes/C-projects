/*The max number of voters it's of 100, since the max number of candidates it's of nine.
The extern file we'll use it to print the winner/s to stdout.*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9
extern FILE *stdout;

//Candidates have a structure; name, votes, and eliminated status.
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

candidate candidates[MAX_CANDIDATES];
int preferences[MAX_VOTERS][MAX_CANDIDATES];
int voter_count;
int candidate_count;
int candidatesIndex;
int timesEliminated = 0;
float fiftyPercent;

bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;

    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }

    //Fills the array of candidates. candidates[].${attribute} = An array of type candidate, which contains the attributes of a candidate; name, votes, and eliminated status.
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");

    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    //Keep querying for votes.
    for (int i = 0; i < voter_count; i++)
    {
        //Query for each rank.
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            //If the arguments of the vote() function are invalid, then prints an error message and ends the program.
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }
        printf("\n");
    }

    //Keep holding runoffs until winner exists.
    while (true)
    {
        //Calculate votes given remaining candidates.
        tabulate();

        //Check if the election has been won. If won, then the code jumps out of the while-loop.
        bool won = print_winner();
        if (won)
        {
            break;
        }

        //find_min() founds the candidate/s who has/have the fewest number of votes, and that is/are still in the election.
        int min = find_min();
        bool tie = is_tie(min);

        //If tie, everyone (who, for that moment, haven't been eliminated) wins. Finally, the code jumps out of the while-loop.
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        //Eliminate anyone with minimum number of votes.
        eliminate(min);

        //Reset vote counts back to zero so that in each turn the votes don't accumulates themselves more than necessary.
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

//Record preference if the vote is valid.
bool vote(int voter, int rank, string name)
{
    candidatesIndex = -1;

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            /*candidatesIndex = The index of the i° candidate of the candidates[i].name array. This will be very helpful to iterate over
            the main preferences of the i° voter.*/
            candidatesIndex = i;
            break;
        }
    }

    if (candidatesIndex == -1)
    {
        return false;
    }

    //preferences[i (voter)][j (rank)] = The j° preference of the voter i.
    preferences[voter][rank] = candidatesIndex;
    return true;
}

//tabulate() assign votes to non-eliminated candidates, that are the main preference between the candidates that aren't eliminated.
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            /*The "j == 0" it's necessary to do a linear search.
            If the candidate of the j° preference (in this case, 0) of the voter i it's already still in the election, 
            then sum its votes by one. For example:

            Candidates: Alice, Bob, and Charlie.
            Number of voters: 1 (with this program this one voter would't be possible, but, we don't need more for this example
            to understand how this works).

            Rank 1: Bob.
            Rank 2: Alice.
            Rank 3: Charlie.

            If "j == 0" in the conditionals, that means, that when j == 0, the "preferences[i][j]" of the second requirement
            make reference to the [0] preference of the voter i.

            As the preferences[][] record the preferences, that means its first index, 0 (or j), records its principal preference.
            Here, its principal preference is Bob.
            However, as the preferences[][] array it's an array of ints, it can't store "Bob", since it's a string.
            In this case, stores its corresponding index of the candidates[].${attribute} array (1).

            With this, we can make reference to the corresponding candidate with no problem
            if we assign it as an index ("candidates[preferences[i][j]].eliminated").*/
            if (j == 0 && candidates[preferences[i][j]].eliminated == false)
            {
                candidates[preferences[i][j]].votes++;
            }

            /*If Bob was eliminated, then we have to sum a vote to its consecutive preference; Alice,
            so, we create a while-loop that iterates over and over until a preferred candidate that's not eliminated is reached.
            And then, we asign a vote to him/her.*/
            else if (j == 0 && candidates[preferences[i][j]].eliminated == true)
            {
                int k = j;
                while (candidates[preferences[i][j + k]].eliminated == true)
                {
                    k++;
                }
                candidates[preferences[i][j + k]].votes++;
            }
        }
    }
}

//Prints the winner/s of the election, if there's one.
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        //fiftyPercent represents the barrier that we have to surpass to reach the majority (more than 50% of the votes).
        fiftyPercent = voter_count / 2;

        if (candidates[i].votes > fiftyPercent)
        {
            //The first parameter it's the destination of what we want to print.
            fprintf(stdout, "%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

//Return the minimum number of votes any remaining candidate has.
int find_min(void)
{
    /*minVote[] it's an array where we were adding and replacing in function of what we need the minimum number of votes
    that the code will be finding. By this way, we'll have an actualized array with the actual minimum number of votes in that moment
    that any remaining candidate has. minVoteIndex will store the index of the last element added in the minVote[] array.
    We'll use it to know in what index we'll place our next min vote.*/
    int minVote[candidate_count];
    int minVoteIndex;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            //Always the first candidate at a first instance is stored in the array.
            if (i == 0)
            {
                minVote[i] = candidates[i].votes;
                minVoteIndex = i;
            }
            /*If the votes of the i° candidate are lesser than the last number of minimum votes added on the minVote[] array,
            then we clean it, and replace by the new minimum vote number.*/
            else if (candidates[i].votes < minVote[minVoteIndex])
            {
                for (int j = 0; j < candidate_count; j++)
                {
                    minVote[j] = 0;
                }
                minVote[0] = candidates[i].votes;
                minVoteIndex = 0;
            }
            /*If the votes of the i° candidate are comparatively equal to the last number of minimum votes added on the minVote[] array,
            then we add it.*/
            else if (candidates[i].votes == minVote[minVoteIndex])
            {
                minVote[minVoteIndex + 1] = candidates[i].votes;
                minVoteIndex++;
            }
        }
    }

    return minVote[0];
}

//Return true if the election is tied between all the candidates that in that moment are remaining, false otherwise.
bool is_tie(int min)
{
    /*We call the eliminate() function in each turn because we need to actualize the timesEliminated value,
    to, in consecuence, obtain the actualized remainingCandidates value.*/
    eliminate(min);

    /*minLimiter is used to compare when there's a tie, but it isn't between all the candidates.
    Instead, maxLimiter is used to compare when effectively there's a tie between all the candidates.*/
    int remainingCandidates = candidate_count - timesEliminated;
    int minLimiter = 0;
    int maxLimiter = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        /*We create a while-loop that iterates over and over until a candidate that's not eliminated is reached.
        And then, if the votes of the i° candidate are comparatively equal to the votes of the i° + j candidate
        (the next candidate not eliminated that we in the previous while loop have find), we sum the minLimiter variable by one.*/
        int j = i;
        while (candidates[j].eliminated == true)
        {
            j++;
        }
        if (candidates[i].votes == candidates[i + j].votes)
        {
            minLimiter++;
        }
    }

    /*How this for-loop checks if there's a tie between all the candidates, we can skip the while-loop step what have we done before,
    since to accomplish this requirement all the candidates will need to have the same amount of votes, without omissions.*/
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == candidates[i + 1].votes)
        {
            maxLimiter++;
        }
    }

    /*If the number of times that the minLimiter variable was summed by one it's comparatively equal to the number of remaining candidates,
    then return true.
    Else if the number of times that the maxLimiter variable was summed by one it's comparatively equal to all the candidates (candidate_count),
    then also return true.*/
    if (minLimiter == remainingCandidates)
    {
        return true;
    }
    else if (maxLimiter == candidate_count)
    {
        return true;
    }

    //Otherwise, return false.
    return false;
}

//Eliminate candidate/s in last place.
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        /*If the votes of the i° candidate are comparatively equal to min (the, in that moment, fewest numbers of votes that
        any remaining candidate has), then eliminate him/her.*/
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
            /*timesEliminated = The number of times that a candidate has been eliminated. With this, we'll can know how many remaining candidates
            are still in the election.*/
            timesEliminated++;
        }
    }
    return;
}