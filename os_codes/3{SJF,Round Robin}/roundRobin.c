#include <stdio.h>

int main() {
    int cnt, j, n, t, remain, flag = 0, tq;
    int wt = 0, tat = 0, at[10], bt[10], temp[10];
    int completion_time[10], turnaround_time[10], waiting_time[10];

    printf("Enter Total Processes:\t ");
    scanf("%d", &n);
    remain = n;

    for (cnt = 0; cnt < n; cnt++) {
        printf("Enter Arrival Time and Burst Time for Process %d :", cnt + 1);
        scanf("%d", &at[cnt]);
        scanf("%d", &bt[cnt]);
        temp[cnt] = bt[cnt];
    }

    printf("Enter Time Quantum:\t");
    scanf("%d", &tq);


    for (t = 0, cnt = 0; remain != 0;) {
        if (bt[cnt] > 0 && at[cnt] <= t) { // Check if process is ready
            if (bt[cnt] <= tq) { // Process will finish within this time quantum
                t += bt[cnt];
                bt[cnt] = 0;
                flag = 1;
            } else { // Process will be partially executed
                bt[cnt] -= tq;
                t += tq;
            }

            if (bt[cnt] == 0 && flag == 1) { // Process just finished
                remain--;
                completion_time[cnt] = t;
                turnaround_time[cnt] = completion_time[cnt] - at[cnt]; // Calculate TAT
                waiting_time[cnt] = turnaround_time[cnt] - temp[cnt]; // Calculate WT
                wt += waiting_time[cnt];
                tat += turnaround_time[cnt];
                flag = 0;
            }
        }
        
        cnt = (cnt + 1) % n; // Move to the next process, wrapping back to 0
    }
    int i;
    printf("\nProcess | AT  | BT  | CT  | TAT | WT\n");
printf("--------|-----|-----|-----|-----|-----\n");
for(i = 0; i < n; i++) {
    printf("P%-7d| %-3d | %-3d | %-3d | %-3d | %-3d\n",
           i + 1, at[i], temp[i], completion_time[i], turnaround_time[i], waiting_time[i]);
}

    printf("\nAverage Waiting Time= %f\n", wt * 1.0 / n);
    printf("Average Turnaround Time = %f\n", tat * 1.0 / n);

    return 0;
}
