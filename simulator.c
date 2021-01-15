#include <stdio.h>
#include "fcfs.h"
#include "nsjf.h"

int main()
{
    int fcfs_n = 3;

    int fcfs_processes[3][6] = {
      {0, 0, 24, 0, 0, 0},
      {1, 0, 3, 0, 0, 0},
      {2, 0, 3, 0, 0, 0}
    };

    printf("FCFS\n");
    fcfs(fcfs_processes, fcfs_n);

    printf("\n\n");

    int nsjf_n = 5;

    int nsjf_processes[5][6] = {
      {1, 2, 6, 0, 0, 0},
      {2, 5, 2, 0, 0, 0},
      {3, 1, 8, 0, 0, 0},
      {4, 0, 3, 0, 0, 0},
      {5, 4, 4, 0, 0, 0}
    };

    printf("NSJF\n");
    nsjf(nsjf_processes, nsjf_n);

    return 0;
}
