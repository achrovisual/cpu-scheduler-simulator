/*
PROJECT TITLE: CPU Scheduling
COURSE: Introduction to Operating Systems
SECTION: S12
AUTHORS: Rafael Maderazo & Eugenio Pastoral
*/

#include <stdio.h>
#include <string.h>
#include "core.h"
#include "cpu_scheduling_core.h"

/*
This function takes in the process array, turnaround times, total waiting time, and the number of processes.
This will update all the pertinent values of the process currently executing.
*/
void fcfs_calculate_values(int process[][6], int turn_around_time[] , int *total_waiting_time, int n) {
  for(int i = 0; i < n; i++) {
    // Update start time.
    process[i][3] = (i == 0) ? process[i][1] : process[i - 1][4] > process[i][1] ? process[i - 1][4] : process[i][1];
    // Update end time.
    process[i][4] = process[i][3] + process[i][2];
    // Update turnaround time.
    turn_around_time[i] = process[i][4] - process[i][1];
    // Update waiting time.
    process[i][5] = turn_around_time[i] - process[i][2];
    // Update total waiting time.
    *total_waiting_time += process[i][5];
  }
}

/*
This function takes in the process array and the number of processes.
It will simulate First Come, First Served scheduling algorithm and store the results in the process array.
*/
void fcfs(int process[][6], int n) {
  // Declare variables for First Come, First Served calculation.
  int total_waiting_time = 0;
  int turn_around_time[n];

  // Initialize array to 0.
  initialize_array(turn_around_time, n, 0);

  // First step of this algorithm is to sort the processes by its arrival time (process[index][1]).
  sort_array_by_index(n, 6, process, 1);

  // Calculate the process values.
  fcfs_calculate_values(process, turn_around_time, &total_waiting_time, n);

  // Print the result.
  print_result("First Come, First Served", process, n, total_waiting_time);
}
