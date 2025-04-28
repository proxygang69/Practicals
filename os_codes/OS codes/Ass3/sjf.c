#include <stdio.h> // Include standard input-output header
#include <limits.h> // Include limits header for INT_MAX

#define MAX 100 // Define a constant for the maximum number of processes

// Define a structure to represent a process with various attributes
typedef struct {
    int id; // Process ID
    int arrival_time; // Arrival time of the process
    int burst_time; // Total burst time needed for execution
    int completion_time; // Time at which the process completes execution
    int waiting_time; // Time the process has been waiting in the ready queue
    int turnaround_time; // Total time taken from arrival to completion
} Process;

// Function to calculate Shortest Job First (SJF) scheduling
void calculateSJF(Process p[], int n) {
    int i, j; // Loop counters
    int total_wt = 0, total_tat = 0; // Variables to accumulate total waiting and turnaround times
    int min_index, temp; // Variables for finding the process with the shortest burst time
    
    // Sort processes based on arrival time
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[j].arrival_time < p[i].arrival_time) {
                // Swap arrival_time
                temp = p[i].arrival_time;
                p[i].arrival_time = p[j].arrival_time;
                p[j].arrival_time = temp;
                
                // Swap burst_time
                temp = p[i].burst_time;
                p[i].burst_time = p[j].burst_time;
                p[j].burst_time = temp;
                
                // Swap id
                temp = p[i].id;
                p[i].id = p[j].id;
                p[j].id = temp;
            }
        }
    }
    
    int time = 0; // Current time in the simulation
    int completed = 0; // Number of completed processes
    int visited[MAX] = {0}; // Array to track completed processes
    
    // Loop until all processes are completed
    while (completed != n) {
        int shortest = INT_MAX; // Initialize shortest burst time to maximum
        min_index = -1; // Initialize index of process with the shortest burst time
        
        // Find the process with the shortest burst time that is ready
        for (i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && !visited[i] && p[i].burst_time < shortest) {
                shortest = p[i].burst_time; // Update shortest burst time
                min_index = i; // Update index of the process with the shortest burst time
            }
        }
        
        if (min_index != -1) { // If a valid process is found
            // Update completion time
            time += p[min_index].burst_time; // Increment current time by burst time of selected process
            p[min_index].completion_time = time; // Set completion time for the process
            p[min_index].turnaround_time = p[min_index].completion_time - p[min_index].arrival_time; // Calculate turnaround time
            p[min_index].waiting_time = p[min_index].turnaround_time - p[min_index].burst_time; // Calculate waiting time
            
            total_wt += p[min_index].waiting_time; // Accumulate total waiting time
            total_tat += p[min_index].turnaround_time; // Accumulate total turnaround time
            
            visited[min_index] = 1; // Mark the process as visited/completed
            completed++; // Increment completed process count
        } else {
            time++; // If no process is ready, increment time
        }
    }
    
    // Print Gantt Chart
    printf("\nGantt Chart:\n");
    printf("0"); // Start time of Gantt chart
    for (i = 0; i < n; i++) {
        printf("----%d", p[i].completion_time); // Print completion times
    }
    printf("\n");
    
    printf(" "); // Space for the process labels
    for (i = 0; i < n; i++) {
        printf("| P%d ", p[i].id); // Print process IDs in Gantt Chart
    }
    printf("|\n");
    
    // Print process details
    printf("\nSJF Scheduling:\n");
    printf("ID\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    for (i = 0; i < n; i++) {
        // Print each process's details
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", p[i].id, p[i].arrival_time, p[i].burst_time, p[i].completion_time, p[i].waiting_time, p[i].turnaround_time);
    }
    
    // Print average waiting and turnaround times
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

// Main function
int main() {
    int n, i; // Variables for number of processes and loop index
    printf("Enter the number of processes: "); // Prompt for number of processes
    scanf("%d", &n); // Read number of processes
    
    Process p[n]; // Declare an array of processes
    
    // Loop to read arrival and burst times for each process
    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        p[i].id = i + 1; // Assign process ID
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time); // Read arrival and burst times
    }
    
    // Call the SJF calculation function
    calculateSJF(p, n);
    return 0; // Return success
}
