#include <stdio.h>
#include "visualizer.h"

void printStrengthBar(int score)
{
    if (score < 0) score = 0;
    if (score > 100) score = 100;
    int blocks = 20;
    int filled = (score * blocks) / 100;
    printf("Strength: [");
    for (int i = 0; i < filled; i++) putchar('#');
    for (int i = filled; i < blocks; i++) putchar('.');
    printf("] %d%%\n", score);
}
