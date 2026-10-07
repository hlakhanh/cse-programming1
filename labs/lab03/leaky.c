// Lab 3 — Valgrind exercise
// The program prints results that "look correct" but has 4 memory bugs.
//   gcc -Wall -g leaky.c -o leaky
//   valgrind --leak-check=full --track-origins=yes ./leaky
// Fix all the bugs until valgrind reports: 0 errors, no leaks.
//
// Record the bugs you find:
//   Bug 1: line 19, valgrind reports invalid write of size 1 copy_string (leaky.c:19), fix: add 1 to malloc and add null terminator;
//   Bug 2: line 41, valgrind reports conditional jump or move depends on uninitialised value(s) (leaky.c:41), fix: start i from 0;
//   Bug 3: line 18, valgrind reports address 0x4a784d4 is 4 bytes inside a block of size 20 free (leaky.c:42), fix: move free(squares) to the end;
//   Bug 4: line 25, valgrind reports 4 bytes in 1 blocks are definitely lost copy_string (leaky.c:18), fix: free(name) at the end;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a copy of the string on the heap
char *copy_string(const char *s) {
    char *copy = malloc(strlen(s) + 1);
    strcpy(copy, s); copy[strlen(s)] = '\0';
    return copy;
}

// Create an array of n elements: element i equals i * i
int *make_squares(int n) {
    int *a = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        a[i] = i * i;
    return a;
}

int main() {
    char *name = copy_string("Programming 1");
    printf("name = %s\n", name);
    free(name);
    int *squares = make_squares(5);
    int sum = 0;
    for (int i = 0; i < 5; i++){
        sum += squares[i];
    }
    if (sum > 0)
        printf("sum of squares = %d\n", sum);
    printf("first square = %d\n", squares[1]);
    free(squares);
    return 0;
}
