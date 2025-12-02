#include <stdio.h>
#include <time.h>   // <-- Important for clock_gettime()

void hanoi_recursive(int n, char from, char to, char aux) {
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", from, to);
        return;
    }

    hanoi_recursive(n - 1, from, aux, to);
    printf("Move disk %d from %c to %c\n", n, from, to);
    hanoi_recursive(n - 1, aux, to, from);
}

int main() {
    int n;
    struct timespec start, end;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of disks must be positive.\n");
        return 1;
    }

    // Start timer
    clock_gettime(CLOCK_MONOTONIC, &start);

    hanoi_recursive(n, 'A', 'C', 'B');

    // End timer
    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed =
        (end.tv_sec - start.tv_sec) +
        (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Execution time = %.9f seconds\n", elapsed);

    return 0;
}
