#include <stdio.h>
#include <stdlib.h>

// Cell & methods
typedef struct Cell {
  int value;
} Cell;

Cell createCell(int value) {
  Cell cell;
  cell.value = value;
  return cell;
}

// Grid & methods
typedef struct Grid {
  Cell* first_cell;
  int rows;
  int cols;
} Grid;

Cell* get_cell_at(Grid* grid, int row, int col) {
  return grid->first_cell + col + row*grid->rows;
}

int get_grid_size(Grid* grid) {
  return grid->rows * grid->cols;
}

void print_grid(Grid* grid) {
  for(int i=0; i < grid->rows; i++) {
    for(int j=0; j < grid->cols; j++) {
      Cell* cell = grid->first_cell + j + (i*grid->rows);
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
  while(fgets(str, 2, fptr)) {
    if(*str == ' ' || *str == '\n') continue;
    int value = atoi(str);
    grid->first_cell[i] = createCell(value);
    i++;
  }
}

void flood_fill(Grid* grid, int row, int col, int p) {

}

int main() {
  FILE *fptr;
  fptr = fopen("img.map", "r");

  Grid grid;

  parse_file(&grid, fptr);
  fclose(fptr);

  print_grid(&grid);

  free(grid.first_cell);
  return 0;
}
