#include <stdio.h>      // Standard I/O library for printf and fgets
#include <stdlib.h>     // Standard library for general functions
#include <string.h>     // String manipulation functions
#include <sys/ipc.h>    // Inter-process communication (IPC) definitions
#include <sys/shm.h>    // Shared memory functions

#define SHM_SIZE 1024   // Size of the shared memory segment

int main() {
    // Generate a unique key for the shared memory segment
    key_t key = ftok("server.c", 65);
    
    // Get the shared memory segment
    int shmid = shmget(key, SHM_SIZE, 0666);
    
    // Attach to the shared memory segment
    char *str = (char *)shmat(shmid, NULL, 0);

    // Prompt the user to enter a message
    printf("Client: Enter a message: ");
    
    // Read the message into shared memory
    fgets(str, SHM_SIZE, stdin);

    // Optionally, clear the newline character from the input
    str[strcspn(str, "\n")] = '\0'; 

    // Detach from the shared memory
    shmdt(str);

    return 0; // Exit the program successfully
}
