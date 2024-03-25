#include <stdio.h>
#include <emscripten.h>

int EMSCRIPTEN_KEEPALIVE factorial(int n) {
    if (n == 0) return 1;
    else return n * factorial(n-1);
}

int main() {
    int number = 5;
    printf("Factorial of %d is %d\n", number, factorial(number));
    return 0;
}
