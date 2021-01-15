#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STRING 900
#define MAX 100

int main(){
    FILE *fp;
    char string[MAX_STRING][MAX_STRING];
    int params[3];
    int processValues[MAX][3];
    int i = 0, j = 0, n = 0, errVal = 0, processNumbers = 0;
    int rowSize = 0;
    char* fileName = "./test.txt";
    char digiCheck;

    fp = fopen(fileName, "r");
    //open file
    if(fp == NULL){
        printf("File cannot be open: %s", fileName);
        return 1;
    }
    //read through file
    while(fgets(string[i], MAX_STRING, fp) != NULL){
        if(strlen(string[i]) - 1 == '\0'){
            string[i][strlen(string[i]) - 1] = ' ';
        }
        
        i++;
    }
    fclose(fp);
    rowSize = i;
    processNumbers = rowSize - 1;
    char* tokenized = strtok(string[0], " ");
    //convert first line to int
    while(tokenized){
        params[n++] = atoi(tokenized);
        tokenized = strtok(NULL, " ");
    }
    //validate parameters for the first line
    for(i = 0; i < 3; i++){
        if(i == 0 &&( params[i] > 3 || params[i] <  0)){
            errVal = 1;
        }
        if(i == 1 && params[i] < 3 && params[i] > 100){
            errVal = 1;
        }
        if(i == 2 && (params[i] < 1 || params[i] > 100) && params[0] == 3){
            errVal = 1;
        }
        if(processNumbers != params[1]){
            errVal = 1;
        }
    }
    if(errVal == 1){
        printf("An invalid parameter on the first line has been found.\n");
        return 0;
    }
    //convert the process values to int, store in 2d arr
    j = 0;
    for(i = 1; i < rowSize; i++){
        n = 0;
        
        char* tokenized = strtok(string[i], " ");
        while(tokenized){
            processValues[j][n++] = atoi(tokenized);
            tokenized = strtok(NULL, " ");
        }
        j++;
    }
    //validate process values
    for(i = 0; i < rowSize-1; i++){
        for(j = 0; j < 3; j++){
            if(processValues[i][j] < 0){
                errVal = 1;
            }
        }
    }
    if(errVal == 1){
        printf("A process time's parameter cannot have a negative value.\n");
        return 0;
    }
    //check if process id is unique
    for(i = 0; i < rowSize-1; i++){
        for(j = 0; j < rowSize - 1; j++){
            if(processValues[i][0] == processValues[j][0]){
                errVal = 1;
            }
        }
    }
    if(errVal == 1){
        printf("Process IDs cannot have the same value.\n");
        return 0;
    }

    printf("\n");
    return 0;
}