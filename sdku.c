#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define digit_t unsigned char
#define DIGITS 9

void printgrid(digit_t* grid)
{
    for (int i = 0; i < DIGITS; ++i) {
        for (int j = 0; j < DIGITS; ++j) {
            printf("%u ", grid[i * DIGITS + j]);
        }
        printf("\n");
    }
}

int main()
{
    srand(time(NULL));
    digit_t* grid = (digit_t*)malloc(sizeof(digit_t) * (DIGITS * DIGITS));
    for (int i = 0; i < DIGITS; ++i) {
        for (int j = 0; j < DIGITS; ++j) {
            grid[i * DIGITS + j] = (rand() % DIGITS + DIGITS) % DIGITS + 1;
        }
    }
    printgrid(grid);
    free((void*)grid);
}
