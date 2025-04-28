#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int n = argc -1;  // represents the number of integers passed to program as arguments
    // argv[0] is the program name so we exclude it, hence n-1
    int arr[n];  // to store integer values from the command-line arguments

    for(int i = 0; i < n; i++){
        arr[i] = atoi(argv[i+1]);
        // argv[i+1] accesses each argument starting from argv[1]
        // atoi -> converts each command line argument to an integer and assigns it to arr[i]
    }

    printf("\nArray in Reverse Order: \n");
    for(int i = n-1; i >= 0; i--){
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}