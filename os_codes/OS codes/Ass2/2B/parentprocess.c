#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring> 

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // swap arr[j] and arr[j+1]
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    bubbleSort(arr, n);

    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed.\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        char *args[20];  // Assuming max arguments
        char arr_str[10];
        int i;

        printf("Child process displaying sorted array in reverse order:\n");
        for (i = 0; i < n; i++) {
            sprintf(arr_str, "%d", arr[n-i-1]);
            args[i] = strdup(arr_str);
        }
        args[i] = NULL;

      execve("./childprocess", args, NULL);


        // execve only returns if an error occurs
        perror("execve");
        return 1;
    } else {
        // Parent process
        wait(NULL);
        printf("Parent process completed.\n");
    }

    free(arr);
    return 0;
}

