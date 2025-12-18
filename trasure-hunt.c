#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 7
#define MOVES 20

int askMathQuestion() {
    int a, b, ans, userAns;
    int op = rand() % 4;

    a = rand() % 10 + 1;
    b = rand() % 10 + 1;

    switch (op) {
        case 0:
            printf("Solve: %d + %d = ", a, b);
            ans = a + b;
            break;

        case 1:
            printf("Solve: %d - %d = ", a, b);
            ans = a - b;
            break;

        case 2:
            printf("Solve: %d * %d = ", a, b);
            ans = a * b;
            break;

        case 3:
            a = a * b;   // ensure clean division
            printf("Solve: %d / %d = ", a, b);
            ans = a / b;
            break;
    }

    scanf("%d", &userAns);

    if (userAns == ans) {
        printf("Correct answer. You earned 5 extra moves.\n");
        return 1;
    } else {
        printf("Wrong answer. No extra moves.\n");
        return 0;
    }
}

int main() {
    int grid[SIZE][SIZE] = {0};
    int visited[SIZE][SIZE] = {0};
    int pr, pc, tr, tc;
    int moves = MOVES;
    int totalMoves = MOVES;
    int bonusUsed = 0;
    int r, c;

    srand(time(NULL));

    // Place treasure
    tr = rand() % SIZE;
    tc = rand() % SIZE;
    grid[tr][tc] = 1;

    // Place player
    do {
        pr = rand() % SIZE;
        pc = rand() % SIZE;
    } while (pr == tr && pc == tc);

    visited[pr][pc] = 1;

    printf("=== 7x7 TREASURE HUNT GAME ===\n");
    printf("Controls: w = up, s = down, a = left, d = right\n");
    printf("Initial moves: %d\n", MOVES);

    while (moves > 0) {
        printf("\nMoves left: %d\n\n", moves);

        // Display grid
        for (r = 0; r < SIZE; r++) {
            for (c = 0; c < SIZE; c++) {
                if (r == pr && c == pc)
                    printf(" P ");
                else if (!visited[r][c])
                    printf(" ? ");
                else
                    printf(" . ");
            }
            printf("\n");
        }

        // Win check
        if (pr == tr && pc == tc) {
            printf("\nYou found the treasure.\n");
            printf("Total moves used: %d\n", totalMoves - moves);
            return 0;
        }

        // Hints
        printf("\nHint: Treasure is ");
        if (tr < pr) printf("north ");
        else if (tr > pr) printf("south ");
        if (tc < pc) printf("west");
        else if (tc > pc) printf("east");
        printf("\n");

        printf("Distance: %d\n", abs(pr - tr) + abs(pc - tc));

        // One-time math bonus
        if (!bonusUsed) {
            char choice;
            printf("\nTry a math question for +5 moves? (y/n): ");
            scanf(" %c", &choice);

            if (choice == 'y' || choice == 'Y') {
                bonusUsed = 1;
                if (askMathQuestion()) {
                    moves += 5;
                    totalMoves += 5;
                }
            }
        }

        // Player movement
        char move;
        printf("\nEnter move (w/a/s/d): ");
        scanf(" %c", &move);

        int nr = pr, nc = pc;

        if (move == 'w') nr--;
        else if (move == 's') nr++;
        else if (move == 'a') nc--;
        else if (move == 'd') nc++;
        else {
            printf("Invalid input\n");
            continue;
        }

        // Boundary check
        if (nr < 0 || nr >= SIZE || nc < 0 || nc >= SIZE) {
            printf("Cannot move outside the grid\n");
            continue;
        }

        pr = nr;
        pc = nc;
        visited[pr][pc] = 1;
        moves--;
    }

    printf("\nOut of moves. You lost.\n");
    printf("Treasure was at (%d, %d)\n", tr, tc);
    printf("Total moves used: %d\n", totalMoves);

    return 0;
}

