#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct {
    int items[64];
    int top;
} Stack;

void push(Stack *s, int value) {
    s->items[++s->top] = value;
}

int pop(Stack *s) {
    return s->top == -1 ? -1 : s->items[s->top--];
}

int is_empty(Stack *s) {
    return s->top == -1;
}

void move_between(Stack *src, Stack *dest) {
    int srcTop = is_empty(src) ? -1 : pop(src);
    int destTop = is_empty(dest) ? -1 : pop(dest);

    if (srcTop == -1) {
        push(src, destTop);
    }
    else if (destTop == -1) {
        push(dest, srcTop);
    }
    else if (srcTop > destTop) {
        push(src, srcTop);
        push(src, destTop);
    }
    else {
        push(dest, destTop);
        push(dest, srcTop);
    }
}

void hanoi_iterative(int n) {
    Stack A = {.top = -1};
    Stack B = {.top = -1};
    Stack C = {.top = -1};

    int total_moves = pow(2, n) - 1;

    for (int i = n; i >= 1; i--)
        push(&A, i);

    char poleA = 'A', poleB = 'B', poleC = 'C';

    if (n % 2 == 0) {
        char temp = poleC;
        poleC = poleB;
        poleB = temp;
    }

    for (int i = 1; i <= total_moves; i++) {
        if (i % 3 == 1)
            move_between(&A, &C);
        else if (i % 3 == 2)
            move_between(&A, &B);
        else
            move_between(&B, &C);
    }
}

int main() {
    int n;
    clock_t start, end;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    start = clock();
    hanoi_iterative(n);
    end = clock();

    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time = %.6f seconds\n", elapsed);

    return 0;
}
