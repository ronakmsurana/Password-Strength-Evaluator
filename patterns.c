#include <stdio.h>
#include <string.h>
#include "patterns.h"

void analyzePatterns(int *score, const char *password) {
    int repeat = 1;
    int forward = 1;
    int backward = 1;
    int warned = 0;
    for (int i = 1; password[i] != '\0'; i++) {
        if (password[i] == password[i-1])
        {
            repeat++;
            if (repeat >= 4 && !warned) {
                printf("- Warning: pattern detected\n");
                warned = 1;
            }
        } 
        else repeat = 1;
        if(password[i] == password[i-1]+1)
        {
            forward +=1;
            if (forward >= 4 && !warned) {
                printf("- Warning: pattern detected\n");
                warned = 1;
            }
        } 
        else forward = 1;
        if(password[i] == password[i-1]-1)
        {
            backward +=1;
            if (backward >= 4 && !warned) {
                printf("- Warning: pattern detected\n");
                warned = 1;
            }
        } 
        else backward = 1;
    }
    if(warned)
        *score -= 15;
}
