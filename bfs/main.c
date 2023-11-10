#include <stdio.h>
#include <stdlib.h>

// Cell & methods
typedef struct Cell {
  int value;
  int row;
  int col;
} Cell;

Cell createCell(int value, int row, int col) {
  Cell cell;
  cell.value = value;
  cell.row = row;
  cell.col = col;
  return cell;
}

// Grid & methods
typedef struct Grid {
  Cell* first_cell;
  int rows;
  int cols;
} Grid;

Cell* get_cell_at(Grid* grid, int row, int col) {
  return grid->first_cell + col + row*grid->cols;
}

int get_grid_size(Grid* grid) {
  return grid->rows * grid->cols;
}

void print_grid(Grid* grid) {
  for(int i=0; i < grid->rows; i++) {
    for(int j=0; j < grid->cols; j++) {
      Cell* cell = grid->first_cell + j + (i*grid->cols);
      printf("%d ", cell->value);
    }
    printf("\n");
  }
}

void parse_file(Grid* grid, FILE* fptr) {
  char str[1];
  int rows = 0, cols = 0;

  while(fgets(str, 2, fptr)) {
    if(*str == ' ') continue;
    if(*str == '\n') rows++;
    if(!rows) cols++;
  }
  
  rewind(fptr); // Resets fgets

  grid->rows = rows;
  grid->cols = cols;

  grid->first_cell = (Cell*) malloc(sizeof(Cell) * get_grid_size(grid));
  
  int i = 0;
  int row = 0, col = 0;
  while(fgets(str, 2, fptr)) {
    if(*str == ' ' || *str == '\n') continue; 

    int value = atoi(str);
    grid->first_cell[i] = createCell(value, row, col);
    col++;
    
    // Row/Col counter
    if(col >= cols) row++, col = 0;
    i++;
  }
}

// Linked list implementation
typedef struct Node {
  Cell* cell;
  struct Node* next;
} Node;

typedef struct LinkedList {
  Node* head;
} LinkedList;

void print_list(LinkedList* list) {
  Node* head = list->head;

  while(head != NULL) {
    printf("(%dx%d:%d) ", head->cell->row, head->cell->col, head->cell->value);
    head = head->next;
  }
}

void push_list(LinkedList* list, Cell* cell) {
  Node* new_node = (Node*) malloc(sizeof(Node));
  new_node->cell = cell;

  if(list->head == NULL) {
    list->head = (Node*) malloc(sizeof(Node));
    list->head = new_node;
    return;
  }

  Node* head = list->head;
  while(head->next != NULL) {
    head = head->next;
  }
  head->next = new_node;
}

Cell* pop_list(LinkedList* list) {
  Cell* first = list->head->cell;
  Node* head = list->head;
  list->head = list->head->next;
  return first;
}

int len_list(LinkedList* list) {
  Node* head = list->head;
  if(head == NULL) return 0;

  int length = 1;
  while(head->next != NULL) {
    head = head->next;
    length++;
  }
  return length;
}

// Position validator
int is_pos_valid(Grid* grid, int row, int col) {
  return !(
    (row < 0) ||
    (row >= grid->rows) ||
    (col < 0) ||
    (col >= grid->cols)
  );
}

// Neighbors getter
void get_neighbors(LinkedList* list, Grid* grid, Cell* cell, int start_val) {
  int indices[4][2] = {
    {cell->row-1, cell->col},
    {cell->row+1, cell->col},
    {cell->row, cell->col-1},
    {cell->row, cell->col+1}
  };

  for(int i=0; i < 4; i++) {
    if(!is_pos_valid(grid, indices[i][0], indices[i][1])) continue; 
    Cell* neighbor = get_cell_at(grid, indices[i][0], indices[i][1]);
    if(neighbor->value != start_val) continue;
    push_list(list, neighbor);
  }
}

// Actual algorithm
void flood_fill(Grid* grid, int row, int col, int p) {
  Cell* start = get_cell_at(grid, row, col);
  int start_val = start->value;
  int visited[grid->rows][grid->cols];

  // Fill array with 0s
  for(int i=0; i < grid->rows; i++) {
    for(int j=0; j < grid->cols; j++) {
      visited[i][j] = 0;
    }
  }

  // Initializing linked list
  LinkedList queue;
  queue.head = NULL;

  LinkedList neighbors;
  neighbors.head = NULL;

  push_list(&queue, start);
  while(len_list(&queue) > 0)  {
    Cell* first = pop_list(&queue);
    if(visited[first->row][first->col]) continue;

    first->value = p;
    visited[first->row][first->col] = 1;
    
    get_neighbors(&neighbors, grid, first, start_val);

    for(int i=0; i < len_list(&neighbors); i++) {
      Cell* neighbor = pop_list(&neighbors);
      if(visited[neighbor->row][neighbor->col]) continue;
      push_list(&queue, neighbor);
    }
  }
}

int main() {

  FILE *fptr;
  fptr = fopen("img.map", "r");
  
  Grid grid;

  parse_file(&grid, fptr);
  fclose(fptr);

  printf("Before:\n");
  print_grid(&grid);

  printf("Write row, col, fill_num\n");
  int row, col, p;
  scanf("%i%i%i", &row, &col, &p);
  
  // Algorithm
  flood_fill(&grid, row, col, p);

  printf("After:\n");
  print_grid(&grid);

  free(grid.first_cell);
  return 0;
}
