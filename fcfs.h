#include <stdio.h>
#include <string.h>
#include "core.h"
#include "cpu_scheduling_core.h"

void fcfs_calculate_values(int process[][6], int turn_around_time[] , int *total_waiting_time, int n) {
  for(int i = 0; i < n; i++) {
    process[i][3] = (i == 0) ? process[i][1] : process[i - 1][4] > process[i][1] ? process[i - 1][4] : process[i][1];
    process[i][4] = process[i][3] + process[i][2];
    turn_around_time[i] = process[i][4] - process[i][1];
    process[i][5] = turn_around_time[i] - process[i][2];
    *total_waiting_time += process[i][5];
  }
}

void fcfs(int process[][6], int n) {
  int total_waiting_time = 0;
  int turn_around_time[n];

  initialize_array(turn_around_time, n, 0);

  sort_array_by_index(n, 6, process, 1);

  fcfs_calculate_values(process, turn_around_time, &total_waiting_time, n);

  print_result("First Come, First Served", process, n, total_waiting_time);
}
