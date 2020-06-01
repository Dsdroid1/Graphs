#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MAX_NO_OF_VERTICES 10
#define INF INT_MAX
//Using Adjacency List

typedef enum {FALSE,TRUE} Bool;
typedef enum {FAILURE,SUCCESS} status_code;
typedef enum {DIRECTED,UNDIRECTED} graph_type;


typedef struct GraphNode
{
    int NodeNumber;
    struct GraphNode *next;
    int weight;
}GraphNode;

typedef struct Graph
{
    int N;//No.of Vertices/Nodes
    struct GraphNode *EdgeList[MAX_NO_OF_VERTICES];
    Bool weighted;
    graph_type type;
}Graph;

//BAsic Structure definitions end here-----------------------

//Definition for queue---------------------------------------
typedef struct Q_element
{
    int data;
    struct Q_element *next;
}Q_element;

typedef struct Queue
{
    Q_element *front;
    Q_element *rear;
}Queue;

//Queue Functions
void InitQueue(Queue *Qptr);
status_code InsertQ(Queue *Qptr,int data);
status_code DeleteQ(Queue *Qptr,int *dptr);
Bool isQueueEmpty(Queue Q);

//Graph Construction
void InitGraph(Graph *G);
status_code AddNode(Graph *G);
status_code AddEdge(Graph *G,int start_vertex,int end_vertex,int weight);
status_code DeleteEdge(Graph *G,int start_vertex,int end_vertex);
status_code DeleteNode(Graph *G);//The latest added node can only be deleted
status_code ReadGraph(Graph *G,char *filename);

//Traversal Functions
void Traverse(int curr_vertex,Graph G,int Visited[MAX_NO_OF_VERTICES]);
void DFT(Graph G);
void BFT(Graph G);
status_code TopologicalSort(Graph G);

//Some other Functions
Bool isGraphConnected(Graph G);

//Algorithms
//------Dijkstra's Shortest Path
status_code DijkstraShortestPath(Graph G,int Vertex,int pathcost[MAX_NO_OF_VERTICES],int path[MAX_NO_OF_VERTICES]);//Will only work for positive edges 
void PrintPathCalculatedViaDijkstra(Graph G,int vertex,int pathcost[MAX_NO_OF_VERTICES],int path[MAX_NO_OF_VERTICES]);
//------All Pair Shortest Path
void PrintPathCalculatedViaAPSP(Graph G,int CostMatrix[MAX_NO_OF_VERTICES][MAX_NO_OF_VERTICES],int Path[MAX_NO_OF_VERTICES][MAX_NO_OF_VERTICES]);
void AllPairShortestPath(Graph G,int Path[MAX_NO_OF_VERTICES][MAX_NO_OF_VERTICES]);
//------Prim's Algorithm for MST
int MST(Graph G);//Requires some structuring of output
//------To detect a cycle
//Require a cover function
Bool isCycleInGraph(Graph G);//For directed
Bool isCycleInGraphVer2(Graph G);//For undirected
//------To calculate all possible paths between a pair of vertices
void FindPath(Graph G,int curr_vertex,int visited[MAX_NO_OF_VERTICES],int destination,int *pathlength,int path[MAX_NO_OF_VERTICES],Bool *atleastOnePath);
void PrintAllPossiblePaths(Graph G,int vertex_Start,int vertex_End);

//-----DFS and BFS
Bool Traverse2(int curr_vertex,Graph G,int Visited[MAX_NO_OF_VERTICES],int value_to_be_searched);
Bool DFS(Graph G,int value_to_be_searched);
Bool BFS(Graph G,int value_to_be_searched);

