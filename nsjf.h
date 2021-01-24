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
This function takes in the process array, running time, turnaround times, total waiting time, statuses, and the index value.
This will update all the pertinent values of the process currently executing.
*/
void nsjf_calculate_values(int process[][6], int running_time, int turn_around_time[] , int *total_waiting_time, int status[], int value) {
  process[value][3] = running_time;
  process[value][4] = process[value][3] + process[value][2];
  turn_around_time[value] = process[value][4] - process[value][1];
  process[value][5] = turn_around_time[value] - process[value][2];
  *total_waiting_time += process[value][5];
  status[value] = 1;
}

/*
This function takes in the process array and the number of processes.
It will simulate Non-Preemptive Shortest Job First scheduling algorithm and store the results in the process array.
*/
void nsjf(int process[][6], int n) {
  // Declare variables for context switching.
  int burst_remaining[999];

  // Declare variables for Non-Preemptive Shortest Job First calculation.
  int total_waiting_time = 0, running_time = 0, completed = 0;
  int turn_around_time[n], status[n];

  // Initialize arrays to 0.
  initialize_array(status, n, 0);
  initialize_array(turn_around_time, n, 0);

  // Copy the burst times of the processes to a mutable array.
  for(int i = 0; i < n; i++)
  burst_remaining[i] = process[i][2];

  // Execute the processes until all of the process have been completed.
  while(completed != n) {
    // Declare and initialize variables for finding the process with the minimum burst time.
    int value = -1;
    int minimum = 10000000;

    // Find the process with the minimum burst time that has already arrived.
    sjf_find_minimum(process, burst_remaining, status, n, running_time, &value, &minimum);

    // If the process has been found, execute it.
    if(value != -1) {
      // Calculate the process values.
      nsjf_calculate_values(process, running_time, turn_around_time, &total_waiting_time, status, value);

      completed++;
      running_time = process[value][4];
    }
    // Otherwise, increment the running time.
    else
    running_time++;
  }

  // Sort the processes by start time.
  sort_array_by_index(n, 6, process, 3);

  // Print the result.
  print_result("Non-Preemptive Shortest Job First", process, n, total_waiting_time);
}
