#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    printf("D: \n");
    printGraph_cmd(*head);
}
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
        while ((letter = scanf("%d", &lv)))
        {
            nextv = findVertex(*head, lv);
            scanf("%d", &weight);
            add_Edge(curr, nextv, weight);
        }
        Vnum--;
    }
    printGraph_cmd(*head);
}
