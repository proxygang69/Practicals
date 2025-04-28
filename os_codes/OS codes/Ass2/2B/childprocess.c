#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Child process received and displaying array in reverse order:\n");
    for (int i = 1; argv[i] != NULL; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n");
    return 0;
}

