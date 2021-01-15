#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "fcfs.h"
#include "nsjf.h"
#include "file_reading.h"

#define MAX 100

int main()
{
  int process_values[MAX][6];
  int parameters[3];

  read_file(parameters, process_values);

  if(parameters[0] == 0)
  fcfs(process_values, parameters[1]);
  else if(parameters[0] == 1)
  nsjf(process_values, parameters[1]);
  // else if(parameters[0] == 2)
  // psjf(process_values, parameters[1]);
  // else if(parameters[0] == 3)
  // rr(process_values, parameters[1]);
  return 0;
}
