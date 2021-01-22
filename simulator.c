#include "fcfs.h"
#include "nsjf.h"
#include "psjf.h"
#include "file_reading.h"
#include "round-robin.h"
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

  read_file(parameters, process_values, filename);

  if(parameters[0] == 0)
  fcfs(process_values, parameters[1]);
  else if(parameters[0] == 1)
  nsjf(process_values, parameters[1]);
  else if(parameters[0] == 2)
  psjf(process_values, parameters[1]);
  else if(parameters[0] == 3)
  roundRobin(process_values, parameters[1], parameters[2]);
  return 0;
}
