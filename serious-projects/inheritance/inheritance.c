// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;
int caseCounter = 0;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));
    person *p = NULL;

    // Create a new family with three generations
    p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    // TODO: Allocate memory for new person
    person *n = malloc(sizeof(person));
    person *tmp = n;
    person *tmp2 = n;
    person *list = n;

    int index = 0;
    char oldGenAll[8];
    char parentGenAll[4];

    // Generation with parent data
    if (generations > 1)
    {
        // TODO: Recursively create blood type histories for parents
        if (n == NULL)
        {
            return NULL;
        }

        n = malloc(sizeof(person));

        if (n == NULL)
        {
            free(list);
            return NULL;
        }

        tmp->parents[0] = n;
        tmp = tmp->parents[0];
        person *tmp3 = tmp;

        for (int j = 0; j < 2; j++)
        {
            n = malloc(sizeof(person));

            if (n == NULL)
            {
                free(list->parents[j]);
                free(list);
                return NULL;
            }

            tmp->parents[j] = n;
            n->parents[j] = NULL;

            for (int k = 0; k < 2; k++)
            {
                n->alleles[k] = random_allele();
                oldGenAll[index] = n->alleles[k];
                index++;
            }
        }

        n = malloc(sizeof(person));

        if (n == NULL)
        {
            free(list);
            return NULL;
        }

        tmp2->parents[1] = n;
        tmp2 = tmp2->parents[1];
        person *tmp4 = tmp2;

        for (int j = 0; j < 2; j++)
        {
            n = malloc(sizeof(person));

            if (n == NULL)
            {
                free(list->parents[j]);
                free(list);
                return NULL;
            }

            tmp2->parents[j] = n;
            n->parents[j] = NULL;

            for (int k = 0; k < 2; k++)
            {
                n->alleles[k] = random_allele();
                oldGenAll[index] = n->alleles[k];
                index++;
            }
        }

        tmp3->alleles[0] = oldGenAll[rand() % 2];
        parentGenAll[0] = tmp3->alleles[0];
        tmp3->alleles[1] = oldGenAll[(rand() % 2) + 2];
        parentGenAll[1] = tmp3->alleles[1];

        tmp4->alleles[0] = oldGenAll[(rand() % 2) + 4];
        parentGenAll[2] = tmp4->alleles[0];
        tmp4->alleles[1] = oldGenAll[(rand() % 2) + 6];
        parentGenAll[3] = tmp4->alleles[1];

        list->alleles[0] = parentGenAll[rand() % 2];
        list->alleles[1] = parentGenAll[(rand() % 2) + 2];

        return list;
    }

    // Generation without parent data
    else
    {
        // TODO: Set parent pointers to NULL

        // TODO: Randomly assign alleles
    }

    // TODO: Return newly created person
    return list;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            free(p->parents[i]->parents[j]);
        }
    }

    free(p->parents[0]);
    free(p->parents[1]);
    free(p);
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    printf("Generation %i, blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}