/*
PROJECT TITLE: CPU Scheduling
COURSE: Introduction to Operating Systems
SECTION: S12
AUTHORS: Rafael Maderazo & Eugenio Pastoral
*/

#include "fcfs.h"
#include "nsjf.h"
#include "psjf.h"
#include "rr.h"
#include "file_reading.h"
#include "core.h"
#include "cpu_scheduling_core.h"

#define MAX 101

int main()
{
  int process_values[MAX][6];
  int parameters[3];

  char filename[256];

  printf("Enter the filename of the test case: ");
  scanf("%s", filename);

  // Get the values required from the indicated text file
  read_file(parameters, process_values, filename);

  // Run the simulation based on what scheduling algorithm is chosen
  if(parameters[0] == 0)
  fcfs(process_values, parameters[1]);
  else if(parameters[0] == 1)
  nsjf(process_values, parameters[1]);
  else if(parameters[0] == 2)
  psjf(process_values, parameters[1]);
  else if(parameters[0] == 3)
  rr(process_values, parameters[1], parameters[2]);

  return 0;
}
