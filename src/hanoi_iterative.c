#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int items[64];
    int top;
} Stack;

// Push element
void push(Stack *s, int value) {
    s->items[++s->top] = value;
}

// Pop element
int pop(Stack *s) {
    if (s->top == -1) return -1;
    return s->items[s->top--];
}

// Check empty
int is_empty(Stack *s) {
    return (s->top == -1);
}

// Move between two poles
void move_between(Stack *src, Stack *dest, char s, char d) {

    int pole1Top = is_empty(src) ? -1 : pop(src);
    int pole2Top = is_empty(dest) ? -1 : pop(dest);

    // If src is empty → move from dest to src
    if (pole1Top == -1) {
        push(src, pole2Top);
        printf("Move disk %d from %c to %c\n", pole2Top, d, s);
    }
    // If dest is empty → move from src to dest
    else if (pole2Top == -1) {
        push(dest, pole1Top);
        printf("Move disk %d from %c to %c\n", pole1Top, s, d);
    }
    // If top of src > top of dest → return them correctly
    else if (pole1Top > pole2Top) {
        push(src, pole1Top);
        push(src, pole2Top);
        printf("Move disk %d from %c to %c\n", pole2Top, d, s);
    }
    // If top of dest > top of src
    else {
        push(dest, pole2Top);
        push(dest, pole1Top);
        printf("Move disk %d from %c to %c\n", pole1Top, s, d);
    }
}

void hanoi_iterative(int n) {
    Stack A = {.top = -1};
    Stack B = {.top = -1};
    Stack C = {.top = -1};

    char s = 'A', a = 'B', d = 'C';

    // If number of disks is even → swap destination and auxiliary
    if (n % 2 == 0) {
        char temp = d;
        d = a;
        a = temp;
    }

    int i;
    int total_moves = pow(2, n) - 1;

    // Load all disks on source pole
    for (i = n; i >= 1; i--)
        push(&A, i);

    for (i = 1; i <= total_moves; i++) {

        if (i % 3 == 1)
            move_between(&A, &C, s, d);
        else if (i % 3 == 2)
            move_between(&A, &B, s, a);
        else
            move_between(&B, &C, a, d);
    }
}

int main() {
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    printf("\n--- Iterative Tower of Hanoi ---\n\n");
    hanoi_iterative(n);

    return 0;
}
