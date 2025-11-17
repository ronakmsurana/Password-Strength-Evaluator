/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evaluator.h"
#include "suggestions.h"
#include "history.h"

int main() {
    char password[50];
    char strength[20];
    Node *history = NULL;
    int choice;

    do {
        printf("\n1. Enter Password\n2. View History\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        if (choice == 1) {
            printf("Enter password: ");
            fgets(password, sizeof(password), stdin);
            password[strcspn(password, "\n")] = '\0';

            int score = evaluatePassword(password);
            classifyStrength(score, strength);

            printf("\nPassword Strength: %s (Score: %d)\n", strength, score);
            if (strcmp(strength, "Strong") != 0)
                suggestImprovements(password);

            push(&history, password);
        }
        else if (choice == 2)
            displayHistory(history);

    } while (choice != 3);

    return 0;
}
    /*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evaluator.h"
#include "suggestions.h"
#include "history.h"

int main() {
    char password[50];
    char strength[20];
    StackNode *stackTop = NULL;
    TrieNode *trieRoot = createTrieNode();
    TrieNode *commonPassword = createTrieNode();
    char buffer[50];
    int choice;
    loadTrieFromFile(commonPassword, "common_passwords.txt");

    do {
        printf("\n1. Enter Password\n2. View Stack History\n3. View Trie History (All Passwords)\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        if (choice == 1) {
            printf("Enter password: ");
            fgets(password, sizeof(password), stdin);
            password[strcspn(password, "\n")] = '\0';

            // Check if password already exists
            if (searchTrie(trieRoot, password)) {
                printf("\n⚠️  Password already exists in history!\n");
                continue;
            }
            if (searchTrie(commonPassword, password)) {
                printf("\nPassword Strength: VERY WEAK (Score: 0)\n");
                printf("This is one of the most common passwords. Please choose something unique.\n");
                // Note: We don't push this to history because it's so bad
                continue; // Go back to menu
            }
            int score = evaluatePassword(password);
            classifyStrength(score, strength);

            printf("\nPassword Strength: %s (Score: %d)\n", strength, score);
            if (strcmp(strength, "Strong") != 0)
                suggestImprovements(password);

            push(&stackTop, password);
            insertTrie(trieRoot, password);
        }
        else if (choice == 2) {
            displayStack(stackTop);
        }
        else if (choice == 3) {
            printf("\n--- Trie (All Stored Passwords Alphabetically) ---\n");
            displayTrie(trieRoot, buffer, 0);
        }

    } while (choice != 4);

    return 0;
}
