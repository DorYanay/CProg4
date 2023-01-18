#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main()
{
    char c = 0;
    // int result = 0;
    // int sourceNum = 0;
    // int destNum = 0;
    pnode head = NULL;
    while (!feof(stdin))
    {
        switch (c)
        {
        case 'A':
            build_graph_cmd(&head);
            break;
        // case 'B':
        //     insert_node_cmd(&head);
        //     break;
        case 'D':
            delete_node_cmd(&head);
            break;
        // case 'S':
        //     scanf("%d", &sourceNum);
        //     scanf("%d", &destNum);
        //     result = shortsPath_cmd(head, sourceNum, destNum);
        //     printf("Dijsktra shortest path: %d \n", result);
        //     break;
        case 'P':
            printGraph_cmd(head);
            break;
        // case 'T':
        //     TSP_cmd(head);
        //     break;
        default:
            break;
        }
        scanf(" %c", &c);
    }
    deleteGraph_cmd(&head);
    return 0;
}