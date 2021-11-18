// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 143091;

// Hash table
node *table[N];

unsigned int dictionaryWords = 0;

bool test = false;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *tmp = table[hash(word)];

    while (tmp != NULL)
    {
        if (strlen(word) == strlen(tmp->word))
        {
            for (int j = 0; strcasecmp(&word[j], &tmp->word[j]) == 0; j++)
            {
                if (j == strlen(word) - 1)
                {
                    return true;
                }
            }
            tmp = tmp->next;
        }
        else
        {
            tmp = tmp->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int i = 0;
    unsigned long long int bucket = 1;
    while (word[i] != '\0')
    {
        if (i < 9)
        {
            bucket *= tolower(word[i]);
        }
        i++;
    }
    bucket %= 143091;

    return bucket;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *input = fopen(dictionary, "r");

    for (unsigned int i = 0; i < N + 1; i++)
    {
        int k = 0;
        unsigned long long int bucket = 1;
        char auxiliar[LENGTH + 1];

        for (int j = 0; auxiliar[j - 1] != '\n'; j++)
        {
            if (!fread(&auxiliar[j], 1, 1, input))
            {
                fclose(input);
                test = true;
                return true;
            }
            if (auxiliar[j] == '\n')
            {
                dictionaryWords++;
                k = j;
                int l = 0;

                while (l < j && l < 9)
                {
                    bucket *= auxiliar[l];
                    l++;
                }
                bucket %= N;
            }
        }
        auxiliar[k] = '\0';

        int m = 0;

        node *n = malloc(sizeof(node));
        node *tmp;
        node *tmp2;

        while (m <= k)
        {
            n->word[m] = auxiliar[m];
            m++;
        }

        if (table[bucket] == NULL)
        {
            table[bucket] = n;
        }
        else
        {
            tmp = table[bucket];
            while (tmp != NULL)
            {
                tmp2 = tmp;
                tmp = tmp->next;
            }
            tmp2->next = n;
        }
    }

    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size()
{
    // TODO
    if (test)
    {
        return dictionaryWords;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *tmp;
        while (table[i] != NULL)
        {
            tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }

        if (i == N - 1)
        {
            return true;
        }
    }

    return false;
}