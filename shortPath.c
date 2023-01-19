#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
int shortsPath_cmd(pnode head)
{
    int v1 = 0, v2 = 0;
    scanf("%d", &v1);
    scanf("%d", &v2);
    pnode vertex1 = findVertex(head, v1);
    pnode vertex2 = findVertex(head, v2);
    if (vertex1 == NULL || vertex2 == NULL)
    {
        printf("-1\n");
        return;
    }
    pnode start = NULL;
    pnode end = NULL;
    pnode curr = head;
    // Initializing

    while (curr)
    {
        curr->visited = 0;
        curr->distance = INFINITY;
        if (curr->node_num == v1)
        {
            start = curr;
            start->distance = 0;
        }
        else if (curr->node_num == v2)
        {
            end = curr;
        }
        curr = curr->next;
    }
}