#include <stdio.h>
#include <string.h>
#include "core.h"
#include "cpu_scheduling_core.h"

void psjf_calculate_values(int process[][6], int running_time, int turn_around_time[] , int *total_waiting_time, int status[], int value) {
  process[value][4] = running_time;
  turn_around_time[value] = process[value][4] - process[value][1];
  process[value][5] = turn_around_time[value] - process[value][2];
  *total_waiting_time += process[value][5];
  status[value] = 1;
}

void psjf_clean_context(int process[][6], int context[][4], int *iterator, int n) {
  //remove non-unique paused start time
  for(int i = 0; i < *iterator; i++)
  for(int j = 0; j < n; j++)
  if(context[i][1] == process[j][3]){
    context[i][0] = 0;
    context[i][1] = 0;
    context[i][2] = 0;
    context[i][3] = 0;
  }
}

void psjf(int process[][6], int n){
  int context[999][4];
  int iterator = 0;

  int burst_remaining[999];
  int first_pass[101];

  int total_waiting_time = 0, running_time = 0, completed = 0;
  int turn_around_time[n], status[n];

  int smallest_burst_index = 101;

  initialize_array(status, n, 0);
  initialize_array(turn_around_time, n, 0);

  for(int i = 0; i < n; i++)
  burst_remaining[i] = process[i][2];

  for(int i = 0; i < n; i++)
  first_pass[i] = 1;

  int min = 10000000;

  while(completed != n) {
    int value = -1;
    int minimum = 10000000;


    sjf_find_minimum(process, burst_remaining, status, n, running_time, &value, &minimum);

    // Look for the process with the minimum burst and log context switching
    for(int j = 0; j < n; j++){
      if((process[j][1] <= running_time) && (burst_remaining[j] < min) && burst_remaining[j] > 0){
        if(first_pass[j] == 1){
          context[(iterator)][0] = process[smallest_burst_index][0];
          context[(iterator)][1] = process[smallest_burst_index][3];
          context[(iterator)][2] = running_time;
          context[(iterator)][3] = min;
          (iterator)++;
        }

        min = burst_remaining[j];
        process[j][3] = running_time;
        first_pass[j] = 0;
        smallest_burst_index = j;
      }
    }

    if(value != -1) {
      if(burst_remaining[value] == process[value][2])
      process[value][3] = running_time;

      burst_remaining[value] -= 1;
      running_time++;

      if(burst_remaining[value] == 0) {
        psjf_calculate_values(process, running_time, turn_around_time, &total_waiting_time, status, value);

        completed++;
      }
    }
    else
    running_time++;

    // Update values for context logging
    min = burst_remaining[smallest_burst_index];

    if(min <= 0)
    min = 999;
  }

  sort_array_by_index(n, 6, process, 5);

  psjf_clean_context(process, context, &iterator, n);
  print_result_with_context("Preemptive Shortest Job First", process, context, n, iterator, total_waiting_time);

}
