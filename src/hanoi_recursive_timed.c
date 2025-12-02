#include <stdio.h>
#include <windows.h>   // IMPORTANT for high-resolution timer

void hanoi_recursive(int n, char from, char to, char aux) {
    if (n == 1) {
        // No printing to avoid slowing down timing
        return;
    }

    hanoi_recursive(n - 1, from, aux, to);
    // Main move (no printf for timing test)
    hanoi_recursive(n - 1, aux, to, from);
}

int main() {
    int n;

    LARGE_INTEGER start, end, freq;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of disks must be positive.\n");
        return 1;
    }

    // High resolution timer frequency
    QueryPerformanceFrequency(&freq);

    // Start timer
    QueryPerformanceCounter(&start);

    // Run algorithm
    hanoi_recursive(n, 'A', 'C', 'B');

    // End timer
    QueryPerformanceCounter(&end);

    // Compute elapsed time in seconds
    double elapsed = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;

    printf("Execution time = %.9f seconds\n", elapsed);

    return 0;
}
