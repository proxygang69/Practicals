#include <stdio.h> // Include standard input-output header

#define MAX 100 // Define a constant for the maximum number of processes

// Define a structure to represent a process with various attributes
typedef struct {
    int id; // Process ID
    int arrival_time; // Arrival time of the process
    int burst_time; // Total burst time needed for execution
    int remaining_time; // Remaining burst time for the process
    int completion_time; // Time at which the process completes execution
    int waiting_time; // Time the process has been waiting in the ready queue
    int turnaround_time; // Total time taken from arrival to completion
} Process;

// Function to calculate Round Robin scheduling
void calculateRR(Process p[], int n, int quantum) {
    int i; // Loop counter
    int total_wt = 0, total_tat = 0; // Variables to accumulate total waiting and turnaround times
    int time = 0; // Current time in the simulation
    int completed = 0; // Number of completed processes
    int gantt_start[MAX], gantt_end[MAX]; // Arrays to store Gantt chart start and end times
    int gantt_index = 0; // Index for Gantt chart arrays
    
    // Initialize remaining time for each process
    for (i = 0; i < n; i++) {
        p[i].remaining_time = p[i].burst_time; // Set remaining time to burst time initially
    }
    
    // Loop until all processes are completed
    while (completed < n) {
        int done_in_this_cycle = 0; // Flag to check if any process executed in this cycle
        
        // Iterate over each process
        for (i = 0; i < n; i++) {
            // Check if the process has arrived and has remaining time
            if (p[i].arrival_time <= time && p[i].remaining_time > 0) {
                done_in_this_cycle = 1; // Mark that at least one process has executed
                
                // Record the start time for Gantt Chart
                gantt_start[gantt_index] = time;
                
                // Determine the time to execute this process in this cycle
                int exec_time = (p[i].remaining_time < quantum) ? p[i].remaining_time : quantum; // Calculate execution time
                p[i].remaining_time -= exec_time; // Decrease the remaining time
                time += exec_time; // Increment the current time
                
                // Record the end time for Gantt Chart
                gantt_end[gantt_index] = time;
                gantt_index++; // Increment Gantt chart index
                
                // Check if the process has finished execution
                if (p[i].remaining_time == 0) {
                    p[i].completion_time = time; // Set completion time
                    p[i].turnaround_time = p[i].completion_time - p[i].arrival_time; // Calculate turnaround time
                    p[i].waiting_time = p[i].turnaround_time - p[i].burst_time; // Calculate waiting time
                    
                    total_wt += p[i].waiting_time; // Accumulate total waiting time
                    total_tat += p[i].turnaround_time; // Accumulate total turnaround time
                    completed++; // Increment completed process count
                }
            }
        }
        
        // If no process was executed in this cycle, increment time
        if (!done_in_this_cycle) {
            time++;
        }
    }
    
    // Print Gantt Chart
    printf("\nGantt Chart:\n");
    for (i = 0; i < gantt_index; i++) {
        printf("%d", gantt_start[i]); // Print start times
        if (i < gantt_index - 1) {
            printf("----"); // Print separator between start times
        }
    }
    printf("\n");
    
    for (i = 0; i < gantt_index; i++) {
        printf("| P%d ", p[i % n].id); // Print process IDs in Gantt Chart
    }
    printf("|\n");
    
    for (i = 0; i < gantt_index; i++) {
        printf("%d", gantt_end[i]); // Print end times
        if (i < gantt_index - 1) {
            printf("----"); // Print separator between end times
        }
    }
    printf("\n");

    // Print process details
    printf("\nRound Robin Scheduling (Quantum = %d):\n", quantum);
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
    int n, i, quantum; // Variables for number of processes, loop index, and time quantum
    printf("Enter the number of processes: "); // Prompt for number of processes
    scanf("%d", &n); // Read number of processes
    
    Process p[n]; // Declare an array of processes
    
    // Loop to read arrival and burst times for each process
    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        p[i].id = i + 1; // Assign process ID
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time); // Read arrival and burst times
    }
    
    printf("Enter the time quantum: "); // Prompt for time quantum
    scanf("%d", &quantum); // Read time quantum
    
    // Call the Round Robin calculation function
    calculateRR(p, n, quantum);
    return 0; // Return success
}
