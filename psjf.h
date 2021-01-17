#include <stdio.h>
#define MAX_VAL 999
void psjfWaitTime(int process[][6], int n, int pausedStates[][6], int *psIter) 
{ 
    int numProcesses = n;

    int remainingTime[101], firstPass[101];
    for(int i = 0; i < n; i++){
        firstPass[i] = 1;
    }

    for(int i = 0; i < n; i++){
        remainingTime[i] = process[i][2];

    }

    int completedProcess = 0, time = 0, smallestBurstIndex = 101, minVal = MAX_VAL;
    int bCheck = 0;
     *psIter = 0;
    while(completedProcess != numProcesses){

        for(int j = 0; j < numProcesses; j++){
            if((process[j][1] <= time) && (remainingTime[j]  < minVal) && remainingTime[j] > 0){
                
                if(firstPass[j] == 1){
                    printf("[%d] Start time: %d End time: %d | Wait: %d\n", process[smallestBurstIndex][0], process[smallestBurstIndex][3], time, process[smallestBurstIndex][5]);
                   pausedStates[(*psIter)][0] =  process[smallestBurstIndex][0];
                   pausedStates[(*psIter)][3] =  process[smallestBurstIndex][3];
                   pausedStates[(*psIter)][4] =  time;
                   pausedStates[(*psIter)][5] = minVal;
                   (*psIter)++;
                }
                
                minVal = remainingTime[j];
                bCheck = 1;
                process[j][3] = time;
                firstPass[j] = 0;
                smallestBurstIndex = j;
            }
        }

        if(bCheck == 0){
            time++;
            continue;
        }

        remainingTime[smallestBurstIndex]--;
        minVal = remainingTime[smallestBurstIndex];

        if(minVal==0){
            minVal = MAX_VAL;
        }

        if(remainingTime[smallestBurstIndex] == 0){
            completedProcess++;
            bCheck = 1;

            process[smallestBurstIndex][4] = time + 1;

            process[smallestBurstIndex][5] = process[smallestBurstIndex][4] - 
                    process[smallestBurstIndex][2] - process[smallestBurstIndex][1];

            if(process[smallestBurstIndex][5] < 0){
                process[smallestBurstIndex][0] = 0;
            }
        }

        time++;

    }
} 

void psjf(int process[][6], int n){
    int time = 0, completedProcess = 0, numProcesses = n;
    int totWaiting = 0;
    float aveWaiting = 0;
    int smallestBurstIndex = 101;
    int pausedStates[100][6];
    process[100][2] = MAX_VAL;
    printf("%d\n\n\n", numProcesses);
    int psIter = 0;
    psjfWaitTime(process, n, pausedStates, &psIter);
    //index 0 = PID; index 1 = arrival; index 2 = burst; index 3 = start; index 4 = end; index 5 = wait
    for(time = 0; completedProcess != numProcesses; time++){
        smallestBurstIndex = 100;
        for(int i = 0; i < numProcesses; i++){
            if(process[i][1] <= time && process[i][2] < process[smallestBurstIndex][2] && process[i][2] > 0){
                smallestBurstIndex = i;
            }
        }

        process[smallestBurstIndex][2]--;

        printf("%d\n", smallestBurstIndex);
        printf("%d\n", completedProcess);
        if(process[smallestBurstIndex][2] == 0){
            completedProcess++;
            printf("%d\n", time);
        }
    }
 
    printf("Preemptive Shortest Job First\n");
    printf("Stored Paused States: %d\n", psIter);
    //remove non-unique paused start time
    for(int i = 0; i < psIter; i++){
        for(int j = 0; j < n; j++){
            if(pausedStates[i][3] == process[j][3]){
                //shift
                for(int k = j; k < psIter; k++){
                    pausedStates[k][0] = pausedStates[k+1][0]; 
                    pausedStates[k][1] = pausedStates[k+1][1]; 
                    pausedStates[k][2] = pausedStates[k+1][2]; 
                    pausedStates[k][3] = pausedStates[k+1][3]; 
                    pausedStates[k][4] = pausedStates[k+1][4]; 
                    pausedStates[k][5] = pausedStates[k+1][5]; 
                }
                psIter--;
            }
        }
    }

    for(int  i = 0; i < n; i++) {
        totWaiting = totWaiting + process[i][5];
        int bValid = 1;
        for(int j = 0; j < psIter; j++){
            if(process[i][0] == pausedStates[j][0] && process[i][3] != pausedStates[j][3]){
                printf("[%d] Start time: %d End time: %d | ", pausedStates[i][0], pausedStates[i][3], pausedStates[i][4]);
            }
        }
        printf("[%d] Start time: %d End time: %d | Waiting time: %d\n", process[i][0], process[i][3], process[i][4], process[i][5]);
    }

    printf("Average waiting time: %.1f", (float)totWaiting / (float)n);
    printf("\n");
}