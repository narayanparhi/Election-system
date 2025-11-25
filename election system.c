#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define the maximum number of candidates and the name length
#define MAX_CANDIDATES 5
#define NAME_LENGTH 30

// Structure to hold candidate information
struct candidate {
    int id;
    char name[NAME_LENGTH];
    int vote_count;
};

// Global array to store candidate data
struct candidate candidates[MAX_CANDIDATES];
int total_candidates = 0;

/**
 * @brief Initializes a set of fixed candidates for the election.
 */
void setup_candidates() {
    // Manually setting up candidates for simplicity
    
    if (MAX_CANDIDATES < 3) return; // Ensure at least 3 candidates
    
    // Candidate 1
    candidates[0].id = 1;
    strcpy(candidates[0].name, "Alice (The Builder)");
    candidates[0].vote_count = 0;
    
    // Candidate 2
    candidates[1].id = 2;
    strcpy(candidates[1].name, "Bob (The Visionary)");
    candidates[1].vote_count = 0;
    
    // Candidate 3
    candidates[2].id = 3;
    strcpy(candidates[2].name, "Charlie (The Reformer)");
    candidates[2].vote_count = 0;

    total_candidates = 3; // Update the count of active candidates
    
    printf("\n--- Election Setup Complete ---\n");
    printf("%d candidates are contesting the election.\n", total_candidates);
}

/**
 * @brief Displays the list of candidates to the voter.
 */
void display_candidates() {
    printf("\n============================\n");
    printf("     VOTING BOOTH\n");
    printf("============================\n");
    for (int i = 0; i < total_candidates; i++) {
        printf(" %d. %s\n", candidates[i].id, candidates[i].name);
    }
    printf("============================\n");
}

/**
 * @brief Allows a voter to cast a vote.
 */
void cast_vote() {
    int choice;
    printf("\nEnter your choice (Candidate ID) to vote: ");
    if (scanf("%d", &choice) != 1) {
        // Handle invalid input (e.g., non-numeric)
        printf("\n❌ Invalid input. Please enter a number.\n");
        // Clear the input buffer
        while (getchar() != '\n'); 
        return;
    }
    
    // Search for the chosen candidate ID
    for (int i = 0; i < total_candidates; i++) {
        if (candidates[i].id == choice) {
            candidates[i].vote_count++; // Increment vote count
            printf("\n✅ Successfully voted for: %s\n", candidates[i].name);
            return;
        }
    }
    
    // If loop completes without finding a match
    printf("\n⚠ Error: Invalid candidate ID entered.\n");
}

/**
 * @brief Displays the current election results (votes cast so far).
 */
void display_results() {
    printf("\n============================\n");
    printf("       ELECTION RESULTS\n");
    printf("============================\n");
    int total_votes = 0;
    for (int i = 0; i < total_candidates; i++) {
        printf(" %-20s : %d votes\n", candidates[i].name, candidates[i].vote_count);
        total_votes += candidates[i].vote_count;
    }
    printf("----------------------------\n");
    printf(" Total Votes Cast : %d\n", total_votes);
    printf("============================\n");
}

/**
 * @brief Finds and prints the winner of the election.
 */
void declare_winner() {
    if (total_candidates == 0) {
        printf("\n🛑 Cannot declare winner: No candidates setup.\n");
        return;
    }

    int max_votes = -1;
    int winner_index = -1;
    int tie_flag = 0;

    // 1. Find the maximum number of votes
    for (int i = 0; i < total_candidates; i++) {
        if (candidates[i].vote_count > max_votes) {
            max_votes = candidates[i].vote_count;
            winner_index = i;
        }
    }
    
    // 2. Check for a tie
    for (int i = 0; i < total_candidates; i++) {
        if (i != winner_index && candidates[i].vote_count == max_votes) {
            tie_flag = 1;
            break; // A tie is found
        }
    }
    
    printf("\n🎉🎉🎉 ELECTION WINNER ANNOUNCEMENT 🎉🎉🎉\n");
    printf("--------------------------------------------\n");
    
    if (max_votes == 0) {
        printf("No votes were cast! The election is inconclusive.\n");
    } else if (tie_flag) {
        printf("IT'S A TIE!\n");
        printf("The following candidates tied with %d votes:\n", max_votes);
        for (int i = 0; i < total_candidates; i++) {
            if (candidates[i].vote_count == max_votes) {
                printf("- %s\n", candidates[i].name);
            }
        }
    } else {
        printf("The winner is: *%s*\n", candidates[winner_index].name);
        printf("Votes received: %d\n", candidates[winner_index].vote_count);
    }
    printf("--------------------------------------------\n");
}


/**
 * @brief Main function with the menu loop.
 */
int main() {
    int choice;
    
    setup_candidates(); // Initialize candidates

    while (1) {
        printf("\n\n--- Main Menu ---\n");
        printf("1. Cast a Vote\n");
        printf("2. Display Current Results\n");
        printf("3. Declare Winner and Exit\n");
        printf("4. Exit Program (without declaration)\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\n❌ Invalid input. Exiting...\n");
            // Clear buffer and exit on non-numeric input
            while (getchar() != '\n'); 
            break;
        }

        switch (choice) {
            case 1:
                display_candidates();
                cast_vote();
                break;
            case 2:
                display_results();
                break;
            case 3:
                declare_winner();
                return 0; // Exit after declaring winner
            case 4:
                printf("\nExiting program. Goodbye!\n");
                return 0;
            default:
                printf("\n⚠ Invalid choice. Please enter a number between 1 and 4.\n");
        }
    }

    return 0;
}