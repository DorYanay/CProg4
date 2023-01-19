#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;
;

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
    int distance;
    int visited;
    struct GRAPH_NODE_ *next;
} node, *pnode;

void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void printGraph_cmd(pnode head); // for self debug
void deleteGraph_cmd(pnode *head);
void TSP_cmd(pnode head);
pnode findVertex(pnode head, int v);
pnode newGraph(int Vnum);
void add_Edge(pnode headvertex, pnode lastvertex, int weight);
pnode init(pnode *head, int numNodes);
void freeCurrentEdges(pnode v);
pnode new_Node(pnode *head, int v);
int shortsPath_cmd(pnode head);
#endif