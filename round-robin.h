#include <stdio.h>
#include <string.h>
#include "core.h"
#include "cpu_scheduling_core.h"

#define MAX_VAL 999

void roundRobin(int process[][6], int n, int quantum){
    //init pausedState storage
    int pausedStates[MAX_VAL][6];
    int burstTimes[MAX_VAL];
    int bTrack = 0;
    int pausedStateIterator = 0;
    int totWaiting = 0;
    int arrival = 0;
    int time = 0;
    //sort_array_by_index(n, 6, process, 1);

    for(int i = 0; i < MAX_VAL; i++){
        for(int j = 0; j < 6; j++){
            pausedStates[i][j] = 0;
        }
    }
    for(int i = 0; i < n; i++){
        burstTimes[i] = process[i][2];
    }

    for(int time = 0, completedProcess = 0, i = 0, quantumTracker = 0; completedProcess < n; time++){
        
        if(process[i][2] > 0 && process[i][1] <= time){
            process[i][2]--;
            bTrack = 1;
            quantumTracker++;
        } 
        
        if(process[i][2] == 0){
            completedProcess++;
            process[i][2] = 0;
            process[i][4] = time;
            process[i][5] = time - process[i][1] - burstTimes[i];
            quantumTracker = 0;
            bTrack = 1;
        }

        if(quantumTracker == quantum - 1){
            quantumTracker = 0;
        }

        if(bTrack == 1){
            bTrack = 0;
        } else {
            quantumTracker++;
        }

        if(i == n-1 && quantumTracker == 0){
            i = 0;
        } else if(i < n && quantumTracker == quantum - 1){
            i++;
        } else if(i < n && quantumTracker == 0){
            i++;
        } else if(i == n-1 && quantumTracker == quantum - 1){
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