#include <stdio.h>

// Function to calculate the nth Fibonacci number
int fibonacci(int n) {
    if (n <= 1) {
        return n;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main() {
    int n=100;

    if (n < 0) {
        printf("Please enter a non-negative integer.\n");
    } else {
        int fib = fibonacci(n);
        printf("Fibonacci number at position %d is: %d\n", n, fib);
    }
    return 0;
}