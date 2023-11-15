#include <stdio.h>
#include <stdlib.h>
#define MAX_V 20

const int MAX_EDG = (MAX_V)*(MAX_V-1)/2;

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

void get_edge_list(Graph* graph, EdgeList* edge_list) {
  for(int i=0; i < graph->size; i++) {
    Edge new_edge;
    for(int j=i+1; j < graph->size; j++) {
      if(*(graph->field + i*MAX_V + j)) {
        new_edge.from = i; new_edge.to = j;
        edge_list->list[edge_list->count++] = new_edge;
      }
    }
  }
}

void get_neighbors(Graph* graph, List neighbors_list[]) {
  for(int i=0; i < graph->size; i++) {
    List neighbors;
    neighbors.count = 0;
    for(int j=0; j < graph->size; j++) {
      if(*(graph->field + j + i*MAX_V)) {
        neighbors.list[neighbors.count++] = j;
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

void complementary_graph(Graph* graph, Graph* comp_graph) {
  for(int i=0; i < graph->size; i++) {
    for(int j=0; j < graph->size; j++) {
      if(i == j) continue;
      int value = *(graph->field + i*MAX_V + j);
      *(comp_graph->field + i*MAX_V + j) = !value;
    }
  }
}

void associated_graph(Graph* graph, Graph* ass_graph) {
  EdgeList edge_list;
  edge_list.count = 0;
  get_edge_list(graph, &edge_list);
  ass_graph->size = edge_list.count;

  for(int i = 0; i < edge_list.count; i++) {
    for(int j = i+1; j < edge_list.count; j++) {
      if(
        edge_list.list[i].from == edge_list.list[j].to ||
        edge_list.list[i].from == edge_list.list[j].from ||
        edge_list.list[i].to == edge_list.list[j].from ||
        edge_list.list[i].to == edge_list.list[j].to
      ) {
        *(ass_graph->field + i*MAX_V + j) = *(ass_graph->field + j*MAX_V + i) = 1;
      }
    }
  }
}

void dfs(Graph* graph, int vertex, int visited[]) {
  if(visited[vertex]) return; 

  visited[vertex] = 1;
  printf("%d ", vertex);

  for(int i=0; i < graph->size; i++) {
    int cur_v = *(graph->field + vertex*MAX_V + i);
    if(cur_v && !visited[i]) 
      dfs(graph, i, visited);
  }
}

void bfs(Graph* graph, int vertex) {
  // initialization
  int visited[MAX_V] = {0};
  int queue[(int)(MAX_V*1.5)] = {0};
  int st = 0, dr = 0;
  // algorithm 
  visited[vertex] = 1;
  queue[0] = vertex;
  while(st <= dr) {
    for(int i=0; i < graph->size; i++) {
      int cur_v = *(graph->field + queue[st]*MAX_V + i);
      if(cur_v && !visited[i]) {
        queue[++dr] = i;
        visited[i] = 1;
      }
    }
    printf("%d ", queue[st++]);
  }
}

void import_graph(Graph* graph, FILE* fptr) {
  char str[1];

  while(fgets(str, 2, fptr)) {
    if(*str == ' ') continue;
    if(*str == '\n') graph->size++;
  }

  rewind(fptr); // Resets fgets
  
  for(int i=0; i < graph->size; i++) {
    for(int j=0; j < graph->size; j++) {
      fgets(str, 2, fptr);
      while(*str == ' ' || *str == '\n') fgets(str, 2, fptr);
      int value = atoi(str);
      *(graph->field + i*MAX_V + j) = value;
    }
  }
}

void export_graph(Graph* graph, FILE* fptr) {
  for(int i=0; i < graph->size; i++) {
    for(int j=0; j < graph->size; j++) {
      int value = *(graph->field + i*MAX_V + j);
      fprintf(fptr, "%d ", value);
    }
    fprintf(fptr, "\n");
  }
}

int main() {
  // Initializing
  int static_graph[MAX_V][MAX_V] = {{0}};
  Graph graph;
  graph.field = (int*) static_graph;
  graph.size = 0;

  FILE *fptr;
  fptr = fopen("graph.in", "r");
  
  // fill graph
  import_graph(&graph, fptr);
  fclose(fptr);

  printf("Graph: \n");
  print(&graph);

  // Task 1
  List neighbors_list[graph.size];
  EdgeList edges_list;
  edges_list.count = 0;
  
  get_edge_list(&graph, &edges_list);

  printf("Edges: \n");
  for(int i =0; i < edges_list.count; i++)  {
    printf("(%d-%d)\n", edges_list.list[i].from, edges_list.list[i].to);
  }

  get_neighbors(&graph, neighbors_list);

  printf("Neighbors: \n");
  for(int i=0; i < graph.size; i++ ) {
    List neighbors = neighbors_list[i];
    printf("%d: ", i);
    for(int j = 0; j < neighbors.count; j++) {
      printf("%d ", neighbors.list[j]);
    }
    printf("\n");
  }

  // Task 2
  int vertex[] = {1, 0, 0, 1, 0};
  add_vertex(&graph, (int*) vertex);

  printf("Graph + vertex: \n");
  print(&graph);

  // Task 3
  remove_vertex(&graph, 5);

  printf("Graph - vertex: \n");
  print(&graph);

  // Task 4
  Edge edge1;
  edge1.from = 2;
  edge1.to = 3;

  add_edge(&graph, &edge1);

  printf("Graph + edge: \n");
  print(&graph);

  // Task 5
  Edge edge2;
  edge2.from = 2;
  edge2.to = 3;

  remove_edge(&graph, &edge2);

  printf("Graph - edge: \n");
  print(&graph);

  // Task 6
  int static_comp_graph[MAX_V][MAX_V] = {{0}};
  Graph comp_graph;
  comp_graph.field = (int*) static_comp_graph;
  comp_graph.size = graph.size;
  complementary_graph(&graph, &comp_graph);

  printf("Complementary Graph: \n");
  print(&comp_graph);
 
  // Task 7
  int ass_graph_static[MAX_EDG][MAX_EDG] = {{0}};
  Graph ass_graph;
  ass_graph.field = (int*) ass_graph_static;
  ass_graph.size = 0;
   
  printf("Associated Graph: \n");
  associated_graph(&graph, &ass_graph);
  print(&ass_graph);

  // Task 8
  int visited[MAX_V] = {0};
  printf("DFS: \n");
  dfs(&graph, 0, visited);

  // Task 9
  printf("\nBFS: \n");
  bfs(&graph, 0);

  // Export 
  fptr = fopen("graph.out", "w");
  export_graph(&graph, fptr);
  fclose(fptr);

  return 0;
}
