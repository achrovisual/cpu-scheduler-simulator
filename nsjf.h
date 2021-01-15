#include <stdio.h>

void nsjf_sort_process(int process[][6], int n) {
  int btime = 0, min, z = 1;

  for(int i = 0; i < n; i++)
  for(int j = 0; j < n - i - 1; j++)
  if(process[j][1] > process[j + 1][1]) {
    for(int k = 0; k < 6; k++) {
      int temp = process[j][k];
      process[j][k] = process[j + 1][k];
      process[j + 1][k] = temp;
    }
  }

  for(int j=0;j<5;j++)
  {
    btime=btime+process[j][2];
    min=process[z][2];

    for(int i = z; i < n; i++) {
      if (btime >= process[i][1] && process[i][2] < min) {
        for(int k = 0; k < 6; k++) {
          int temp = process[z][k];
          process[z][k] = process[i][k];
          process[i][k] = temp;
        }
      }
    }
    z++;
  }
}

void nsjf_calculate_start_time(int process[][6], int n) {
  for(int  i = 0; i < n; i++) {
    if(i > 0)
    process[i][3] = process[i - 1][4];
    else
    process[i][3] = 0;
  }
}

void nsjf_calculate_end_time(int process[][6], int n) {
  for(int  i = 0; i < n ; i++) {
    if(i > 0)
    process[i][4] = process[i - 1][4] + process[i][2];
    else
    process[i][4] = process[i][2];
  }
}

void nsjf_calculate_waiting_time(int process[][6], int n) {
  int sum = 0;
  process[0][5] = 0;
  for(int i = 1; i < n; i++) {
    sum += process[i - 1][2];
    process[i][5] = sum - process[i][1];
  }
}

void nsjf(int process[][6], int n) {
  int total_waiting_time = 0;

  nsjf_sort_process(process, n);
  nsjf_calculate_waiting_time(process, n);
  nsjf_calculate_end_time(process, n);
  nsjf_calculate_start_time(process, n);

  printf("Non-Preemptive Shortest Job First\n");
  for(int  i = 0; i < n; i++) {
    total_waiting_time = total_waiting_time + process[i][5];
    printf("[%d] Start time: %d End time: %d | Waiting time: %d\n", process[i][0], process[i][3], process[i][4], process[i][5]);
  }

  printf("Average waiting time: %.1f", (float)total_waiting_time / (float)n);
  printf("\n");
}
