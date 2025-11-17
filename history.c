/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"

void push(Node **top, const char *password) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        return;
    }
    strcpy(newNode->password, password);
    newNode->next = *top;
    *top = newNode;
}

void displayHistory(Node *top) {
    printf("\nPassword History:\n");
    for (Node *curr = top; curr != NULL; curr = curr->next)
        printf("- %s\n", curr->password);
}/*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"

// ---------------- STACK IMPLEMENTATION ----------------
void push(StackNode **top, const char *password) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        return;
    }
    strcpy(newNode->password, password);
    newNode->next = *top;
    *top = newNode;
}

void displayStack(StackNode *top) {
    printf("\n--- Stack (Recent Passwords) ---\n");
    for (StackNode *curr = top; curr != NULL; curr = curr->next)
        printf("%s\n", curr->password);
}

// ---------------- TRIE IMPLEMENTATION ----------------
TrieNode* createTrieNode() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    if (!node) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    node->isEndOfWord = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    return node;
}

void insertTrie(TrieNode *root, const char *password) {
    TrieNode *curr = root;
    for (int i = 0; password[i] != '\0'; i++) {
        unsigned char index = (unsigned char)password[i];
        if (curr->children[index] == NULL)
            curr->children[index] = createTrieNode();
        curr = curr->children[index];
    }
    curr->isEndOfWord = 1;
}

int searchTrie(TrieNode *root, const char *password) {
    TrieNode *curr = root;
    for (int i = 0; password[i] != '\0'; i++) {
        unsigned char index = (unsigned char)password[i];
        if (curr->children[index] == NULL)
            return 0; // Not found
        curr = curr->children[index];
    }
    return curr != NULL && curr->isEndOfWord;
}

void displayTrie(TrieNode *root, char *buffer, int depth) {
    if (root == NULL) return;

    if (root->isEndOfWord) {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            buffer[depth] = i;
            displayTrie(root->children[i], buffer, depth + 1);
        }
    }
}

// In history.c (make sure to #include <stdio.h> and <string.h> at the top)

void loadTrieFromFile(TrieNode *root, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("WARNING: Could not open common password file: %s\n", filename);
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) > 0) {
            insertTrie(root, line);
        }
    }
    fclose(file);
    printf("Common password dictionary loaded.\n");
}
