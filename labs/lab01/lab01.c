// Lab 1 — C Fundamentals
// Compile and run:  gcc -Wall -Wextra lab01.c -o lab01 && ./lab01
// Task: implement the functions marked TODO until all tests PASS.
#include <stdio.h>

// ---------------------------------------------------------------------------
// Simple test harness (no need to modify)
static int passed = 0, total = 0;
#define CHECK(expr)                                 \
    do {                                            \
        total++;                                    \
        if (expr) {                                 \
            passed++;                               \
            printf("  PASS  %s\n", #expr);          \
        } else {                                    \
            printf("  FAIL  %s\n", #expr);          \
        }                                           \
    } while (0)
// ---------------------------------------------------------------------------

// 1.1 Sum of two numbers
int add(int a, int b) {
    return a + b;
}

// 1.2 Sum of the digits of n (n may be negative: sum_digits(-12) = 3)
int sum_digits(int n) {
    if (n < 0) n = -n;
    int sum = 0;
    for (; n > 0; n /= 10) sum += (n % 10);
    return sum; 
}

// 1.3 n! using a loop (0! = 1)
long long factorial(int n) {
    long long fact = 1;
    for (int i = 1; i <= n; i++) fact *= i;
    return fact;
}

// 1.4a Recursive Fibonacci: fib(0) = 0, fib(1) = 1, fib(n) = fib(n-1) + fib(n-2)
long fib_recursive(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fib_recursive(n-2) + fib_recursive(n-1);
}

// 1.4b Iterative Fibonacci
long fib_loop(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    long a = 0;
    long b = 1;
    long temp = 0;
    for (int i = 2; i <= n; i++)
    {
        temp = a + b;
        a = b;
        b = temp;
    }
    
    return temp;
}

// 1.5 Return 1 if n is prime, otherwise 0 (numbers < 2 are not prime)
int is_prime(int n) {
    if (n < 2) return 0;
    for (long i = 2; i * i <= n; i++)
    if (n % i == 0) return 0;
    return 1;
}

// 1.6 Greatest common divisor (Euclid's algorithm): gcd(a, b) = gcd(b, a % b), gcd(a, 0) = a
int gcd(int a, int b) {
    int temp;
    if (a < b){
        temp = a;
        a = b;
        b = temp;
    }
    while (a > b && b != 0)
    {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// 1.7 Leap year
int is_leap_year(int y) {
    return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
}

// 1.8 Number of days in a month. You MUST use switch, grouping cases with the same result.
// Return 0 if month is not in 1..12
int days_in_month(int month, int year) {
    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 2:
        if (is_leap_year(year)) return 29;
        else return 28;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    default:
        return 0;
    }
}

int main() {
    printf("1.1 add\n");
    CHECK(add(2, 3) == 5);
    CHECK(add(-4, 4) == 0);

    printf("1.2 sum_digits\n");
    CHECK(sum_digits(1234) == 10);
    CHECK(sum_digits(0) == 0);
    CHECK(sum_digits(-12) == 3);

    printf("1.3 factorial\n");
    CHECK(factorial(0) == 1);
    CHECK(factorial(5) == 120);
    CHECK(factorial(15) == 1307674368000L);

    printf("1.4 fibonacci\n");
    CHECK(fib_recursive(0) == 0);
    CHECK(fib_recursive(1) == 1);
    CHECK(fib_recursive(20) == 6765);
    CHECK(fib_loop(0) == 0);
    CHECK(fib_loop(20) == 6765);
    CHECK(fib_loop(80) == 23416728348467685L);

    printf("1.5 is_prime\n");
    CHECK(is_prime(2) == 1);
    CHECK(is_prime(97) == 1);
    CHECK(is_prime(1) == 0);
    CHECK(is_prime(91) == 0);
    CHECK(is_prime(-7) == 0);

    printf("1.6 gcd\n");
    CHECK(gcd(12, 18) == 6);
    CHECK(gcd(17, 5) == 1);
    CHECK(gcd(7, 0) == 7);

    printf("1.7 is_leap_year\n");
    CHECK(is_leap_year(2024) == 1);
    CHECK(is_leap_year(2023) == 0);
    CHECK(is_leap_year(1900) == 0);
    CHECK(is_leap_year(2000) == 1);

    printf("1.8 days_in_month\n");
    CHECK(days_in_month(1, 2023) == 31);
    CHECK(days_in_month(4, 2023) == 30);
    CHECK(days_in_month(2, 2023) == 28);
    CHECK(days_in_month(2, 2024) == 29);
    CHECK(days_in_month(13, 2024) == 0);

    printf("\nResult: %d/%d PASS\n", passed, total);
    return passed == total ? 0 : 1;
}
