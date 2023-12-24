#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DIGITS 9
#define BLOCK_DIM 3

typedef unsigned char digit_t;

void pprintgrid(digit_t* grid)
{
    for (int i = 0; i < DIGITS; ++i) {
        if (i > 0 && i % BLOCK_DIM == 0) {
            for (int j = 0; j < BLOCK_DIM; ++j) {
                if (j > 0)
                    printf(" + ");
                printf("-----");
            }
            printf("\n");
        }
        for (int j = 0; j < DIGITS; ++j) {
            if (j > 0 && j % BLOCK_DIM == 0)
                printf("| ");
            printf("%u ", grid[i * DIGITS + j]);
        }
        printf("\n");
    }
}

void printgrid(digit_t* grid)
{
    for (int i = 0; i < DIGITS; ++i) {
        for (int j = 0; j < DIGITS; ++j) {
            printf("%u ", grid[i * DIGITS + j]);
        }
        printf("\n");
    }
}

/*
Updates seen vector for block containing the given point
Returns number of new digits seen
*/
int checkblock(digit_t* grid, int* seen, int r, int c)
{
    int block_r = r / BLOCK_DIM * BLOCK_DIM;
    int block_c = c / BLOCK_DIM * BLOCK_DIM;
    int numseen = 0;
    for (int i = block_r; i < block_r + BLOCK_DIM; ++i) {
        for (int j = block_c; j < block_c + BLOCK_DIM; ++j) {
            digit_t d = grid[i * DIGITS + j];
            if (d == 0)
                continue;
            if (!seen[d]) {
                seen[d] = 1;
                numseen += 1;
            }
        }
    }
    return numseen;
}

/*
Updates seen vector for the given row
Returns number of new digits seen
*/
int checkrow(digit_t* grid, int* seen, int r)
{
    int numseen = 0;
    for (int i = 0; i < DIGITS; ++i) {
        digit_t d = grid[r * DIGITS + i];
        if (d == 0)
            continue;
        if (!seen[d]) {
            seen[d] = 1;
            numseen += 1;
        }
    }
    return numseen;
}

/*
Updates seen vector for the given column
Returns number of new digits seen
*/
int checkcol(digit_t* grid, int* seen, int c)
{
    int numseen = 0;
    for (int i = 0; i < DIGITS; ++i) {
        digit_t d = grid[i * DIGITS + c];
        if (d == 0)
            continue;
        if (!seen[d]) {
            seen[d] = 1;
            numseen += 1;
        }
    }
    return numseen;
}

/*
Returns T if a solution can be produced, F otherwise
*/
int setcell(digit_t* grid, int idx)
{
    // Done
    if (idx == DIGITS * DIGITS) {
        return 1;
    }
    int r = idx / DIGITS;
    int c = (idx % DIGITS + DIGITS) % DIGITS;
    int numseen = 0;
    int seen[DIGITS + 1];
    memset(seen, 0, sizeof(int) * (DIGITS + 1));
    numseen += checkblock(grid, seen, r, c);
    numseen += checkrow(grid, seen, r);
    numseen += checkcol(grid, seen, c);
    while (numseen < DIGITS) {
        digit_t d;
        do {
            d = (rand() % DIGITS + DIGITS) % DIGITS + 1;
        } while (seen[d]);
        seen[d] = 1;
        numseen += 1;
        // Set and try to make progress
        grid[idx] = d;
        if (setcell(grid, idx + 1))
            return 1;
    }
    grid[idx] = 0;
    return 0;
}

int main()
{
    srand(time(NULL));
    digit_t grid[DIGITS * DIGITS];
    memset(grid, 0, sizeof(digit_t) * DIGITS * DIGITS);
    printf("Success? %s\n", setcell(grid, 0) ? "true" : "false");
    pprintgrid(grid);
}
