#include <stdio.h>       // Include standard I/O library for printing
#include <stdlib.h>      // Include standard library for memory allocation
#include <pthread.h>     // Include pthread library for threading
#include <semaphore.h>    // Include semaphore library for synchronization
#include <unistd.h>      // Include unistd.h for sleep function

#define BUFFER_SIZE 10   // Define the size of the buffer

int buffer[BUFFER_SIZE]; // Create a buffer array of defined size

int in = 0;  // Index for the next producer position
int out = 0; // Index for the next consumer position

sem_t empty; // Semaphore to count empty slots in the buffer
sem_t full;  // Semaphore to count filled slots in the buffer

pthread_mutex_t mutex; // Mutex for protecting critical section

// Function to display the current state of the buffer
void displaybuffer() {
    printf("Current Buffer - [");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (i == in) {
            printf("|"); // Mark the 'in' index
        }
        if (buffer[i] != -1) {
            printf("%d", buffer[i]); // Print the item in the buffer
        } else {
            printf("_"); // Print underscore for empty slots
        }
    }
    printf("]\n"); // Close the buffer display
}

// Producer thread function
void* producer(void* arg) {
    int id = *((int*)arg); // Get producer ID from argument
    free(arg); // Free the allocated memory for ID
    while (1) { // Infinite loop for continuous production
        int item = rand() % 10; // Generate a random item
        sem_wait(&empty); // Wait for an empty slot in the buffer
        pthread_mutex_lock(&mutex); // Lock the mutex

        buffer[in] = item; // Add item to the buffer
        printf("Producer %d produced item %d\n", id, item); // Log production
        in = (in + 1) % BUFFER_SIZE; // Update the 'in' index circularly

        displaybuffer(); // Display current buffer state

        pthread_mutex_unlock(&mutex); // Unlock the mutex
        sem_post(&full); // Signal that a new item is available

        sleep(rand() % 7); // Sleep for a random time (0-6 seconds)
    }
    return NULL; // Return NULL when done (not reachable in this case)
}

// Consumer thread function
void* consumer(void* arg) {
    int id = *((int*)arg); // Get consumer ID from argument
    free(arg); // Free the allocated memory for ID

    while (1) { // Infinite loop for continuous consumption
        sem_wait(&full); // Wait for a filled slot in the buffer
        pthread_mutex_lock(&mutex); // Lock the mutex

        int item = buffer[out]; // Get the item from the buffer
        printf("Consumer %d has consumed item %d\n", id, item); // Log consumption
        buffer[out] = -1; // Mark the slot as empty
        out = (out + 1) % BUFFER_SIZE; // Update the 'out' index circularly

        displaybuffer(); // Display current buffer state
        pthread_mutex_unlock(&mutex); // Unlock the mutex
        sem_post(&empty); // Signal that a slot has become empty
        sleep(rand() % 7); // Sleep for a random time (0-6 seconds)
    }
    return NULL; // Return NULL when done (not reachable in this case)
}

// Main function
int main() {
    int num_producers, num_consumers; // Variables for number of producers and consumers

    // User input for number of producers
    printf("Enter the number of producers: ");
    scanf("%d", &num_producers);
    // User input for number of consumers
    printf("Enter the number of consumers: ");
    scanf("%d", &num_consumers);

    pthread_t producers[num_producers], consumers[num_consumers]; // Thread identifiers

    sem_init(&empty, 0, BUFFER_SIZE); // Initialize empty semaphore with buffer size
    sem_init(&full, 0, 0); // Initialize full semaphore with 0 (no items)
    pthread_mutex_init(&mutex, NULL); // Initialize the mutex

    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = -1; // Initialize the buffer to indicate all slots are empty
    }
    // Create producer threads
    for (int i = 0; i < num_producers; i++) {
        int* id = (int*)malloc(sizeof(int)); // Allocate memory for producer ID
        *id = i + 1; // Assign ID
        pthread_create(&producers[i], NULL, producer, id); // Create producer thread
        sleep(1); // Optional sleep to stagger thread creation
    }
    // Create consumer threads
    for (int i = 0; i < num_consumers; i++) {
        int* id = (int*)malloc(sizeof(int)); // Allocate memory for consumer ID
        *id = i + 1; // Assign ID
        pthread_create(&consumers[i], NULL, consumer, id); // Create consumer thread
        sleep(1); // Optional sleep to stagger thread creation
    }
    // Wait for all producer threads to finish
    for (int i = 0; i < num_producers; i++) {
        pthread_join(producers[i], NULL);
    }    
    // Wait for all consumer threads to finish
    for (int i = 0; i < num_consumers; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Clean up resources
    sem_destroy(&empty); // Destroy empty semaphore
    sem_destroy(&full); // Destroy full semaphore
    pthread_mutex_destroy(&mutex); // Destroy the mutex

    return 0; // Return success
}
