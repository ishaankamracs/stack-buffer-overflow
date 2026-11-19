#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// login trusts its caller about how many PIN digits to copy.
// pin only has room for 2, but nothing checks that i stays below 2.
void login(int64_t n) {
    int64_t access = 0;
    int64_t pin[2];

    for (int64_t i = 0; i < n; i++)
        pin[i] = 9;

    if (access != 0) printf("Access granted\n");
    else printf("Access denied\n");
}

int main(int argc, char **argv) {
    int64_t n = (argc > 1) ? atoll(argv[1]) : 3;
    login(n);
    return 0;
}
