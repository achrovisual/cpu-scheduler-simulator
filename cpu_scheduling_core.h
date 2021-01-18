#include <stdio.h>
#include <string.h>

#ifndef CPU_SCHEDULING_CORE_H
#define CPU_SCHEDULING_CORE_H

void calculate_total_waiting_time(int process[][6], int n, int *total_waiting_time) {
  for(int  i = 0; i < n; i++) {
    *total_waiting_time = *total_waiting_time + process[i][5];
  }
}


void print_result(char message[], int process[][6], int n, int total_waiting_time) {
  printf("%s\n", message);
  for(int  i = 0; i < n; i++) {
    printf("[%d] Start time: %d End time: %d | Waiting time: %d\n", process[i][0], process[i][3], process[i][4], process[i][5]);
  }

  printf("Average waiting time: %.1f", (float)total_waiting_time / (float)n);
  printf("\n");
}

void print_result_with_paused_states(char message[], int process[][6], int paused_states[][4], int n, int iterator, int total_waiting_time) {
  printf("%s\n", message);
  for(int  i = 0; i < n; i++) {
    int is_valid = 1;

    for(int j = 0; j < iterator; j++){
      if(process[i][0] == paused_states[j][0] && process[i][3] != paused_states[j][1]){
        if(is_valid == 1)
        printf("[%d] Start time: %d End time: %d | ", paused_states[j][0], paused_states[j][1], paused_states[j][2]);
        else
        printf("Start time: %d End time: %d | ",  paused_states[j][1], paused_states[j][2]);

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
