#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "evaluator.h"

int evaluatePassword(const char *password)
{
    int score = 0, len = strlen(password);
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;

    for (int i = 0; i < len; i++)
    {
        if (isupper(password[i])) hasUpper = 1;
        else if (islower(password[i])) hasLower = 1;
        else if (isdigit(password[i])) hasDigit = 1;
        else hasSpecial = 1;
    }

    if (len >= 4) score += 15;
    if (len >= 8) score += 15;
    if (len >=12) score += 10;
    if (hasUpper) score += 15;
    if (hasLower) score += 15;
    if (hasDigit) score += 15;
    if (hasSpecial) score += 15;
    return score;
}

void classifyStrength(int score, char *strengthLabel)
{
    if (score <= 30)
        strcpy(strengthLabel, "Weak");
    else if (score <= 60)
        strcpy(strengthLabel, "Moderate");
    else if (score <= 75)
        strcpy(strengthLabel, "Good");
    else
        strcpy(strengthLabel, "Strong");
}
