#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define digit_t unsigned char
#define DIGITS 9
#define CELL_DIM 3

void printgrid(digit_t* grid)
{
    for (int i = 0; i < DIGITS; ++i) {
        for (int j = 0; j < DIGITS; ++j) {
            printf("%u ", grid[i * DIGITS + j]);
        }
        printf("\n");
    }
}

/* T if the cell is valid, F otherwise */
int checkcell(digit_t* grid, int r, int c)
{
    int block_r = r / CELL_DIM * CELL_DIM;
    int block_c = c / CELL_DIM * CELL_DIM;
    static int seen[DIGITS];
    memset(seen, DIGITS, 0);
    for (int i = block_r; i < block_r + CELL_DIM; ++i) {
        for (int j = block_c; j < block_c + CELL_DIM; ++j) {
            digit_t d = grid[i * DIGITS + j] - 1;
            if (seen[d])
                return 0;
            seen[d] = 1;
        }
    }
    return 1;
}

/* T if the row is valid, F otherwise */
int checkrow(digit_t* grid, int r)
{
    static int seen[DIGITS];
    memset(seen, DIGITS, 0);
    for (int c = 0; c < DIGITS; ++c) {
        digit_t d = grid[r * DIGITS + c] - 1;
        if (seen[d])
            return 0;
        seen[d] = 1;
    }
    return 1;
}

/* T if the column is valid, F otherwise */
int checkcol(digit_t* grid, int c)
{
    static int seen[DIGITS];
    memset(seen, DIGITS, 0);
    for (int r = 0; r < DIGITS; ++r) {
        digit_t d = grid[r * DIGITS + c] - 1;
        if (seen[d])
            return 0;
        seen[d] = 1;
    }
    return 1;
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
    printf("%s\n", (checkcell(grid, 1, 1) ? "true" : "false"));
    free((void*)grid);
}
