#include <stdio.h>
#include <string.h>
#include "core.h"
#include "cpu_scheduling_core.h"

#define MAX 101

void nsjf_calculate_values(int process[][6], int running_time, int turn_around_time[] , int *total_waiting_time, int status[], int value) {
  process[value][3] = running_time;
  process[value][4] = process[value][3] + process[value][2];
  turn_around_time[value] = process[value][4] - process[value][1];
  process[value][5] = turn_around_time[value] - process[value][2];
  *total_waiting_time += process[value][5];
  status[value] = 1;
}

void nsjf_find_minimum(int process[][6], int status[], int n, int running_time, int *value, int *minimum) {
  for(int i = 0; i < n; i++) {
    if(process[i][1] <= running_time && status[i] == 0) {
      if(process[i][2] < *minimum) {
        *minimum = process[i][2];
        *value = i;
      }
      if(process[i][2] == *minimum)
      if(process[i][1] < process[*value][1]) {
        *minimum = process[i][2];
        *value = i;
      }
    }
  }
}

void nsjf(int process[][6], int n) {
  int total_waiting_time = 0, running_time = 0, completed = 0;
  int turn_around_time[n], status[n];

  initialize_array(status, n, 0);
  initialize_array(turn_around_time, n, 0);

  while(completed != n) {
    int value = -1;
    int minimum = 10000000;

    nsjf_find_minimum(process, status, n, running_time, &value, &minimum);

    if(value != -1) {
      nsjf_calculate_values(process, running_time, turn_around_time, &total_waiting_time, status, value);

      completed++;
      running_time = process[value][4];
    }
    else
    running_time++;
  }

  sort_array_by_index(n, 6, process, 3);

  print_result("Non-Preemptive Shortest Job First", process, n, total_waiting_time);
}
