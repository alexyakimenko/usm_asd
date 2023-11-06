#include <stdio.h>

typedef struct Graph {
  int field[5][5];
  int width;
} Graph;

int checked[5] = {0, 0, 0, 0, 0};

void dfs(Graph* graph, int vertex) {
  if(!checked[vertex]) {
    checked[vertex] = 1;
    printf("%d ", vertex);
    for(int i=0; i < graph->width; i++) {
      if(graph->field[vertex][i] && !checked[i]) 
        dfs(graph, i);
    }
  }
}

int main() {
  Graph graph;
  int graph_template[5][5] = {
    {0, 1, 0, 1, 1},
    {0, 0, 0, 1, 0},
    {0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
  };
  graph.width = 5;

  for(int i=0; i < graph.width; i++) {
    for(int j=0; j < graph.width; j++) {
      graph.field[i][j] = graph_template[i][j];
    }
  }

  dfs(&graph, 0);
  return 0;
}
