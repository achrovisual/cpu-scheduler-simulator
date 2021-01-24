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
void psjf_calculate_values(int process[][6], int running_time, int turnaround_time[] , int *total_waiting_time, int status[], int value) {
  // Update end time.
  process[value][4] = running_time;
  // Update turnaround time.
  turnaround_time[value] = process[value][4] - process[value][1];
  // Update waiting time.
  process[value][5] = turnaround_time[value] - process[value][2];
  // Update total waiting time.
  *total_waiting_time += process[value][5];
  // Set process status to complete.
  status[value] = 1;
}

/*
This function takes in the process array, context array, context iterator, and the number of processes.
This will remove all non-unique context switch records in the array.
*/
void psjf_clean_context(int process[][6], int context[][4], int *iterator, int n) {
  for(int i = 0; i < *iterator; i++)
  for(int j = 0; j < n; j++)
  // If non-unique context switch record is found, set all its values to 0.
  if(context[i][1] == process[j][3]){
    context[i][0] = 0;
    context[i][1] = 0;
    context[i][2] = 0;
    context[i][3] = 0;
  }
}

/*
This function takes in the process array and the number of processes.
It will simulate Preemptive Shortest Job First scheduling algorithm and store the results in the process array.
*/
void psjf(int process[][6], int n){
  // Declare variables for context switching.
  int context[999][4];
  int iterator = 0;
  int first_pass[101];
  int smallest_burst_index = 101;
  int min = 999;

  // Declare variables for Preemptive Shortest Job First calculation.
  int burst_remaining[999];
  int total_waiting_time = 0, running_time = 0, completed = 0;
  int turnaround_time[n], status[n];

  // Initialize arrays to 0.
  initialize_array(status, n, 0);
  initialize_array(turnaround_time, n, 0);

  // Initialize array to 1.
  initialize_array(first_pass, n, 1);

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

    // Look for the process with the minimum burst and log context switching.
    for(int j = 0; j < n; j++){
      // Find the the process with the minimum burst time that has arrived and not been completed yet.
      if((process[j][1] <= running_time) && (burst_remaining[j] < min) && burst_remaining[j] > 0){
        // If the aforementioned process has not executed yet, log it and update its start time.
        if(first_pass[j] == 1){
          context[(iterator)][0] = process[smallest_burst_index][0];
          context[(iterator)][1] = process[smallest_burst_index][3];
          context[(iterator)][2] = running_time;
          context[(iterator)][3] = min;
          (iterator)++;
        }
        // Update start time.
        process[j][3] = running_time;

        // Update first pass flag.
        first_pass[j] = 0;

        min = burst_remaining[j];
        smallest_burst_index = j;
      }
    }

    // If the process has been found, execute it.
    if(value != -1) {
      // If it's the first time that the process is executing, set its starting time to the current running time.
      if(burst_remaining[value] == process[value][2])
      // Update start time.
      process[value][3] = running_time;

      burst_remaining[value] -= 1;
      running_time++;

      // If the process is already done, calculate all the pertinent values for that process.
      if(burst_remaining[value] == 0) {
        // Calculate the process values.
        psjf_calculate_values(process, running_time, turnaround_time, &total_waiting_time, status, value);

        completed++;
      }
    }
    // Otherwise, increment the running time.
    else
    running_time++;

    // Update values for context switch logging.
    min = burst_remaining[smallest_burst_index];

    // If min is less than or equal to zero, reset its value.
    if(min <= 0)
    min = 999;
  }

  // Sort the processes by waiting time.
  sort_array_by_index(n, 6, process, 5);

  // Remove all context switch records that are non-unique.
  psjf_clean_context(process, context, &iterator, n);

  // Print the result.
  print_result_with_context("Preemptive Shortest Job First", process, context, n, iterator, total_waiting_time);

}
