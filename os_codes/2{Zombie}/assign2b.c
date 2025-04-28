#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i){
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if(l < n && arr[l] > arr[largest]){
        largest = l;
    }
    if(r < n && arr[r] > arr[largest]){
        largest = r;
    }

    if(largest != i){
        swap(&arr[largest], &arr[i]);
        heapify(arr,n,largest);
    }
}

void heapSort(int arr[], int n){
    for(int i = n/2-1; i >=0; i--){
        heapify(arr,n,i);
    }

    for(int i = n-1; i >0; i--){
        swap(&arr[0], &arr[i]);
        heapify(arr,n,0);
    }
}

void arrayPrint(int arr[], int n){
    printf("Sorted array : \n");
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(){
    int n;
    printf("Enter number of elements in the array: ");
    scanf("%d", &n);

    int arr[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }

    heapSort(arr,n);

    //preparing the arguments for the execve system call 
    // create array of strings arguments that can be passed to the execve call 
    // array - path to child.c program, each element of sorted array converted into string, a NULL pointer req by execve to signify end of arguments list
    
    
    char* args[n+2];  // declares an array of char *(string pointers) called args
    // size of args = n+2  -> n is no of sorted elements, +1 for program name("./child", which execve expects as first argument)
    // +1 for NULL pointer which tells execve where arguments list end
    args[0] = "./child";   // will be used by execve to locate and run child

    //converts each integer to string
    for(int i = 0; i < n; i++){
        args[i+1] = malloc(12);  // i+1 because it skips over the program name alre4ady set in args[0]
        // malloc allocates 12 bytes of memory to each integer's string representation
        sprintf(args[i+1], "%d", arr[i]);  // sprintf - string print. Instead of printing on console, it prints output on char buffer which are specified in sprintf
        // it formats arr[i] as decimal string and stores it in args[i+1]
    }

    args[n+1] = NULL;  // execve requires the argument list to be NULL. execve requires the argument list to be NULL-terminated. 
    // This NULL pointer signals the end of the arguments to execve, so it knows not to read beyond this point.

    pid_t pid = fork();

    if(pid < 0){
        printf("Fork Failed\n");
        return 1;
    }
    else if(pid == 0){
        printf("\nChild process is %d, and parent process is %d\n", getpid(), getppid());
        arrayPrint(arr,n);
        printf("\nChild process started \n");
        
        sleep(1);
        execve(args[0], args, NULL);
        perror("execve failed\n"); // if execve fails, print error
        exit(1);
    }
    else{
        wait(NULL);
        printf("Parent Process finished\n");

        //free allocated memory for arguments
        //free is used to release this memory back to the system to prevent memory leaks, as dynamically allocated memory persists beyond the scope of the function unless freed.
        for(int i = 1; i < n; i++){
            if(args[i] != NULL){
                free(args[i]);
            }
        }
    }

    return 0;
}