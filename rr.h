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
This function takes in the process array, number of processes, and time quantum.
It will simulate Round Robin scheduling algorithm and store the results in the process array.
*/
void rr(int process[][6], int n, int time_quantum) {
  // Declare variables for context switching.
  int context[999][4];
  int iterator = 0;

  // Declare variables for Round Robin calculation.
  int burst_remaining[999];
  int total_waiting_time = 0, running_time = 0, completed = 0;
  int turnaround_time[n], status[n];

  // Initialize arrays to 0.
  initialize_array(status, n, 0);
  initialize_array(turnaround_time, n, 0);

  // First step of this algorithm is to sort the processes by its arrival time (process[index][1]).
  sort_array_by_index(n, 6, process, 1);

  // Copy the burst times of the processes to a mutable array.
  for(int i = 0; i < n; i++)
  burst_remaining[i] = process[i][2];

  // Execute the processes based on the time quantum indicated.
  while(completed != n) {
    // Declare and initialize boolean variable for active process checking.
    int check = 0;

    // Look for a process that has already arrived and not yet complete.
    for(int i = 0; i < n; i++) {
      if(running_time >= process[i][1] && status[i] == 0) {
        check = 1;
        break;
      }
    }

    // If a process has been found, start executing each process.
    if(check) {
      // Go through each process and check if it has arrived.
      for(int i = 0; i < n; i ++) {
        // If the process has arrived and is not yet completed, execute the process.
        if(status[i] == 0 && running_time >= process[i][1]) {
          // If the process still hasn't executed, run it and update the values.
          if(burst_remaining[i] == process[i][2]) {
            // Update start time
            process[i][3] = running_time > process[i][1] ? running_time : process[i][1];
            // Set running time to start time of process.
            running_time = process[i][3];
          }
          // If the remaining burst - time quantum is greater than 0, execute it and log the context switch.
          if(burst_remaining[i] - time_quantum > 0) {
            // Update start time.
            process[i][3] = running_time;

            burst_remaining[i] -= time_quantum;
            running_time += time_quantum;

            // Log context switches.
            context[iterator][0] = process[i][0];
            context[iterator][1] = process[i][3];
            context[iterator][2] = running_time;
            iterator++;
          }
          // Otherwise, the process has executed completely and update the values.
          else {
            // Update start time.
            process[i][3] = running_time;

            running_time += burst_remaining[i];
            burst_remaining[i] = 0;

            completed++;

            // Update end time.
            process[i][4] = running_time;
            // Update turnaround time.
            turnaround_time[i] = process[i][4] - process[i][1];
            // Update waiting time.
            process[i][5] = turnaround_time[i] - process[i][2];
            // Update total waiting time.
            total_waiting_time += process[i][5];
            // Set process status to complete.
            status[i] = 1;
          }
        }
      }
    }
    // Otherwise, increment the running time.
    else
    running_time++;
  }

  // Print the result.
  print_result_with_context("Round Robin", process, context, n, iterator, total_waiting_time);
}
