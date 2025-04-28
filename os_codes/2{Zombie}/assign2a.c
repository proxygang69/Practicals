#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//pointers are used to swap the actual original values in the caller's variables
// if we don't use pointers - Values from a and b are copied to new local varoables, and the swapping would happen between these variables 
// and not in the original values that we need
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}


//MAX HEAP

void heapify(int arr[], int n, int i){
    int largest = i;
    int l = 2*i + 1;  // left child of ith node
    int r = 2*i + 2;  // right child of ith node

    // if left child is greater than the ith node
    if(l < n && arr[l] > arr[largest]){
        largest = l;
    }

    // if right child is greater than the ith node
    if(r < n && arr[r] > arr[largest]){
        largest = r;
    }

    if(largest != i){
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// TIME COMPLEXITY - O(n log n)
void heapSort(int arr[], int n){
    // start from last non-leaf node and move upwards to the root, calling heapify on each node.
    // This builds a max heap structure for the entire array. 
    for(int i = n/2 - 1; i >= 0; i--){
        heapify(arr, n, i);
    }

    //repeatedly move the largest element of the array to the end of the array
    //after each swap, reduce the size of the heap( taking i as the heap size), and call heapify() on the root and restore the heap property 
    //sorting the array in ascending order
    for(int i = n-1; i > 0; i--){
        swap(&arr[0], &arr[i]);
        heapify(arr,i,0);
    }
}

void printArray(int arr[], int size){
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void zombie(){
    pid_t pid = fork();

    if(pid < 0){  // failed
        perror("fork");
        exit(1);
    }
    else if(pid == 0){  // child process
        printf("Child process %d started, parent process is %d \n\n",getpid(), getppid());
        exit(0);
    }
    else{  // parent process
        printf("Parent process %d created child process %d \n\n", getpid(), pid);
        sleep(7);
        
        // ps dispplays information about currently running processes
        // -e  -> tells 'ps' to show all processes
        // -o -> specify output format
        // pid, ppid, state, cmd  -  process ID, parent process id, current state of process, command that started the process
        // use args instead of cmd if it is not running
        // grep | defunct -> pipes output pf ps to grep which filters output to show only lines containing the word 'defunct'
        // in UNIX system, defunct process is a zombie process
        system("ps -eo pid,ppid,state,args | grep defunct");

        printf("Parent process %d is terminating \n", getpid());
        
    }
    sleep(5);

    /*
    OUTPUT ->
    Parent process 92746 created child process 92749 

     Child process 92749 started, parent process is 92746 

     pid   ppid  state  command 
     92749 92746 Z+   <defunct>
     92755 92746 S+   sh -c ps -eo pid,ppid,state,args | grep defunct
     92757 92755 R+   grep defunct
     Parent process 92746 is terminating 
    */

    // Z+ -> process is a zombie process
    // S+ -> process is sleeping 
    // R+ -> process is running
    // +: The process is in the foreground group.

    // 92749 - PID of child process that has terminated but still in system as zombie
    // 92746 - PPID of parent process that created the child process
    // 92755 - PID of shell process that is running the 'ps' command and 'grep'
    // 92746 - indicates that this shell process(upar wala) is child of the same parent process as the zombie
    // 92757 - PID of the grep command
    // 92755 - grep command is child of the shell process
}

void orphan(){
    pid_t pid = fork();

    if(pid < 0){  //failed
        perror("fork");
        exit(1);
    }
    else if(pid == 0){  // child process
        sleep(5);
        printf("Child process %d started. Parent process is %d. \n", getpid(), getppid());
        system("ps -eo pid,ppid,state,args | grep a.out");
        printf("Child process %d finished, now adopted by init (PID: %d).\n", getpid(), getppid());
    }
    else{  // parent process
        printf("Parent process %d created child process %d. \n",getpid(),pid);

        // grep a.out -> filters the output, displaying the line that contains a.out
        // filters to show only processes related to currently running program
        // This is useful to check if your program’s processes are still active, and it helps identify the parent and child processes or check if they are in a zombie or orphan state.
        // "a.out" is the default name for compiled C programs if you use gcc without specifying an output name, so here, it refers to any instance of your program assign2 that is running.
        system("ps -eo pid,ppid,state,args | grep a.out");
        printf("Parent process %d is terminating. \n", getpid());
        exit(0);  // terminating parent process abruptly, leaving child orphaned
    }
    sleep(3);

    /*
    
    OUTPUT - 
    2
    Parent process 95033 created child process 95041. 
    pid   ppid  state cmds
    95042 95033 S+   sh -c ps -eo pid,ppid,state,args | grep a.out
    95044 95042 R+   grep a.out
    Parent process 95033 is terminating. 
    ➜  OSL working Child process 95041 started. Parent process is 1. 
    95059 95041 S    sh -c ps -eo pid,ppid,state,args | grep a.out
    95061 95059 R    grep a.out
    Child process 95041 finished, now adopted by init (PID: 1).

    */
   // 95042 - PID of the shell process started by system(), whose parent is 95033 which is also the parent for child prcess
   // 95044 - PID for grep cmd, whose parent is the shell process
   // 95033 wala parent process is terminated
   // child 95041 is then adopted by init 
   // system("ps -eo pid,ppid,state,args | grep a.out"); -> This command now shows the child process 94636 with its new parent as 1 and the associated shell and grep processes

}

void waitSort(int arr[], int n){
    pid_t pid = fork();

    if(pid < 0){
        perror("fail");
        exit(1);
    }
    else if(pid == 0){
        //child process
        printf("---Child process sorting with heap sort---\n");
        heapSort(arr, n);
        printf("Child process sorted array : ");
        printArray(arr,n);
        printf("Child process %d finished. \n", getpid());
        exit(0);
    }
    else{
        //parent process
        printf("---Parent process sorting with heap sort---\n");
        heapSort(arr,n);
        printf("Parent process sorted array : ");
        printArray(arr,n);
        printf("Array sorted and wait called. \n");

        // wait for child process to finish
        int status;
        pid_t child_pid = wait(&status);

        if(child_pid < 0){
            perror("Failed");
            exit(0);
        }
        else{
            printf("Parent process %d waited for child process %d", getpid(), child_pid);
        }
    }
}

int main(){
    int n,c;

    printf("Enter number of integers to sort: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the integers: ");
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }

    printf("Enter choice: \n1. Zombie\n2. Orphan\n3. Using wait and sort\n");
    scanf("%d", &c);
    switch(c){
        case 1:
            zombie();
            break;

        case 2:
            orphan();
            break;

        case 3:
            waitSort(arr,n);
            break;

        default:
            printf("Invalid choice\n");
            break;
    }

    return 0;

}