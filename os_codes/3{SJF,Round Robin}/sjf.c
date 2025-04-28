#include <stdio.h>
  
int main() 
{
      int arrival_time[10], burst_time[10], temp[10];
      int completion_time[10], wait_time[10], turnaround_time[10];
      int i, smallest, count = 0, time, n;
      double total_wait_time = 0, total_turnaround_time = 0, end;
      float average_waiting_time, average_turnaround_time;

      printf("\nEnter the Total Number of Processes:\t");
      scanf("%d", &n); 

      printf("\nEnter Details of %d Processes\n", n);
      for(i = 0; i < n; i++)
      {
            printf("\nEnter Arrival Time:\t");
            scanf("%d", &arrival_time[i]);

            printf("Enter Burst Time:\t");
            scanf("%d", &burst_time[i]); 

            temp[i] = burst_time[i];
      }

      burst_time[9] = 9999;  
      
      for(time = 0; count != n; time++)
      {
            smallest = 9;
            for(i = 0; i < n; i++)
            {
                  if(arrival_time[i] <= time && burst_time[i] < burst_time[smallest] && burst_time[i] > 0)
                  {
                        smallest = i;
                  }
            }
            burst_time[smallest]--;

            if(burst_time[smallest] == 0)
            {
                  count++;
                  completion_time[smallest] = time+1;
                  turnaround_time[smallest] = completion_time[smallest] - arrival_time[smallest];
                  wait_time[smallest] = turnaround_time[smallest] - temp[smallest];

                  total_turnaround_time+=turnaround_time[smallest];
                  total_wait_time+=wait_time[smallest];
            }
      }

      average_waiting_time = total_wait_time / n; 
      average_turnaround_time = total_turnaround_time / n;

      printf("\nProcess | AT  | BT  | CT  | TAT | WT\n");
printf("--------|-----|-----|-----|-----|-----\n");
for(i = 0; i < n; i++) {
    printf("P%-7d| %-3d | %-3d | %-3d | %-3d | %-3d\n",
           i + 1, arrival_time[i], temp[i], completion_time[i], turnaround_time[i], wait_time[i]);
}

      
      printf("\nAverage Waiting Time:\t%lf\n", average_waiting_time);
      printf("Average Turnaround Time:\t%lf\n", average_turnaround_time);
      return 0;
}