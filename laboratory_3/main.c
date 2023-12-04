#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// max - 2096336 (for my compiler)
const int ARR_LEN = 2000000;

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

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
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

// Quick Sort
void quick_sort(Array* arr, int left, int right) {
  if(left >= right) return;

  int left_val = arr->field[left];
  int k = left;

  for(int i = left+1; i <= right; i++) {
    if(arr->field[i] < left_val) {
      swap(&arr->field[i], &arr->field[++k]);
    }
  }
  swap(&arr->field[left], &arr->field[k]);
  quick_sort(arr, left, k-1);
  quick_sort(arr, k+1, right);
}

// Merge Sort
void merge(Array* arr, int left, int middle, int right)
{
  int left_len = middle - left + 1;
  int right_len = right - middle;

  int left_arr[left_len], right_arr[right_len];

  for (int i = 0; i < left_len; i++) left_arr[i] = arr->field[left + i];
  for (int j = 0; j < right_len; j++) right_arr[j] = arr->field[middle + 1 + j];

  int i = 0, j = 0, k = left;
  while (i < left_len && j < right_len) {
    if (left_arr[i] <= right_arr[j]) {
        arr->field[k++] = left_arr[i++];
    } else {
        arr->field[k++] = right_arr[j++];
    }
  }

  while (i < left_len) { arr->field[k++] = left_arr[i++]; }
  while (j < right_len) { arr->field[k++] = right_arr[j++]; }
}
 
void merge_sort(Array* arr, int left, int right) {
  if(left >= right) return;

  int middle = (left + right) / 2;

  merge_sort(arr, left, middle);
  merge_sort(arr, middle+1, right);

  merge(arr, left, middle, right);
}

// Heap Sort
void heapify(int arr[], int n, int i) {
    // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
  
    if (left < n && arr[left] > arr[largest])
      largest = left;
  
    if (right < n && arr[right] > arr[largest])
      largest = right;
  
    // Swap and continue heapifying if root is not largest
    if (largest != i) {
      swap(&arr[i], &arr[largest]);
      heapify(arr, n, largest);
    }
  }

void heap_sort(Array* arr) {
  // Build max heap
  for (int i = arr->len / 2 - 1; i >= 0; i--)
    heapify(arr->field, arr->len, i);

  // Heap sort
  for (int i = arr->len - 1; i >= 0; i--) {
    swap(&arr->field[0], &arr->field[i]);

    // Heapify root element to get highest element at root again
    heapify(arr->field, i, 0);
  }
}


// Callers
void sort_quick(Array* arr) {
  // call quick sort
  quick_sort(arr, 0, arr->len-1);
  // print_arr(arr);
}

void sort_merge(Array* arr) {
  // call merge sort
  merge_sort(arr, 0, arr->len-1);
}

void sort_heap(Array* arr) {
  // call sort heap
  heap_sort(arr);
  // print_arr(arr);
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
