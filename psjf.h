#define MAX_VAL 999

void psjf_calculate_waiting_time(int process[][6], int n, int paused_states[][6], int *iterator)
{
  int n_process = n;

  int remaining_time[101], first_pass[101];
  for(int i = 0; i < n; i++){
    first_pass[i] = 1;
  }

  for(int i = 0; i < n; i++){
    remaining_time[i] = process[i][2];
  }

  int completed_process = 0, time = 0, smallest_burst_index = 101, min = MAX_VAL;
  int check = 0;
  *iterator = 0;
  while(completed_process != n_process){

    for(int j = 0; j < n_process; j++){
      if((process[j][1] <= time) && (remaining_time[j]  < min) && remaining_time[j] > 0){
        if(first_pass[j] == 1){
          paused_states[(*iterator)][0] =  process[smallest_burst_index][0];
          paused_states[(*iterator)][3] =  process[smallest_burst_index][3];
          paused_states[(*iterator)][4] =  time;
          paused_states[(*iterator)][5] = min;
          (*iterator)++;
        }

        min = remaining_time[j];
        check = 1;
        process[j][3] = time;
        first_pass[j] = 0;
        smallest_burst_index = j;
      }
    }

    if(check == 0){
      time++;
      continue;
    }

    remaining_time[smallest_burst_index]--;
    min = remaining_time[smallest_burst_index];

    if(min==0){
      min = MAX_VAL;
    }

    if(remaining_time[smallest_burst_index] == 0){
      completed_process++;
      check = 1;

      process[smallest_burst_index][4] = time + 1;

      process[smallest_burst_index][5] = process[smallest_burst_index][4] -
      process[smallest_burst_index][2] - process[smallest_burst_index][1];

      if(process[smallest_burst_index][5] < 0){
        process[smallest_burst_index][0] = 0;
      }
    }

    time++;

  }
}

void psjf(int process[][6], int n){
  int time = 0, completed_process = 0, n_process = n;
  int total_waiting_time = 0;
  int smallest_burst_index = 101;
  int paused_states[100][6];
  process[100][2] = MAX_VAL;
  int iterator = 0;

  psjf_calculate_waiting_time(process, n, paused_states, &iterator);

  //index 0 = PID; index 1 = arrival; index 2 = burst; index 3 = start; index 4 = end; index 5 = wait
  for(time = 0; completed_process != n_process; time++){
    smallest_burst_index = 100;
    for(int i = 0; i < n_process; i++){
      if(process[i][1] <= time && process[i][2] < process[smallest_burst_index][2] && process[i][2] > 0){
        smallest_burst_index = i;
      }
    }

    process[smallest_burst_index][2]--;

    if(process[smallest_burst_index][2] == 0){
      completed_process++;
    }
  }

  printf("Preemptive Shortest Job First\n");
  //remove non-unique paused start time
  for(int i = 0; i < iterator; i++){
    for(int j = 0; j < n; j++){
      if(paused_states[i][3] == process[j][3]){
        //shift
        for(int k = j; k < iterator; k++){
          paused_states[k][0] = paused_states[k + 1][0];
          paused_states[k][1] = paused_states[k + 1][1];
          paused_states[k][2] = paused_states[k + 1][2];
          paused_states[k][3] = paused_states[k + 1][3];
          paused_states[k][4] = paused_states[k + 1][4];
          paused_states[k][5] = paused_states[k + 1][5];
        }
        iterator--;
      }
    }
  }

  for(int  i = 0; i < n; i++) {
    total_waiting_time = total_waiting_time + process[i][5];
    int is_valid = 1;
    for(int j = 0; j < iterator; j++){
      if(process[i][0] == paused_states[j][0] && process[i][3] != paused_states[j][3]){
        if(is_valid == 1){
          printf("[%d] Start time: %d End time: %d | ", paused_states[i][0], paused_states[i][3], paused_states[i][4]);
        } else {
          printf("Start time: %d End time: %d | ",  paused_states[i][3], paused_states[i][4]);
        }

        is_valid = 0;
      }
    }
    if(is_valid == 1){
      printf("[%d] Start time: %d End time: %d | Waiting time: %d\n", process[i][0], process[i][3], process[i][4], process[i][5]);
    } else {
      printf("Start time: %d End time: %d | Waiting time: %d\n",  process[i][3], process[i][4], process[i][5]);
    }

  }

  printf("Average waiting time: %.1f", (float)total_waiting_time / (float)n);
  printf("\n");
}
