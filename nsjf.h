#include <stdio.h>

#define MAX 100

void nsjf_initialize_array(int arr[], int size) {
  for(int i = 0; i < size; i ++)
  arr[i] = 32767;
}

void nsjf_sort_process(int process[][6], int n) {
  for(int i = 0; i < n; i++)
  for(int j = 0; j < n - i - 1; j++)
  if(process[j][1] > process[j + 1][1]) {
    for(int k = 0; k < 6; k++) {
      int temp = process[j][k];
      process[j][k] = process[j + 1][k];
      process[j + 1][k] = temp;
    }
  }
}

void nsjf_maintain_minimum(int process[][6], int n) {
  int temp, val;
  int completion_time[n];

  nsjf_initialize_array(completion_time, n);

  completion_time[0] = process[0][1] + process[0][2];

  for(int i = 1; i < n; i++)
  {
    temp = completion_time[i - 1];
    int min = process[i][2];

    for(int j = i; j < n; j++)
    if(temp >= process[j][1] && min >= process[j][2]) {
      min = process[j][2];
      val = j;
    }

    completion_time[val] = temp + process[val][2];

    for(int k = 0; k < 6; k++) {
      int tempo = process[val][k];
      process[val][k] = process[i][k];
      process[i][k] = tempo;
    }
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
  nsjf_maintain_minimum(process, n);
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
