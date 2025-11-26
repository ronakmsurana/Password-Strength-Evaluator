#ifndef HISTORY_H
#define HISTORY_H

#define ALPHABET_SIZE 128  // to handle all ASCII chars

// Stack Node
typedef struct StackNode
{
    char password[50];
    struct StackNode *next;
} StackNode;

// Trie Node
typedef struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    int isEndOfWord;
} TrieNode;

// Stack functions
void push(StackNode **top, const char *password);
void displayStack(StackNode *top);

// Trie functions
TrieNode* createTrieNode();
void insertTrie(TrieNode *root, const char *password);
int searchTrie(TrieNode *root, const char *password);
void displayTrie(TrieNode *root, char *buffer, int depth);

#endif
