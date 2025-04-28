#include <stdio.h>      // Standard I/O library for printf
#include <stdlib.h>     // Standard library for general functions
#include <string.h>     // String manipulation functions
#include <sys/ipc.h>    // Inter-process communication (IPC) definitions
#include <sys/shm.h>    // Shared memory functions
#include <unistd.h>     // Unix standard functions

#define SHM_SIZE 1024   // Size of the shared memory segment

int main() {
    // Generate a unique key for the shared memory segment using ftok
    key_t key = ftok("server.c", 65); 
    
    // Create the shared memory segment
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    
    // Attach to the shared memory segment
    char *str = (char *)shmat(shmid, NULL, 0); 

    // Indicate that the server is waiting for a client message
    printf("Server: Waiting for client message...\n");
    
    // Continuously check for a message from the client
    while (1) {
        // If the message length is greater than 0, it means a message is received
        if (strlen(str) > 0) { 
            printf("Server: Received message: %s\n", str);
            break; // Exit the loop after receiving the message
        }
        sleep(1); // Sleep to prevent busy waiting
    }

    // Detach from the shared memory
    shmdt(str);

    // Cleanup: remove the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);

    return 0; // Exit the program successfully
}
