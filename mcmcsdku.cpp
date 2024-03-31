#include <bits/stdc++.h>

#define DIGITS 9
#define BLOCK_DIM 3

using namespace std;

typedef unsigned char digit_t;
typedef array<digit_t, DIGITS> row_t;
typedef array<row_t, DIGITS> grid_t;

void pprintgrid(digit_t* grid)
{
    int printwidth = 1;
    int maxval = 0;
    for (int i = 0; i < DIGITS * DIGITS; ++i) {
        if (grid[i] > maxval)
            maxval = grid[i];
    }
    while (maxval > 9) {
        printwidth += 1;
        maxval /= 10;
    }

    for (int i = 0; i < DIGITS; ++i) {
        if (i > 0 && i % BLOCK_DIM == 0) {
            for (int j = 0; j < BLOCK_DIM; ++j) {
                if (j > 0)
                    printf(" + ");
                int dashes = BLOCK_DIM * printwidth + BLOCK_DIM - 1;
                while (dashes--)
                    printf("-");
            }
            printf("\n");
        }
        for (int j = 0; j < DIGITS; ++j) {
            if (j > 0 && j % BLOCK_DIM == 0)
                printf("| ");
            int numwidth = printf("%u", grid[i * DIGITS + j]);
            while (numwidth++ < printwidth)
                printf(" ");
            printf(" ");
        }
        printf("\n");
    }
}

int l1dist(array<digit_t, DIGITS>& x) {
    static const array<digit_t, DIGITS> y = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int dist = 0;
    sort(x.begin(), x.end());
    for (int i = 0; i < x.size(); ++i)
        dist += abs(x[i] - y[i]);
    return dist;
}

int r(digit_t* grid, int i) {
    static array<digit_t, DIGITS> x;
    for (int j = 0; j < DIGITS; ++j) {
        x[j] = grid[i * DIGITS + j];
    }
    return l1dist(x);
}

int c(digit_t* grid, int j) {
    static array<digit_t, DIGITS> x;
    for (int i = 0; i < DIGITS; ++i) {
        x[i] = grid[i * DIGITS + j];
    }
    return l1dist(x);
}

int Q(digit_t* grid) {
    int q = 0;
    for (int i = 0; i < DIGITS; ++i) {
        q += (r(grid, i) + c(grid, i));
    }
    return q;
}

pair<int, int> rand_idx_pair(digit_t* grid, const grid_t& block_indices) {
    int block = rand() % DIGITS;
    int idx1 = rand() % DIGITS;
    int idx2;
    do {
        idx2 = rand() % DIGITS;
    } while (idx2 == idx1);
    return {block_indices[block][idx1], block_indices[block][idx2]};
}

int main(int argc, char** argv) {
    srand(time(NULL));
    digit_t grid[DIGITS * DIGITS];

    for (int i = 0; i < DIGITS * DIGITS; ++i) {
        scanf("%hhu ", &grid[i]);
    }

    // Collect groups of block indices
    grid_t block_indices;
    for (int i = 0; i < DIGITS; ++i) {
        int block_r = i / BLOCK_DIM * BLOCK_DIM;
        int block_c = i % BLOCK_DIM * BLOCK_DIM;
        for (int j = 0; j < BLOCK_DIM; ++j) {
            for (int k = 0; k < BLOCK_DIM; ++k) {
                int idx = (block_r + j) * DIGITS + (block_c + k);
                block_indices[i][j * BLOCK_DIM +  k] = idx;
            }
        }
    }

    // Fill in missing grid entries
    for (const row_t& row : block_indices) {
        array<bool, DIGITS + 1> seen;
        fill(seen.begin(), seen.end(), false);
        for (const digit_t& idx : row) {
            if (grid[idx] != 0)
                seen[grid[idx]] = true;
        }
        for (const digit_t& idx : row) {
            if (grid[idx] == 0) {
                digit_t d;
                do {
                    d = (rand() % DIGITS) + 1;
                } while (seen[d]);
                seen[d] = true;
                grid[idx] = d;
            }
        }
    }

    pprintgrid(grid);
    printf("\n");

    pair<int, int> idx_pair;
    int qprev = Q(grid);
    long iterations = 0;
    double lambda = (argc > 1 ? atof(argv[1]) : 1.0);
    do {
        idx_pair = rand_idx_pair(grid, block_indices);
        swap(grid[idx_pair.first], grid[idx_pair.second]);
        int qprop  = Q(grid);
        // Probability of rejecting the change
        double pr = 1.0 - min(1.0, exp(-lambda * (qprop - qprev)));
        if (rand() * 1.0 / RAND_MAX <= pr) {
            // Undo the swap
            swap(grid[idx_pair.first], grid[idx_pair.second]);
        }
        qprev = Q(grid);
        iterations += 1;
    } while (qprev != 0);

    printf("Succeeded after %ld iterations!\n", iterations);
    pprintgrid(grid);

    return 0;
}

