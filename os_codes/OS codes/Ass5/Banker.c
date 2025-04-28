#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_RESOURCES 10       // Maximum number of resource types
#define MAX_PROCESSES 10       // Maximum number of processes

// Global variables for matrices and resource tracking
int **Max, **Allocation, **Need; // Matrices for max needs, current allocations, and remaining needs
int *Available;                  // Array for available resources
int numProcesses, numResources;  // Number of processes and resource types

// Function to allocate memory for matrices and available resources
void initializeMatrices() {
    Max = (int **)malloc(numProcesses * sizeof(int *));       // Allocate memory for Max matrix
    Allocation = (int **)malloc(numProcesses * sizeof(int *)); // Allocate memory for Allocation matrix
    Need = (int **)malloc(numProcesses * sizeof(int *));       // Allocate memory for Need matrix
    Available = (int *)malloc(numResources * sizeof(int));      // Allocate memory for Available array

    for (int i = 0; i < numProcesses; i++) {
        Max[i] = (int *)malloc(numResources * sizeof(int));      // Allocate memory for each row in Max
        Allocation[i] = (int *)malloc(numResources * sizeof(int)); // Allocate memory for each row in Allocation
        Need[i] = (int *)malloc(numResources * sizeof(int));      // Allocate memory for each row in Need
    }
}

// Function to free allocated memory for matrices and arrays
void freeMatrices() {
    for (int i = 0; i < numProcesses; i++) {
        free(Max[i]);         // Free each row in Max
        free(Allocation[i]);  // Free each row in Allocation
        free(Need[i]);        // Free each row in Need
    }
    free(Max);               // Free the Max matrix
    free(Allocation);        // Free the Allocation matrix
    free(Need);              // Free the Need matrix
    free(Available);         // Free the Available array
}

// Function to calculate the Need matrix based on Max and Allocation matrices
void calculateNeed() {
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j]; // Calculate Need as Max - Allocation
        }
    }
}

// Function to check if the system is in a safe state
bool isSafe(int work[], bool finish[]) {
    int count = 0; // Count of finished processes
    while (count < numProcesses) { // Until all processes are finished
        bool found = false; // Flag to check if a process can proceed
        for (int p = 0; p < numProcesses; p++) {
            if (!finish[p]) { // If the process has not finished
                int j; // Index for resources
                for (j = 0; j < numResources; j++) {
                    if (Need[p][j] > work[j]) { // If the need is greater than available resources
                        break; // Break the loop if we cannot fulfill the need
                    }
                }

                if (j == numResources) { // If all resources are available
                    for (int k = 0; k < numResources; k++) {
                        work[k] += Allocation[p][k]; // Simulate resource allocation
                    }
                    finish[p] = true; // Mark process as finished
                    found = true; // Indicate a process has been found
                    count++; // Increment the count of finished processes
                }
            }
        }
        if (!found) // If no process can proceed
            return false; // System is not in a safe state
    }
    return true; // System is in a safe state
}

// Function to request resources for a specific process
bool requestResources(int process_id, int request[]) {
    for (int j = 0; j < numResources; j++) {
        if (request[j] > Need[process_id][j]) { // Check if request exceeds max claim
            printf("Error: Process has exceeded its maximum claim.\n");
            return false; // Request cannot be granted
        }
        if (request[j] > Available[j]) { // Check if resources are available
            printf("Process must wait, resources not available.\n");
            return false; // Request cannot be granted
        }
    }

    // Pretend to allocate requested resources
    for (int j = 0; j < numResources; j++) {
        Available[j] -= request[j];           // Reduce available resources
        Allocation[process_id][j] += request[j]; // Allocate resources to process
        Need[process_id][j] -= request[j];    // Reduce need for the process
    }

    // Check system state
    int work[MAX_RESOURCES]; // Work array to track available resources
    bool finish[MAX_PROCESSES] = {0}; // Finish array to track completed processes
    for (int j = 0; j < numResources; j++) {
        work[j] = Available[j]; // Initialize work array with available resources
    }

    if (isSafe(work, finish)) { // Check if the system is in a safe state
        printf("Resources allocated successfully.\n");
        return true; // Request processed successfully
    } else {
        printf("Request cannot be granted. Rolling back.\n");
        for (int j = 0; j < numResources; j++) {
            Available[j] += request[j];           // Rollback allocation
            Allocation[process_id][j] -= request[j]; // Reverse allocation
            Need[process_id][j] += request[j];     // Restore need
        }
        return false; // Request not processed
    }
}

// Function to display the Need matrix
void displayNeed() {
    printf("Need Matrix:\n");
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            printf("%d ", Need[i][j]); // Print each need value
        }
        printf("\n"); // New line for each process
    }
}

// Function to check the safety of the current state
void displaySafety() {
    int work[MAX_RESOURCES]; // Work array for safety check
    bool finish[MAX_PROCESSES] = {0}; // Finish array for completed processes
    for (int j = 0; j < numResources; j++) {
        work[j] = Available[j]; // Initialize work array with available resources
    }

    if (isSafe(work, finish)) { // Check if the system is in a safe state
        printf("System is in a safe state.\n");
    } else {
        printf("System is not in a safe state.\n");
    }
}

// Main function to execute the program
int main() {
    // Get number of processes from user
    printf("Enter number of processes (max %d): ", MAX_PROCESSES);
    scanf("%d", &numProcesses);
    if (numProcesses < 1 || numProcesses > MAX_PROCESSES) { // Validate input
        printf("Invalid number of processes. Exiting.\n");
        return 1; // Exit on invalid input
    }

    // Get number of resource types from user
    printf("Enter number of resource types (max %d): ", MAX_RESOURCES);
    scanf("%d", &numResources);
    if (numResources < 1 || numResources > MAX_RESOURCES) { // Validate input
        printf("Invalid number of resource types. Exiting.\n");
        return 1; // Exit on invalid input
    }

    initializeMatrices(); // Allocate matrices and arrays

    // Get available resources from user
    printf("Enter the available resources:\n");
    for (int j = 0; j < numResources; j++) {
        printf("Resource %d: ", j + 1);
        scanf("%d", &Available[j]); // Read available resources
    }

    // Get maximum resource needs for each process
    printf("Enter the maximum resource needs for each process:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d: ", i + 1);
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &Max[i][j]); // Read max needs for each process
        }
    }

    // Get currently allocated resources for each process
    printf("Enter the currently allocated resources for each process:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d: ", i + 1);
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &Allocation[i][j]); // Read allocated resources for each process
        }
    }

    calculateNeed(); // Calculate the Need matrix

    int choice; // Variable for user menu choice
    while (1) { // Infinite loop for menu
        // Display menu options
        printf("\nBanker's Algorithm Menu:\n");
        printf("1. Calculate Need Matrix\n");
        printf("2. Check Safety\n");
        printf("3. Request Resources\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice); // Read user choice

        switch (choice) {
            case 1:
                displayNeed(); // Display Need matrix
                break;
            case 2:
                displaySafety(); // Check and display safety
                break;
            case 3: { // Request resources from user
                int process_id, request[MAX_RESOURCES];
                printf("Enter process ID (0 to %d): ", numProcesses - 1);
                scanf("%d", &process_id); // Read process ID
                if (process_id < 0 || process_id >= numProcesses) { // Validate input
                    printf("Invalid process ID.\n");
                    break;
                }
                printf("Enter request for resources (values for %d resources): ", numResources);
                for (int j = 0; j < numResources; j++) {
                    scanf("%d", &request[j]); // Read resource request
                }
                bool processed = requestResources(process_id, request); // Process the resource request
                if (processed) {
                    printf("Request for process %d was processed.\n", process_id);
                } else {
                    printf("Request for process %d was NOT processed.\n", process_id);
                }
                break;
            }
            case 4:
                freeMatrices(); // Free allocated memory
                return 0; // Exit program
            default:
                printf("Invalid choice. Please try again.\n"); // Handle invalid menu choices
        }
    }
}
