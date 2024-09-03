#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    char *name;
    int votes;
    int eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
int vote(int voter, int rank, char *name);
void tabulate(void);
int print_winner(void);
int find_min(void);
int is_tie(int min);
void eliminate(int min);

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = 0;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            char *name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (vote(i, j, name) == 0)
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (1)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        int won = print_winner();
        if (won == 1)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        int tie = is_tie(min);

        // If tie, everyone wins
        if (tie == 1)
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

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
int vote(int voter, int rank, char *name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if ((strcmp(name, candidates[i].name)) == 0)
        {
            preferences[voter][rank] = i; // i is basically the candidate name
            return 1;
        }
    }
    return 0;
}

// Updates the vote count for each candidate
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        printf("Voter number %i\n", i);
        for (int j = 0; j < candidate_count; j++)
        {
            printf("Candidate number %i for voter %i\n", j, i);
            int preference = preferences[i][j];
            if (!(candidates[preference].eliminated))
            { // If the candidate is still on the run...
                printf("This candidate (%i) has not been eliminated. Increasing votes...\n", j);
                candidates[preference].votes++; // Update of the candidate's votes
                break; // We leave early the loop, since only one candidate (top preferred) gets the
                       // vote
            }
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        printf("Candidate number %i total votes are %i\n", i, candidates[i].votes);
    }
    return;
}

// Print the winner of the election, if there is one
int print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > (voter_count / 2))
        { // Candidate wins when it has more than half the votes
            printf("%s\n", candidates[i].name);
            return 1;
        }
    }
    return 0;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = -1; // So we make sure to store the first non eliminated vote
    for (int i = 0; i < candidate_count; i++)
    {
        if (!(candidates[i].eliminated))
        {
            if (min == -1 || candidates[i].votes < min)
            {
                min = candidates[i].votes;
            }
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
int is_tie(int min)
{
    int counter = 0, remainingCandidates = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            counter++;
        }
        if (!(candidates[i].eliminated))
        {
            remainingCandidates++;
        }
    }
    if (counter == remainingCandidates)
    {
        return 1;
    }
    return 0;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = 1;
        }
    }
    return;
}
