#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

const int ARR_LEN = 100;
// Utility
typedef struct Array {
  int* field;
  int len;
} Array;

typedef struct timeval Time;

double get_secs(Time start, Time stop) {
  return (stop.tv_usec - start.tv_usec) / 1000000.0 + stop.tv_sec - start.tv_sec;
}

double get_function_time(Array* arr, void (*caller)(Array*)) {
  Time start, stop;
  gettimeofday(&start, NULL);
  (*caller)(arr);
  gettimeofday(&stop, NULL);
  return get_secs(start, stop);
}

void fill_array(Array* arr) {
  srand(1);
  arr->field = (int*) calloc(arr->len, sizeof(int));
  for(int i = 0; i < arr->len; i++) {
    arr->field[i] = rand() % (arr->len*10);
  }
}

void print_arr(Array* arr) {
  printf("\n[ ");
  for(int i = 0; i < arr->len; i++) {
    printf("%d ", arr->field[i]);
  }
  printf("]\n");
}

// Sortings
void merge_sort() {}
void heap_sort() {}
void quick_sort() {}

void sort_merge(Array* arr) {
  // call merge sort
  print_arr(arr);
}

void sort_heap(Array* arr) {
  // call sort heap
  print_arr(arr);
}

void sort_quick(Array* arr) {
  // call quick sort
  print_arr(arr);
}

int main() { 
  Array quick_arr;
  quick_arr.len = ARR_LEN;
  fill_array(&quick_arr);
  printf("Quick Sort (%d): %f\n", quick_arr.len, get_function_time(&quick_arr, sort_quick));

  Array merge_arr;
  merge_arr.len = ARR_LEN;
  fill_array(&merge_arr);
  printf("Merge Sort (%d): %f\n", merge_arr.len, get_function_time(&merge_arr, sort_merge));
  
  Array heap_arr;
  heap_arr.len = ARR_LEN;
  fill_array(&heap_arr);
  printf("Heap Sort (%d):  %f\n", heap_arr.len, get_function_time(&heap_arr, sort_heap));

  return 0; 
}
