#include <stdio.h>
#include <string.h>

void fcfs_calculate_start_time(int process[][6], int n) {
  for(int  i = 0; i < n ; i++)
  process[i][3] = process[i][5];
}

void fcfs_calculate_end_time(int process[][6], int n) {
  for(int  i = 0; i < n ; i++) {
    if(i > 0)
    process[i][4] = process[i][5] + process[i][2];
    else
    process[i][4] = process[i][2];
  }

}

void fcfs_calculate_waiting_time(int process[][6], int n) {
  process[0][5] = 0;

  for(int  i = 1; i < n ; i++)
  process[i][5] =  process[i - 1][2] + process[i - 1][5] ;
}

void fcfs(int process[][6], int n) {
  int total_waiting_time = 0;

  fcfs_calculate_waiting_time(process, n);
  fcfs_calculate_start_time(process, n);
  fcfs_calculate_end_time(process, n);

  printf("First Come, First Served\n");
  for(int  i = 0; i < n; i++) {
    total_waiting_time = total_waiting_time + process[i][5];
    printf("[%d] Start time: %d End time: %d | Waiting time: %d\n", process[i][0], process[i][3], process[i][4], process[i][5]);
  }

  printf("Average waiting time: %.1f", (float)total_waiting_time / (float)n);
  printf("\n");
}
