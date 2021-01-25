/*
PROJECT TITLE: CPU Scheduling
COURSE: Introduction to Operating Systems
SECTION: S12
AUTHORS: Rafael Maderazo & Eugenio Pastoral
*/

#include <stdio.h>
#include <string.h>

#ifndef CPU_SCHEDULING_CORE_H
#define CPU_SCHEDULING_CORE_H

/*
This function takes in the process array, remaining burst times, statuses, running time, value index, and the minimum.
This will look for the process that has the minimum burst time.
*/
void sjf_find_minimum(int process[][6], int burst_remaining[], int status[], int n, int running_time, int *value, int *minimum) {
  for(int i = 0; i < n; i++) {
    if(process[i][1] <= running_time && status[i] == 0) {
      if(burst_remaining[i] < *minimum) {
        *minimum = burst_remaining[i];
        *value = i;
      }
      if(burst_remaining[i] == *minimum)
      if(process[i][1] < process[*value][1]) {
        *minimum = burst_remaining[i];
        *value = i;
      }
    }
  }
}

/*
This function takes in the process array, running time, turnaround times, total waiting time, statuses, and value index.
This will update all the pertinent values of the process currently executing.
*/
void sjf_calculate_values(int process[][6], int running_time, int turn_around_time[] , int *total_waiting_time, int status[], int value) {
  process[value][3] = running_time;
  process[value][4] = process[value][3] + process[value][2];
  turn_around_time[value] = process[value][4] - process[value][1];
  process[value][5] = turn_around_time[value] - process[value][2];
  *total_waiting_time += process[value][5];
  status[value] = 1;
}

/*
This function takes in the process array, number of processes, and total waiting time.
This will calculate the total waiting time.
*/
void calculate_total_waiting_time(int process[][6], int n, int *total_waiting_time) {
  for(int  i = 0; i < n; i++) {
    *total_waiting_time = *total_waiting_time + process[i][5];
  }
}

/*
This function takes in a message, process array, number of processes, and total waiting time.
This prints the result.
*/
void print_result(char message[], int process[][6], int n, int total_waiting_time) {
  printf("%s\n", message);
  for(int  i = 0; i < n; i++) {
    printf("[%d] Start time: %d End time: %d | Waiting time: %d\n", process[i][0], process[i][3], process[i][4], process[i][5]);
  }

  printf("Average waiting time: %.1f", (float)total_waiting_time / (float)n);
  printf("\n");
}

/*
This function takes in a message, process array, contexts,  number of processes, context iterator, and total waiting time.
This prints the result.
*/
void print_result_with_context(char message[], int process[][6], int context[][4], int n, int iterator, int total_waiting_time) {
  printf("%s\n", message);
  for(int  i = 0; i < n; i++) {
    int is_valid = 1;

    for(int j = 0; j < iterator; j++){
      if(process[i][0] == context[j][0] && process[i][3] != context[j][1]){
        if(is_valid == 1)
        printf("[%d] Start time: %d End time: %d | ", context[j][0], context[j][1], context[j][2]);
        else
        printf("Start time: %d End time: %d | ",  context[j][1], context[j][2]);

        is_valid = 0;
      }
    }
    if(is_valid == 1)
    printf("[%d] Start time: %d End time: %d | Waiting time: %d\n", process[i][0], process[i][3], process[i][4], process[i][5]);
    else
    printf("Start time: %d End time: %d | Waiting time: %d\n",  process[i][3], process[i][4], process[i][5]);
  }
  printf("Average waiting time: %.1f", (float)total_waiting_time / (float)n);
  printf("\n");
}
#endif
