#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Utility
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void print(int *arr, int n) {
  printf("[ ");
  for(int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("]\n");
}

void fill_arr(int *arr, int n) {
  for(int i = 0; i < n; i++) {
    arr[i] = rand();
  }
}

double get_secs(struct timeval start, struct timeval stop) {
  return (stop.tv_usec - start.tv_usec) / 1000000.0 + stop.tv_sec - start.tv_sec;
}

// Sorts
void bubble_sort(int *arr, int n) {
  for(int i = 0; i < n-1; i++) {
    for(int j = 0; j < n - i - 1; j++) {
      if(arr[j] > arr[j+1]) {
        swap(&arr[j], &arr[j+1]);
      }
    }
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
    while(arr[index] < arr[index-1]) {
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
  double dif;

  int num = 100000;

  int bubble[num];
  int selection[num];
  int insertion[num];
  int fast_insertion[num]; 

  fill_arr(bubble, num);
  fill_arr(selection, num);
  fill_arr(insertion, num);
  fill_arr(fast_insertion, num);

  // Bubble Sort
  gettimeofday(&start, NULL);
  bubble_sort(bubble, num);
  gettimeofday(&stop, NULL);
  printf("Bubble: %f\n", get_secs(start, stop));

  // Insertion Sort
  gettimeofday(&start, NULL);
  insertion_sort(insertion, num);
  gettimeofday(&stop, NULL);
  printf("Insertion: %f\n", get_secs(start, stop));
  
  // Selection Sort
  gettimeofday(&start, NULL);
  selection_sort(selection, num);
  gettimeofday(&stop, NULL);
  printf("Selection: %f\n", get_secs(start, stop));
  
  // Fast Insertion Sort
  gettimeofday(&start, NULL);
  fast_insertion_sort(fast_insertion, num);
  gettimeofday(&stop, NULL);
  printf("Fast Insertion: %f\n", get_secs(start, stop));

  return 0;
}
