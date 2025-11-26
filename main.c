#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "evaluator.h"
#include "suggestions.h"
#include "history.h"
#include "patterns.h"
#include "visualizer.h"
#include "crypt.h"

int main()
{
    char password[50];
    char strength[20];
    StackNode *stackTop = NULL;
    TrieNode *trieRoot = createTrieNode();
    char buffer[50];
    char encrypted_password[50];
    int choice, key;
    char keyLine[20];

    do
    {
        printf("\n1. Enter Password\n2. View Stack History\n3. View Trie History\n4. Search History (encrypted)\n5. Exit\nEnter choice: "); 
        char line[50];
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%d", &choice);

        if (choice == 1)
        {
            printf("Enter password: ");
            fgets(password, sizeof(password), stdin);
            password[strcspn(password, "\n")] = '\0';

            if (searchTrie(trieRoot, password)) // using advantage of fast trie search
            {
                printf("\n  Password already exists in history!\n");
                continue;
            }

            int score = evaluatePassword(password);
            classifyStrength(score, strength);

            printf("\nPassword Strength: %s (Score: %d)\n", strength, score);

            printStrengthBar(score);
            analyzePatterns(&score, password);

            if (strcmp(strength, "Strong") != 0)
                suggestImprovements(password);

            push(&stackTop, password);
            insertTrie(trieRoot, password);

            printf("Enter an encryption key (e.g., 3): ");
            fgets(keyLine, sizeof(keyLine), stdin);
            sscanf(keyLine, "%d", &key);

            strcpy(encrypted_password, password);
            encrypt(encrypted_password, key);
            printf("\nEncrypted Password: ->%s<-\n", encrypted_password);
        }
        else if (choice == 2)
            displayStack(stackTop);
        else if (choice == 3)
        {
            printf("\n--- Trie ---\n");
            displayTrie(trieRoot, buffer, 0);
        }
        else if (choice == 4)
        {
            char searchStr[50];
            char decryptedStr[50];
            char keyLine[20];
            int key;

            printf("Enter encrypted password to search for: ");
            fgets(searchStr, sizeof(searchStr), stdin);
            searchStr[strcspn(searchStr, "\n")] = '\0';

            printf("  Enter key to decrypt: ");
            fgets(keyLine, sizeof(keyLine), stdin);
            sscanf(keyLine, "%d", &key);

            strcpy(decryptedStr, searchStr);
            decrypt(decryptedStr, key);

            if (searchTrie(trieRoot, decryptedStr))
            {
                printf("  Password found in history.\n");
                printf("  Decrypted Password: %s\n", decryptedStr);
            }
            else
                printf("  Password not found in history.\n");
        }

    } while (choice != 5);

    return 0;
}
