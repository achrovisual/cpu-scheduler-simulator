#include <stdio.h>
#include <string.h>
#include "core.h"
#include "cpu_scheduling_core.h"

void rr(int process[][6], int n, int tq) {

  int paused_states[MAX_VAL][4];
  int iterator = 0;

  int burst_remaining[MAX_VAL];

  int total_waiting_time = 0, running_time = 0, completed = 0;
  int turn_around_time[n], status[n];

  initialize_array(status, n, 0);
  initialize_array(turn_around_time, n, 0);

  sort_array_by_index(n, 6, process, 1);


  for(int i = 0; i < n; i++)
  burst_remaining[i] = process[i][2];

  while(completed != n) {
    int check = 0;

    for(int i = 0; i < n; i++) {
      if(running_time >= process[i][1] && status[i] == 0) {
        // printf("found\n");
        check = 1;
        break;
      }
    }

    if(check) {
      for(int i = 0; i < n; i ++) {
        // printf("Process ID: %d\nStatus: %d\nRunning Time: %d\nArrival Time: %d\n\n\n", process[i][0], status[i], running_time, process[i][1]);
        if(status[i] == 0 && running_time >= process[i][1]) {
          if(burst_remaining[i] == process[i][2]) {
            process[i][3] = running_time > process[i][1] ? running_time : process[i][1];
            running_time = process[i][3];
          }

          if(burst_remaining[i] - tq > 0) {
            burst_remaining[i] -= tq;
            running_time += tq;
          }
          else {
            running_time += burst_remaining[i];
            burst_remaining[i] = 0;

            completed++;

            process[i][4] = running_time;
            turn_around_time[i] = process[i][4] - process[i][1];
            process[i][5] = turn_around_time[i] - process[i][2];
            total_waiting_time += process[i][5];

            status[i] = 1;
          }
                  // printf("Process ID: %d\nBurst Time: %d\nStart Time: %d\nEnd Time: %d\nWaiting Time: %d\nRunning Time: %d\nRemaining Burst: %d\n\n", process[i][0], process[i][2], process[i][3], process[i][4], process[i][5], running_time, burst_remaining[i]);
        }
      }
    }
    else
    running_time++;

  }

  print_result("Round Robin", process, n, total_waiting_time);
}
