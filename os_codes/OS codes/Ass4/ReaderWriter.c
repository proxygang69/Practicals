#include <stdio.h>      // Include standard input-output library for printf
#include <stdlib.h>     // Include standard library for memory allocation
#include <pthread.h>    // Include pthread library for threading
#include <semaphore.h>   // Include semaphore library for synchronization
#include <unistd.h>     // Include unistd for sleep function

#define num_readers 5   // Define the number of reader threads
#define num_writers 5   // Define the number of writer threads

sem_t read_mutex;      // Declare semaphore for controlling access to read_count
sem_t write_mutex;     // Declare semaphore for controlling access to writing
int read_count = 0;    // Initialize read_count to keep track of active readers

// Function executed by reader threads
void* reader(void* arg) {
    int id = *((int*)arg); // Retrieve the reader's ID from the passed argument
    free(arg);              // Free the allocated memory for the ID

    while(1) { // Infinite loop for the reader's operation
        sem_wait(&read_mutex); // Lock the read_mutex to safely modify read_count
        read_count++;          // Increment the number of readers
        if (read_count == 1) { // If this is the first reader
            sem_wait(&write_mutex); // Lock the write_mutex to block writers
        }
        sem_post(&read_mutex); // Unlock read_mutex after updating read_count

        printf("Reader %d is reading\n", id); // Indicate the reader is reading
        sleep(rand() % 3); // Simulate reading time with a random sleep

        sem_wait(&read_mutex); // Lock the read_mutex to update read_count
        read_count--;          // Decrement the number of readers
        if (read_count == 0) { // If this was the last reader
            sem_post(&write_mutex); // Unlock the write_mutex to allow writers
        }
        sem_post(&read_mutex); // Unlock read_mutex after updating read_count
        sleep(rand() % 3); // Simulate time before the next read operation
    }
    return NULL; // Return NULL when the function completes
}

// Function executed by writer threads
void* writer(void* arg) {
    int id = *((int*)arg); // Retrieve the writer's ID from the passed argument
    free(arg);              // Free the allocated memory for the ID

    while(1) { // Infinite loop for the writer's operation
        sem_wait(&write_mutex); // Lock the write_mutex to gain exclusive access

        printf("Writer %d is writing\n", id); // Indicate the writer is writing
        sleep(rand() % 3); // Simulate writing time with a random sleep
        printf("Writer %d has done writing\n", id); // Indicate writing is complete

        sem_post(&write_mutex); // Unlock the write_mutex to allow other writers
        sleep(rand() % 3); // Simulate time before the next write operation
    }
    return NULL; // Return NULL when the function completes
}

int main() {
    pthread_t readers[num_readers], writers[num_writers]; // Create thread arrays

    sem_init(&read_mutex, 0, 1); // Initialize read_mutex semaphore with value 1
    sem_init(&write_mutex, 0, 1); // Initialize write_mutex semaphore with value 1

    // Create reader threads
    for(int i = 0; i < num_readers; i++) {
        int* id = (int*)malloc(sizeof(int)); // Allocate memory for reader ID
        *id = i + 1; // Assign a unique ID to the reader
        pthread_create(&readers[i], NULL, reader, id); // Create the reader thread
    }

    // Create writer threads
    for(int i = 0; i < num_writers; i++) {
        int* id = (int*)malloc(sizeof(int)); // Allocate memory for writer ID
        *id = i + 1; // Assign a unique ID to the writer
        pthread_create(&writers[i], NULL, writer, id); // Create the writer thread
    }

    // Wait for all reader threads to complete
    for(int i = 0; i < num_readers; i++) {
        pthread_join(readers[i], NULL); // Join the reader threads
    }
    
    // Wait for all writer threads to complete
    for(int i = 0; i < num_writers; i++) {
        pthread_join(writers[i], NULL); // Join the writer threads
    }

    sem_destroy(&write_mutex); // Destroy the write_mutex semaphore
    sem_destroy(&read_mutex); // Destroy the read_mutex semaphore

    return 0; // Return 0 to indicate successful completion
}
