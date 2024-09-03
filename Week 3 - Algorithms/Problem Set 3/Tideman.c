#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
int locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
char *candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
int vote(int rank, char *name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
int checkCycle(int winner, int loser);
void lock_pairs(void);
void print_winner(void);

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = 0;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            char *name = get_string("Rank %i: ", j + 1);

            if (vote(j, name, ranks) == 0)
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
int vote(int rank, char *name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if ((strcmp(candidates[i], name)) == 0)
        {
            ranks[rank] = i;
            return 1;
        }
    }
    return 0;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
            // Candidate i is prefered over candidate j (next in line of rank array)
            // so therefore, the counter is increased
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair temppair;

    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] <
                preferences[pairs[j + 1].winner][pairs[j + 1].loser])
            {
                temppair = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temppair;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!(checkCycle(pairs[i].winner, pairs[i].loser)))
        {
            locked[pairs[i].winner][pairs[i].loser] = 1;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int counter = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (!(locked[j][i]))
            {
                counter++;
            }
        }
        if (counter == candidate_count)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}

int checkCycle(int winner, int loser)
{
    if (loser == winner)
    {
        return 1; // Base Case
    }
    for (int i = 0; i < pair_count; i++)
    {
        if (locked[loser][i])
        {
            if (checkCycle(winner, i))
            {
                return 0;
            }
        }
    }
    return 0;
}
