#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Same program, but it prints where each variable lives,
// so you can see that pin[2] is the same address as access.
void login(int64_t n) {
    int64_t access = 0;
    int64_t pin[2];

    printf("access is at    %p\n", (void *)&access);
    printf("pin[0] is at    %p\n", (void *)&pin[0]);
    printf("pin[1] is at    %p\n", (void *)&pin[1]);
    printf("pin[2] would be %p\n", (void *)&pin[2]);

    for (int64_t i = 0; i < n; i++)
        pin[i] = 9;

    printf("access = %ld\n", (long)access);
    if (access != 0) printf("Access granted\n");
    else printf("Access denied\n");
}

int main(int argc, char **argv) {
    int64_t n = (argc > 1) ? atoll(argv[1]) : 3;
    login(n);
    return 0;
}
