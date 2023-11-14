#include <stdio.h>
#define MAX_V 20

typedef struct Graph {
  int* field;
  int size;
} Graph;

typedef struct List {
  int list[MAX_V];
  int count;
} List;

typedef struct Edge {
  int from;
  int to;
} Edge;

typedef struct EdgeList {
  Edge list[MAX_V*(MAX_V-1)];
  int count;
} EdgeList;

void print(Graph* graph) {
  for(int i=0; i < graph->size; i++) {
    for(int j=0; j < graph->size; j++) {
      printf("%2d", *(graph->field + j + i*MAX_V));
    }
    printf("\n");
  }
}

void get_edg_neigh(Graph* graph, List neighbors_list[], EdgeList* edges_list) {
  for(int i=0; i < graph->size; i++) {
    List neighbors;
    neighbors.count = 0;

    for(int j=0; j < graph->size; j++) {
      Edge new_edge;
      if(*(graph->field + j + i*MAX_V)) {
        neighbors.list[neighbors.count++] = j;
        if(j<=i) continue; // If Undirected graph
        new_edge.from = i; new_edge.to = j;
        edges_list->list[edges_list->count++] = new_edge;
      }
    }
    neighbors_list[i] = neighbors;
  }
}

void add_vertex(Graph* graph, int* vertex) {
  for(int i=0; i < graph->size; i++) {
    // Directed graph
    *(graph->field + (graph->size)*MAX_V + i) = *(vertex + i);
    // Undirected graph;
    *(graph->field + graph->size + MAX_V*i) = *(vertex + i);
  }
  graph->size++;
}

void remove_vertex(Graph* graph, int vertex_n) {
  for(int i = 0; i < graph->size; i++) {
    for(int j = vertex_n; j < graph->size; j++) {
      *(graph->field + i*MAX_V + j) = *(graph->field + i*MAX_V + j+1);
    }
  }
  for(int i = 0; i < graph->size; i++) {
    for(int j = vertex_n; j < graph->size; j++) {
      *(graph->field + j*MAX_V + i) = *(graph->field + (j+1)*MAX_V + i);
    }
  }
  graph->size--;
}

void add_edge(Graph* graph, Edge* edge) {
  // Directed graph
  *(graph->field + edge->from*MAX_V + edge->to) = 1;
  // Undirected graph
  *(graph->field + edge->to*MAX_V + edge->from) = 1;
}

void remove_edge(Graph* graph, Edge* edge) {
  // Directed graph
  *(graph->field + edge->from*MAX_V + edge->to) = 0;
  // Undirected graph
  *(graph->field + edge->to*MAX_V + edge->from) = 0;
}

void complementary_graph(Graph* graph) {
  for(int i=0; i < graph->size; i++) {
    for(int j=0; j < graph->size; j++) {
      if(i == j) continue;
      int value = *(graph->field + i*MAX_V + j);
      *(graph->field + i*MAX_V + j) = !value;
    }
  }
}


void dfs(Graph* graph, int vertex, int checked[]) {
  if(!checked[vertex]) {
    checked[vertex] = 1;
    printf("%d ", vertex+1);
    for(int i=0; i < graph->size; i++) {
      if(*(graph->field + i) && !checked[i]) 
        dfs(graph, i, checked);
    }
  }
}
int main() {
  // Initializing
  int graph_static[MAX_V][MAX_V] = {{0}};
  int init_graph[4][4] = {
    {0, 1, 0, 1},
    {1, 0, 1, 0},
    {0, 1, 0, 0},
    {1, 0, 0, 0},
  };
  for(int i=0; i < 4; i++) {
    for(int j=0; j < 4; j++) {
      graph_static[i][j] = init_graph[i][j];
    }
  }
  Graph graph;
  graph.field = (int*) graph_static;
  graph.size = 4;

  printf("Graph: \n");
  print(&graph);

  // Task 1
  List neighbors_list[graph.size];
  EdgeList edges_list;
  edges_list.count = 0;

  get_edg_neigh(&graph, neighbors_list, &edges_list);
  
  printf("Neighbors: \n");
  for(int i=0; i < graph.size; i++ ) {
    List neighbors = neighbors_list[i];
    printf("%d: ", i+1);
    for(int j = 0; j < neighbors.count; j++) {
      printf("%d ", neighbors.list[j]+1);
    }
    printf("\n");
  }
  printf("Edges: \n");
  for(int i =0; i < edges_list.count; i++)  {
    printf("(%d-%d)\n", edges_list.list[i].from+1, edges_list.list[i].to+1);
  }
  // Task 2
  int vertex[] = {1, 0, 0, 1};

  add_vertex(&graph, (int*) vertex);

  printf("Graph + vertex: \n");
  print(&graph);

  // Task 3
  remove_vertex(&graph, 1);

  printf("Graph - vertex: \n");
  print(&graph);

  // Task 4
  Edge edge1;
  edge1.from = 1;
  edge1.to = 3;

  add_edge(&graph, &edge1);

  printf("Graph + edge: \n");
  print(&graph);
  // Task 5
  Edge edge2;
  edge2.from = 0;
  edge2.to = 2;

  remove_edge(&graph, &edge2);

  printf("Graph - edge: \n");
  print(&graph);

  // Task 6
  complementary_graph(&graph);

  printf("Complementary Graph: \n");
  print(&graph);
  
  // Task 7
  
  // Task 8
  int checked[graph.size];
  for(int i=0; i < graph.size; i++) checked[i] = 0;
  
  printf("DFS: \n");
  dfs(&graph, 0, checked);

  return 0;
}
