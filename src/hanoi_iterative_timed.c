#include <stdio.h>
#include <windows.h>

typedef struct {
    int items[64];
    int top;
} Stack;

void push(Stack *s, int value) {
    s->items[++s->top] = value;
}

int pop(Stack *s) {
    return (s->top == -1) ? -1 : s->items[s->top--];
}

int is_empty(Stack *s) {
    return s->top == -1;
}

// volatile prevents optimization
volatile unsigned long long moves = 0;

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

    moves++; // anti-optimisation
}

void hanoi_iterative(int n) {
    Stack A = {.top = -1};
    Stack B = {.top = -1};
    Stack C = {.top = -1};

    int total_moves = (1 << n) - 1; // 2^n - 1

    for (int i = n; i >= 1; i--)
        push(&A, i);

    int p1 = 0, p2 = 1, p3 = 2;
    Stack* poles[3] = {&A, &B, &C};

    if (n % 2 == 0) {
        Stack* temp = poles[1];
        poles[1] = poles[2];
        poles[2] = temp;
    }

    for (int i = 1; i <= total_moves; i++) {
        if (i % 3 == 1)
            move_between(poles[p1], poles[p3]);
        else if (i % 3 == 2)
            move_between(poles[p1], poles[p2]);
        else
            move_between(poles[p2], poles[p3]);
    }
}

int main() {
    int n;
    LARGE_INTEGER start, end, freq;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    hanoi_iterative(n);

    QueryPerformanceCounter(&end);

    double elapsed = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;

    printf("Execution time = %.9f seconds\n", elapsed);
    return 0;
}
