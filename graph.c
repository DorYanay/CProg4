#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "graph.h"

void add_Edge(pnode headvertex, pnode lastvertex, int weight)
{
    pedge newEdge = (pedge)malloc(sizeof(edge));
    if (!newEdge)
    {
        return;
    }
    newEdge->weight = weight;
    newEdge->endpoint = lastvertex;
    newEdge->next = headvertex->edges;
    headvertex->edges = newEdge;
}
pnode newGraph(int Vnum)
{
    pnode first = (pnode)malloc(sizeof(node));
    if (!first)
    {
        return NULL;
    }
    first->node_num = Vnum - 1;
    first->edges = NULL;
    first->next = NULL;

    for (int i = 1; i < Vnum; i++)
    {
        pnode newNode = (pnode)malloc(sizeof(node));
        if (!newNode)
        {
            return NULL;
        }
        newNode->node_num = Vnum - i - 1;
        newNode->edges = NULL;
        newNode->next = first;
        first = newNode;
    }
    return first;
}
void printGraph_cmd(pnode head)
{
    if (head == NULL)
    {
        printf("NO GRAPH\n");
    }
    pnode temp = head;
    pedge edge1;
    while (temp)
    {
        edge1 = temp->edges;
        printf("Edges of %d:\n", temp->node_num);
        while (edge1)
        {
            printf("V:%d, E:%d W:%d\n", temp->node_num, edge1->endpoint->node_num, edge1->weight);
            edge1 = edge1->next;
        }
        temp = temp->next;
    }
}
pnode new_Node(pnode *head, int v)
{
    pnode vertex = (pnode)malloc(sizeof(node));
    if (!vertex)
    {
        return NULL;
    }
    vertex->node_num = v;
    vertex->edges = NULL;
    vertex->next = *head;
    *head = vertex;
    return vertex;
}
pnode findVertex(pnode head, int v)
{
    while (head)
    {
        if (head->node_num == v)
        {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

void deleteGraph_cmd(pnode *head)
{
    pnode temp = *head;
    pedge edge1 = NULL;
    pnode timo = NULL;
    while (temp)
    {
        edge1 = temp->edges;
        while (edge1)
        {
            pedge ted = edge1;
            edge1 = edge1->next;
            free(ted);
        }
        timo = temp;
        temp = temp->next;
        free(timo);
    }
}
// D
void delete_node_cmd(pnode *head)
{
    int v = 0;
    scanf("%d", &v);
    pnode temp = *head;
    pnode vert = NULL;
    pnode prever = NULL;
    while (temp)
    {
        if (temp->node_num == v)
        {
            vert = temp;
            break;
        }
        prever = temp;
        temp = temp->next;
    }
    if (vert == NULL)
    {
        return;
    }
    temp = *head;
    pedge yev = NULL;
    pedge yevprev = NULL;
    while (temp)
    {
        yev = temp->edges;
        while (yev)
        {
            if (yev->endpoint->node_num == v)
            {
                if (yevprev == NULL)
                {
                    temp->edges = yev->next;
                }
                else
                {
                    yevprev->next = yev->next;
                }
                free(yev);
                break;
            }
            yevprev = yev;
            yev = yev->next;
        }
        temp = temp->next;
    }
    pedge ed = vert->edges;
    pedge edtemp = NULL;
    while (ed)
    {
        edtemp = ed;
        ed = ed->next;
        free(edtemp);
    }
    if (prever == NULL)
    {
        *head = vert->next;
    }
    else
    {
        prever->next = vert->next;
    }
    free(vert);
    // printf("D: \n");
    // printGraph_cmd(*head);
}
int NumofVertices(pnode head)
{
    int count = 0;
    pnode current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}
pedge findEdge(pnode head, int v1, int v2)
{
    pnode current = head;
    while (current != NULL)
    {
        if (current->node_num == v1)
        {
            pedge edge = current->edges;
            while (edge != NULL)
            {
                if (edge->endpoint->node_num == v2)
                {
                    return edge;
                }
                edge = edge->next;
            }
        }
        current = current->next;
    }
    // if there is no edge between v1 and v2
    return NULL;
}

void freeCurrentEdges(pnode v)
{
    pedge vedge = v->edges;
    while (vedge)
    {
        pedge temp = vedge;
        vedge = vedge->next;
        free(temp);
    }
    v->edges = NULL;
}
// B
void insert_node_cmd(pnode *head)
{
    int v = 0;
    pnode nextvertex = NULL;
    int lastv = 0;
    int res = 0;
    int weight = 0;
    scanf("%d", &v);
    pnode temp = findVertex(*head, v);
    if (temp != NULL)
    {
        freeCurrentEdges(temp);
    }
    else
    {
        temp = new_Node(head, v);
    }
    while ((res = scanf("%d", &lastv)) && !feof(stdin))
    {
        nextvertex = findVertex(*head, lastv);
        scanf("%d", &weight);
        add_Edge(temp, nextvertex, weight);
    }
    // printGraph_cmd(*head);
}
// A
void build_graph_cmd(pnode *head)
{
    deleteGraph_cmd(head);
    int Vnum = 0;
    scanf("%d", &Vnum);
    if (Vnum == 0)
    {
        return;
    }
    *head = newGraph(Vnum);
    pnode curr;
    pnode nextv;
    int lv = 0, v = 0, letter = 0, weight = 0;
    char n;
    while (Vnum)
    {
        scanf(" %c", &n);
        scanf("%d", &v);
        curr = findVertex(*head, v);
        while ((letter = scanf("%d", &lv)) && !feof(stdin))
        {
            nextv = findVertex(*head, lv);
            scanf("%d", &weight);
            add_Edge(curr, nextv, weight);
        }
        Vnum--;
    }
    // printGraph_cmd(*head);
}
// S
int shortsPath_cmd(pnode head, int v1, int v2)
{
    pnode start = NULL;
    pnode end = NULL;
    pnode current = head;

    // resetting visiting and saving start and end
    while (current)
    {
        current->distance = infinity;
        current->visited = 0;
        if (current->node_num == v1)
        {
            start = current;
            start->distance = 0;
        }
        else if (current->node_num == v2)
        {
            end = current;
        }
        current = current->next;
    }

    current = start;
    while (current)
    {
        current->visited = 1;
        pedge currentNE = current->edges;
        while (currentNE)
        {
            if (!currentNE->endpoint->visited && current->distance + currentNE->weight < currentNE->endpoint->distance)
            {
                currentNE->endpoint->distance = current->distance + currentNE->weight;
            }
            currentNE = currentNE->next;
        }
        current = MinVisit(head);
    }
    if (end->distance == infinity)
    {
        end->distance = -1;
    }
    return end->distance;
}
pnode MinVisit(pnode head)
{
    int mindistance = infinity;
    pnode minvisit = NULL;
    while (head)
    {
        // checking if vertice has been visited
        if (head->visited == 0 && head->distance < mindistance)
        {
            // updating the new mindistance and head.
            mindistance = head->distance;
            minvisit = head;
        }
        head = head->next;
    }
    return minvisit;
}

// T
void swap(int *arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[i];
    arr[j] = tmp;
}

void check(pnode head, int *arr, int k, int current, int *ans)
{
    // if there are only two vertices
    if (k == 2)
    {
        int distance = shortsPath_cmd(head, arr[0], arr[1]);
        if (distance != -1 && (current + distance) < *ans)
        {
            *ans = (current + distance);
        }
        return;
    }

    // check other paths recursively
    for (int i = 1; i < k; i++)
    {
        swap(arr, 1, i);
        int distance2 = shortsPath_cmd(head, arr[0], arr[1]);
        if (distance2 == -1)
        {
            return;
        }
        check(head, arr + 1, k - 1, current + distance2, ans);
        swap(arr, i, 1);
    }
}

void TSP_cmd(pnode head)
{
    // getting input and inserting number to an array
    int k;
    scanf("%d", &k);
    int *arr = (int *)(malloc(sizeof(int) * k));
    int ans = infinity;
    for (int i = 0; i < k; i++)
    {
        scanf("%d", &arr[i]);
    }

    // checking every possible vertex to start from
    for (int i = 0; i < k; i++)
    {
        swap(arr, 0, i);
        check(head, arr, k, 0, &ans);
        swap(arr, i, 0);
    }

    if (ans == infinity)
    {
        ans = -1;
    }
    free(arr);
    printf("TSP shortest path: %d \n", ans);
}