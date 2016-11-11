#include <cstdio>
#include <cstdlib>
#define MaxV 1000

struct edgenode {
  int y;
  int weight;
  edgenode *next; /* Adjacency Info */
};

struct graph{
  edgenode *edges[MaxV+1];  /* Adjacency Info */
  int degree[MaxV+1];       /* Outdegree of each vertex*/
  int nVertices;
  int nEdges;
  bool directed;
};

int initialize_graph(graph *g, bool directed) {
  int i;

  g->nVertices = 0;
  g->nEdges = 0;
  g->directed = directed;

  for (i=0; i<=MaxV; i++) g->degree[i] = 0;
  for (i=0; i<=MaxV; i++) g->edges[i] = NULL;

  return 0;
};

int insert_edge(graph *g, int x, int y, bool directed) {
  edgenode *p;
  p = (edgenode*)std::malloc(sizeof(edgenode));

  p->weight = NULL;
  p->y = y;
  p->next = g->edges[x];
  
  g->edges[x] = p;
  g->degree[x] ++;

  if (directed == false) {
    insert_edge(g, y, x, true);
  } else {
    g->nEdges ++;
  }

  return 0;
};

graph * read_graph(graph *g, bool directed) {
  int i;
  int m; /* number of edges */
  int x, y; /* vertices in edge (x,y) */
  FILE * pFile;

  initialize_graph(g, directed);

  pFile = std::fopen("graph-data.txt", "r");

  if (pFile != NULL) {
    std::fscanf(pFile, "%d %d", &(g->nVertices), &m); /* Put a value in g->nVertices and a value in m from first line of file */

    for (i=1; i<=m; i++) {
      std::fscanf(pFile, "%d %d", &x, &y); /* Put a value in x and a value in y from a line in the file */
      insert_edge(g, x, y, directed);
    }
  }

  std::fclose(pFile);
  return g;
}

int print_graph(graph *g) {
  int i;
  edgenode *p;

  for (i=1; i<=g->nVertices; i++) {
    std::printf("%d: ", i);
    p = g->edges[i];

    while (p != NULL) {
      std::printf(" %d", p->y);
      p = p->next;
    }
    std::printf("\n");
  }
  return 0;
};

int main() {
  graph *g = read_graph(new graph, false);
  print_graph(g);
  return 0;
};
