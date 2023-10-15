#include <stdio.h>
#include <sys/time.h>
#include <stdbool.h> // to get rid of 1 and 0 

// Utility
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int my_rand(int seed) {
  int sqr_seed = seed * seed;
  int result = sqr_seed / 10 + sqr_seed % 10000;
  if(result < 0) {
    result = -result;
  }
  return result;
}

void print(int *arr, int n) {
  printf("[ ");
  for(int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("]\n");
}

void fill_arr(int *arr, int n) {
  struct timeval time;
  gettimeofday(&time, NULL);

  int seed = my_rand(time.tv_usec);
  for(int i = 0; i < n; i++) {
    seed = my_rand(seed);
    arr[i] = my_rand(seed) % 10000;
  }
}

double get_secs(struct timeval start, struct timeval stop) {
  return (stop.tv_usec - start.tv_usec) / 1000000.0 + stop.tv_sec - start.tv_sec;
}

// Sorts
void bubble_sort(int *arr, int n) {
  for(int i = 0; i < n-1; i++) {
    for(int j = 0; j < n-1; j++) {
      if(arr[j] > arr[j+1]) {
        swap(&arr[j], &arr[j+1]);
      }
    }
  }
}

void fast_bubble_sort(int *arr, int n) {
  bool changes;
  for(int i = 0; i < n-1; i++) {
    changes = false;
    for(int j = 0; j < n-i-1; j++) {
      if(arr[j] > arr[j+1]) {
        swap(&arr[j], &arr[j+1]);
        changes = true;
      }
    }
    if(!changes) break;
  }
}

void selection_sort(int *arr, int n) {
  for(int i = 0; i < n-1; i++) {
    int min_i = i;
    for(int j = i+1; j < n; j++) {
      if(arr[j] < arr[min_i]) {
        min_i = j; 
      }
    }
    swap(&arr[i], &arr[min_i]);
  }
}

void insertion_sort(int *arr, int n) {
  for(int i = 1; i < n; i++) {
    int index = i;
    while(arr[index] < arr[index-1] && index > 0) {
      swap(&arr[index], &arr[index-1]);
      index -= 1;
    }
  }
}

void fast_insertion_sort(int *arr, int n) {
  for(int i = 1; i < n; i++) {
    if(arr[i] < arr[i-1]) {
      int start = 0, 
          end = i,
          mid = (start + end) / 2;

      while(!(arr[i] <= arr[mid] && arr[i] > arr[mid-1])) {
        mid = (start + end) / 2;
        if(arr[i] > arr[mid]) {
          start = mid;
        } else {
          end = mid;
        }
      }

      int temp = arr[i];
      
      for(int j = i; j > mid; j--) {
        arr[j] = arr[j-1];
      }

      arr[mid] = temp; 
    }
  }
}

int main() {
  struct timeval start, stop;

  int num = 100000;
  int example_array[num];
  fill_arr(example_array, num);

  gettimeofday(&start, NULL);
  selection_sort(example_array, num);
  gettimeofday(&stop, NULL);
  printf("Time dif: %f\n", get_secs(start, stop));

  return 0;
}
