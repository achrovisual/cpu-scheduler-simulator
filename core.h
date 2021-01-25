/*
AUTHOR: Eugenio Pastoral
*/

#include <stdio.h>

#ifndef CORE_H
#define CORE_H

/*
This function initializes an array with the value indicated.
*/
void initialize_array(int array[], int size, int value) {
  for(int i = 0; i < size; i++)
  array[i] = value;
}

/*
This function sorts a two-dimmensional array based on the specified column.
*/
void sort_array_by_index(int row, int column, int array[row][column], int index) {
  for(int i = 0; i < row; i++)
  for(int j = 0; j < row - i - 1; j++)
  if(array[j][index] > array[j + 1][index]) {
    for(int k = 0; k < column; k++) {
      int temp = array[j][k];
      array[j][k] = array[j + 1][k];
      array[j + 1][k] = temp;
    }
  }
}
#endif
