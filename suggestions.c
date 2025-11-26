#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "suggestions.h"

void suggestImprovements(const char *password)
{
    int len = strlen(password);
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;

    for (int i = 0; i < len; i++)
    {
        if (isupper(password[i])) hasUpper = 1;
        else if (islower(password[i])) hasLower = 1;
        else if (isdigit(password[i])) hasDigit = 1;
        else hasSpecial = 1;
    }

    printf("\nSuggestions:\n");
    if (len < 8) printf("- Increase password length to at least 8 characters.\n");
    if (!hasUpper) printf("- Add uppercase letters.\n");
    if (!hasLower) printf("- Add lowercase letters.\n");
    if (!hasDigit) printf("- Include numbers.\n");
    if (!hasSpecial) printf("- Include special symbols.\n");
}
