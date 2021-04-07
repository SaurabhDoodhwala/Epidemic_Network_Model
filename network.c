/*
 * CSE 6010 Assignment 6
 * Team: Sarah and Saurabh
 * Created by Saurabh
 * Last edited on 30 October 2020
 */

#include <stdlib.h>
#include <string.h>
#include "network.h"

/*
 * Function:  Search_Node
 * --------------------
 * Description:
 *      Function to search an element/neighbor in the adjacency list corresponding to any specific node
 * Parameters:
 *      list: We will provide the linked list which contains the elements/neighbors of specific node
 * 			  like adj_list[i] will contain neighbors of node i
 *      data: an integer value of the element to be searched
 * Returns:
 *      Will give value of the element itself if it's present in the list
 *      If the element is not present, it will return -1 (indicating element is not present)
 */
int Search_Node(adj_node *list, int data){

    //temp will go through whole list to search for the element

    adj_node *temp = (adj_node*)malloc(sizeof(adj_node*));
    //temp will start from first element
    temp = list->head;
    //while loop to search through whole list
    while (temp != NULL) {
        if (temp->vertex == data){
            return data;
        }
        temp = temp->next;
    }
    //return -1 if element not present
    return -1;
    free(temp);
}

/*
 * Function:  node_count
 * --------------------
 * Description:
 *      Function to count number of elements/nodes in the adjacency list corresponding to any specific node
 * Parameters:
 *      list: We will provide the linked list which contains the elements/neighbors of specific node
 * 			  like adj_list[i] will contain neighbors of node i
 * Returns:
 *      Will give an integer value greater than or equal to 0, which is count
 *      of elements in that specific adj_list[i] for node i
 */

unsigned int node_count(adj_node *list)
{
    //count to keep track of number of elements
    int count = 0;
    //temp will travel to every element through while loop and increase count value
    //when it passes through a new element

    adj_node *temp = (adj_node*)malloc(sizeof(adj_node*));

    //temp starts from first value
    temp = list->head;

    //while loop will run until NULL is reached
    while(temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
    free(temp);
}

// Frees all nodes in the given adjacency linked list.
void freeAll(adj_node *list)
{
    adj_node *toFree = list;
    adj_node *next = NULL;

    while(toFree != NULL)
    {
        next = toFree->next;
        free(toFree);
        toFree = next;
    }
}