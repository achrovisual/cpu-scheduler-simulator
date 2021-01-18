#include <stdio.h>
#include <string.h>
#include "core.h"
#include "cpu_scheduling_core.h"

#define MAX_VAL 999

void psjf_initialize_array(int arr[][4], int size) {
  for(int i = 0; i < size; i ++)
  for(int j = 0; j < 4; i ++)
  arr[i][j] = 0;
}

void psjf_clean_paused_states(int process[][6], int paused_states[][4], int *iterator, int n) {
  //remove non-unique paused start time
  for(int i = 0; i < *iterator; i++)
  for(int j = 0; j < n; j++)
  if(paused_states[i][1] == process[j][3]){
    //shift
    for(int k = j; k < *iterator; k++){
      paused_states[k][0] = paused_states[k + 1][0];
      paused_states[k][1] = paused_states[k + 1][1];
      paused_states[k][2] = paused_states[k + 1][2];
      paused_states[k][3] = paused_states[k + 1][3];
    }
    *iterator = *iterator - 1;
  }
}

void psjf_sort_process(int process[][6], int paused_states[][4], int n) {
  for(int i = 0; i < n; i++)
  for(int j = 0; j < n - i - 1; j++)
  if(process[j][5] > process[j + 1][5]) {
    for(int k = 0; k < 6; k++) {
      int temp = process[j][k];
      process[j][k] = process[j + 1][k];
      process[j + 1][k] = temp;
    }
  }
}

void psjf_calculate_waiting_time(int process[][6], int paused_states[][4], int *iterator, int n)
{
  int remaining_time[101], first_pass[101];
  for(int i = 0; i < n; i++){
    first_pass[i] = 1;
  }

  for(int i = 0; i < n; i++){
    remaining_time[i] = process[i][2];
  }

  int completed_process = 0, time = 0, smallest_burst_index = 101, min = MAX_VAL;
  int check = 0;
  *iterator = 0;
  while(completed_process != n){
    for(int j = 0; j < n; j++){
      if((process[j][1] <= time) && (remaining_time[j]  < min) && remaining_time[j] > 0){
        if(first_pass[j] == 1){
          paused_states[(*iterator)][0] = process[smallest_burst_index][0];
          paused_states[(*iterator)][1] = process[smallest_burst_index][3];
          paused_states[(*iterator)][2] = time;
          paused_states[(*iterator)][3] = min;
          (*iterator)++;
        }

        min = remaining_time[j];
        check = 1;
        process[j][3] = time;
        first_pass[j] = 0;
        smallest_burst_index = j;
      }
    }

    if(check == 0){
      time++;
      continue;
    }

    remaining_time[smallest_burst_index]--;
    min = remaining_time[smallest_burst_index];

    if(min==0){
      min = MAX_VAL;
    }

    if(remaining_time[smallest_burst_index] == 0){
      completed_process++;
      check = 1;

      process[smallest_burst_index][4] = time + 1;

      process[smallest_burst_index][5] = process[smallest_burst_index][4] -
      process[smallest_burst_index][2] - process[smallest_burst_index][1];

      if(process[smallest_burst_index][5] < 0){
        process[smallest_burst_index][0] = 0;
      }
    }

    time++;
  }
}

void psjf(int process[][6], int n){
  int total_waiting_time = 0;
  int paused_states[n][4];
  int iterator = 0;

  psjf_calculate_waiting_time(process, paused_states, &iterator, n);
  psjf_clean_paused_states(process, paused_states, &iterator, n);
  psjf_sort_process(process, paused_states, n);

  calculate_total_waiting_time(process, n, &total_waiting_time);

  print_result_with_paused_states("Preemptive Shortest Job First", process, paused_states, n, iterator, total_waiting_time);

}
