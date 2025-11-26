#include "crypt.h"
#include <ctype.h>
#include "history.h"
void encrypt(char *str, int key)
{
    int shift = (key % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE;
    for (int i = 0; str[i] != '\0'; i++)
    {
        char c = str[i];
        c = (c + shift) % ALPHABET_SIZE;
        
        str[i] = (char)c;
    }
}
void decrypt(char *str, int key)
{
    int shift = (key % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE;
    for (int i = 0; str[i] != '\0'; i++)
    {
        char c = str[i];
        c = (c - shift + ALPHABET_SIZE) % ALPHABET_SIZE;   
        str[i] = (char)c;
    }
}