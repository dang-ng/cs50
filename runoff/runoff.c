#include <cs50.h>
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
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
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
        candidates[i].eliminated = false;
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
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }
        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
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
bool vote(int voter, int rank, string name)
{
    for (int k = 0; k < candidate_count; k++)
        if (strcmp(name, candidates[k].name) == 0)
        {
            preferences[voter][rank] = k;
            return true;
        }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    int q;
    for (int l = 0; l < voter_count; l++)
    {
        for (int m = 0; m < candidate_count; m++)
        {
            q = preferences[l][m];
            if (candidates[q].eliminated == false)
            {
                candidates[q].votes++;
                break;
            }

            // if (candidates[m].eliminated = true)
            // {

            // }

        }

    }
// // my preferences ***************************************************************************************
//     printf("number of candidates: %d\nnumber of voters: %d\n", candidate_count, voter_count);
//     for (int loop2 = 0; loop2 < voter_count; loop2++)
//     {
//         for (int loop1 = 0; loop1 < candidate_count; loop1++)
//         {
//             printf("%i", preferences[loop2][loop1]);
//         }
//         printf("\n");
//     }

//     for (int vot = 0; vot < candidate_count; vot++)
//     {
//         printf("số vote của candidates %s: %i\n", candidates[vot].name, candidates[vot].votes);
//     }

// // my preferences ***************************************************************************************

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int w = 0; w < candidate_count; w++)
    {
        if (candidates[w].votes > (voter_count / 2))
        {
            printf("%s\n", candidates[w].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int fmin = candidates[0].votes;
    for (int n = 0; n < candidate_count; n++)
    {
        if (candidates[n].eliminated == false && candidates[n].votes < fmin)
        {
            fmin = candidates[n].votes;
        }
    }
    // printf("loser name: %s & loser votes: %i\n", loser[0].name, loser[0].votes);

    return fmin;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int tie = 0; tie < candidate_count; tie++)
    {
        if (candidates[tie].eliminated == false && candidates[tie].votes != min)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int eliminate = 0; eliminate < candidate_count; eliminate++)
    {
        if (candidates[eliminate].votes == min)
        {
            candidates[eliminate].eliminated = true;
        }
    }
    return;
}