#ifndef GRAPH_
#define GRAPH_
#define infinity __INT_MAX__

typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_
{
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;

typedef struct GRAPH_NODE_
{
    int node_num;
    pedge edges;
    double distance;
    int visited;
    struct GRAPH_NODE_ *next;
} node, *pnode;
void helper(pnode head, int *arr, int k, int current, int *ans);
void swap(int *n, int i, int j);
void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void printGraph_cmd(pnode head); // for self debug
void deleteGraph_cmd(pnode *head);
void TSP_cmd(pnode head);
void add_Edge(pnode headvertex, pnode lastvertex, int weight);
void freeCurrentEdges(pnode v);
int shortsPath_cmd(pnode head, int v1, int v2);
int NumofVertices(pnode head);
pnode newGraph(int Vnum);
pnode findVertex(pnode head, int v);
pnode new_Node(pnode *head, int v);
pnode MinVisit(pnode head);
pedge findEdge(pnode head, int v1, int v2);

#endif