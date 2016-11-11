#include <cstdio>
#include <cstdlib>
#include <queue>
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

  p->weight = 0;
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


/* BFS */
bool processed[MaxV+1];
bool discovered[MaxV+1];
int parent[MaxV+1];

int initialize_search(graph *g) {
  int i;

  for (i=1; i<=g->nVertices; i++) {
    processed[i] = discovered[i] = false;
    parent[i] = -1;
  }

  return 0;
};

int process_vertex_late(int v) {
  return 0;
};

int process_vertex_early(int v) {
  std::printf("processed vertex %d\n", v);
  return 0;
};

int process_edge(int x, int y) {
  std::printf("processed edge (%d, %d)\n", x, y);
  return 0;
};

int bfs(graph *g, int start) {
  std::queue <int> q;
  int v; /* Current vertex */
  int y; /* Successor vertex */
  edgenode *p;

  q.push(start);
  discovered[start] = true;

  while (q.empty() == false) {
    v = q.front();
    q.pop();
    process_vertex_early(v);
    processed[v] = true;
    p = g->edges[v];

    while (p != NULL) {
      y = p->y;

      if ((processed[y] == false) || g->directed) {
        process_edge(v, y);
      }

      if (discovered[y] == false) {
        q.push(y);
        discovered[y] = true;
        parent[y] = v;
      }

      p = p->next;
    }

    process_vertex_late(v);
  }
  return 0;
};

int find_path(int start, int end, int parents[]) {
  if ((start == end) || (end == -1)) {
    std::printf("\n%d", start);
  } else {
    find_path(start, parents[end], parents);
    std::printf(" %d", end);
  }
  return 0;
};

int main() {
  graph *g = read_graph(new graph, false);

  std::printf("Printing graph data from structure:\n");
  print_graph(g);

  std::printf("\n");

  std::printf("BFS algo: \n");
  bfs(g, 1);

  std::printf("\nShortest path from 1 to 4 is:");
  find_path(1, 4, parent);

  std::printf("\n");
  return 0;
};
