#include <stdio.h>       // Standard input/output library
#include <stdlib.h>      // Standard library for memory allocation and abs function
#include <stdbool.h>     // Library for boolean type support

#define MAX_TRACKS 200  // Define the maximum number of tracks on the disk

// Function prototypes for the disk scheduling algorithms
void SSTF(int requests[], int n, int head);
void SCAN(int requests[], int n, int head, int direction);
void C_LOOK(int requests[], int n, int head);

int main() {
    int n, head, choice; // Variables for number of requests, head position, and user choice

    // Get the number of requests from the user
    printf("Enter number of requests: "); 
    scanf("%d", &n); 
    
    int requests[n]; // Array to store the disk requests
    printf("Enter the requests (0 to 199):\n"); 
    for (int i = 0; i < n; i++) { 
        scanf("%d", &requests[i]); // Read requests into the array
    }
    
    // Get the initial position of the read/write head
    printf("Enter the initial position of the read/write head (0 to 199): "); 
    scanf("%d", &head); 

    // Infinite loop for the menu to choose scheduling algorithms
    while (1) { 
        printf("\nDisk Scheduling Algorithms Menu:\n"); 
        printf("1. Shortest Seek Time First (SSTF)\n"); 
        printf("2. SCAN\n"); 
        printf("3. C-LOOK\n"); 
        printf("4. Exit\n"); 
        printf("Choose an option (1-4): "); 
        scanf("%d", &choice); // Read user choice

        // Execute the chosen disk scheduling algorithm
        switch (choice) {
            case 1: 
                SSTF(requests, n, head); // Call the SSTF algorithm
                break; 
            case 2: { 
                // Get the direction for SCAN
                printf("Enter direction (1 for up, 0 for down): "); 
                int direction; 
                scanf("%d", &direction); // Read direction
                SCAN(requests, n, head, direction); // Call the SCAN algorithm
                break; 
            }
            case 3: 
                C_LOOK(requests, n, head); // Call the C-LOOK algorithm
                break; 
            case 4: 
                printf("Exiting...\n"); // Exit message
                exit(0); // Terminate the program
            default: 
                printf("Invalid choice! Please try again.\n"); // Handle invalid input
        }
    }

    return 0; // Return 0 to indicate successful termination
}

// Function to implement Shortest Seek Time First (SSTF) algorithm
void SSTF(int requests[], int n, int head) {
    bool visited[n]; // Array to track visited requests
    int total_seek_time = 0; // Variable to keep track of total seek time
    int current_position = head; // Start at the initial head position
    int completed = 0; // Counter for completed requests

    // Initialize all requests as unvisited
    for (int i = 0; i < n; i++) {
        visited[i] = false; 
    }

    printf("\nSSTF Execution Order:\n"); 
    // Loop until all requests are processed
    while (completed < n) { 
        int closest_index = -1; // Index of the closest request
        int closest_distance = MAX_TRACKS + 1; // Initialize to a large number

        // Find the closest unvisited request
        for (int i = 0; i < n; i++) {
            if (!visited[i]) { 
                int distance = abs(current_position - requests[i]); // Calculate distance
                if (distance < closest_distance) { 
                    closest_distance = distance; // Update closest distance
                    closest_index = i; // Update index of closest request
                }
            }
        }

        // If a closest request was found, process it
        if (closest_index != -1) {
            printf("%d ", requests[closest_index]); // Print the request being serviced
            total_seek_time += closest_distance; // Add to total seek time
            current_position = requests[closest_index]; // Move the head to the new position
            visited[closest_index] = true; // Mark this request as visited
            completed++; // Increment the completed request counter
        }
    }

    // Calculate and print the average seek time
    printf("\nAverage Seek Time: %.2f\n", (float)total_seek_time / n); 
}

// Function to implement the SCAN disk scheduling algorithm
void SCAN(int requests[], int n, int head, int direction) {
    int total_seek_time = 0; // Variable for total seek time
    int current_position = head; // Start at the head position

    // Sort requests in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    printf("\nSCAN Execution Order:\n");

    // If the direction is up
    if (direction == 1) { 
        // Process requests in the upward direction
        for (int i = 0; i < n; i++) {
            if (requests[i] >= current_position) {
                printf("%d ", requests[i]); // Print the request
                total_seek_time += abs(current_position - requests[i]); // Update seek time
                current_position = requests[i]; // Move the head to the new position
            }
        }
        
        // Move the head to the end of the disk if not already there
        if (current_position < MAX_TRACKS - 1) { 
            printf("%d ", MAX_TRACKS - 1); // Print the end of the disk
            total_seek_time += abs(current_position - (MAX_TRACKS - 1)); 
            current_position = MAX_TRACKS - 1; // Update head position
        }
        
        // Process requests in the downward direction
        for (int i = n - 1; i >= 0; i--) { 
            if (requests[i] < head) {
                printf("%d ", requests[i]); // Print the request
                total_seek_time += abs(current_position - requests[i]); // Update seek time
                current_position = requests[i]; // Move head
            }
        }
    } else { // If the direction is down
        // Process requests in the downward direction
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] <= current_position) {
                printf("%d ", requests[i]); // Print the request
                total_seek_time += abs(current_position - requests[i]); // Update seek time
                current_position = requests[i]; // Move head
            }
        }

        // Move the head to the beginning of the disk if not already there
        if (current_position > 0) { 
            printf("%d ", 0); // Print the start of the disk
            total_seek_time += abs(current_position - 0); // Update seek time
            current_position = 0; // Update head position
        }

        // Process requests in the upward direction
        for (int i = 0; i < n; i++) {
            if (requests[i] > head) {
                printf("%d ", requests[i]); // Print the request
                total_seek_time += abs(current_position - requests[i]); // Update seek time
                current_position = requests[i]; // Move head
            }
        }
    }

    // Calculate and print the average seek time
    printf("\nAverage Seek Time: %.2f\n", (float)total_seek_time / n);
}

// Function to implement the C-LOOK disk scheduling algorithm
void C_LOOK(int requests[], int n, int head) {
    int total_seek_time = 0; // Variable for total seek time
    int current_position = head; // Start at the head position

    // Sort the requests array in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    printf("\nC-LOOK Execution Order:\n");

    // Process requests greater than or equal to the head position
    for (int i = 0; i < n; i++) {
        if (requests[i] >= current_position) {
            printf("%d ", requests[i]); // Print the request
            total_seek_time += abs(current_position - requests[i]); // Update seek time
            current_position = requests[i]; // Move head
        }
    }

    // Jump back to the start of the request queue
    total_seek_time += abs(current_position - requests[0]);
    current_position = requests[0]; // Reset head to the first request

    // Process requests less than the head position
    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {
            printf("%d ", requests[i]); // Print the request
            total_seek_time += abs(current_position - requests[i]); // Update seek time
            current_position = requests[i]; // Move head
        }
    }

    // Calculate and print the average seek time
    printf("\nAverage Seek Time: %.2f\n", (float)total_seek_time / n);
}
