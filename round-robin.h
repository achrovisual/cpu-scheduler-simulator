#include <stdio.h>
#include <string.h>
#include "core.h"
#include "cpu_scheduling_core.h"

#define MAX_VAL 999

void roundRobin(int process[][6], int n, int quantum){
    //init pausedState storage
    int pausedStates[MAX_VAL][6];
    int burstTimes[MAX_VAL];
    int bProcessCompleted = 0;
    int pausedStateIterator = 0;
    int totWaiting = 0;
    for(int i = 0; i < MAX_VAL; i++){
        for(int j = 0; j < 6; j++){
            pausedStates[i][j] = 0;
        }
    }
    
    for(int i = 0; i < n; i++){
        burstTimes[i] = process[i][2];
    }

    for(int time = 0, i = 0, completedProcesses = 0; completedProcesses < n;){
        
        if(process[i][2] <= quantum && process[i][2] > 0){
            //time-leaping since burst time is <= quantum
            bProcessCompleted = 1;
            //set start time
            process[i][3] = time;
            //set end time 
            process[i][4] = time+=process[i][2];
            process[i][2] = 0;
            
        } else if(process[i][2] > 0){
            
            //set start time for current process
            process[i][3] = time;
            //remove quantum val from burst
            process[i][2] -= quantum;
            time+=quantum;
            
            //store paused states here
            //pausedStates[pausedStateIterator][0] = process[i][0];
            //pausedStates[pausedStateIterator][1] = process[i][3];
            //pausedStates[pausedStateIterator][2] = time;
            //pausedStateIterator++;
        }

        if(bProcessCompleted == 1 && process[i][2] == 0){
            //store wait time
            process[i][5] = time - process[i][1] - burstTimes[i];
            bProcessCompleted = 0;
            completedProcesses++;
        }

        if(i == n-1){
            i =0;
        } else if(process[i+1][1] <= time && i+1 < n){
            i++;
        } else {
            i = 0;
        }
    }

    //printing wala pa paused states tho + ala pa test cases
    for(int  i = 0; i < n; i++) {
        totWaiting = totWaiting + process[i][5];
        int bValid = 1;
        printf("[%d] Start time: %d End time: %d | Waiting time: %d\n", process[i][0], process[i][3], process[i][4], process[i][5]);
    }

    printf("Average waiting time: %.1f", (float)totWaiting / (float)n);
    printf("\n");
}