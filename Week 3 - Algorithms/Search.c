#include <stdio.h>

// Functions

// Structures

typedef struct {
    char *name;
    int votes;
}
candidate;

int main(void)
{
    const int numCandidates = 4;
    candidate candidates[numCandidates];

    candidates[0].name = "Carter";
    candidates[0].votes = 10;

    candidates[1].name = "Yuliia";
    candidates[1].votes = 5;

    candidates[2].name = "Inno";
    candidates[2].votes = 7;

    candidates[3].name = "Kai";
    candidates[3].votes = 15;

    // Find highest number of votes
    int highestVotes = 0;
    for (int i = 0; i < numCandidates; i ++) {
        if (highestVotes < candidates[i].votes) {
            highestVotes = candidates[i].votes;
        }
    }
    printf("Highest vote number is %i\n", highestVotes);

    // Print name of candidate with highest votes
    for (int i = 0; i < numCandidates; i ++) {
        if (highestVotes == candidates[i].votes) {
            printf("The name of the candidate with the highest number of votes is %s\n", candidates[i].name);
        }
    }
}
