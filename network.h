/*
 * CSE 6010 Assignment 6
 * Team: Sarah and Saurabh
 * Created by Saurabh
 * Last edited on 30 October 2020
 */

#ifndef NETWORK_H
#define NETWORK_H

#define numAgents 500
#define numIterations 100
#define numNearestNeighbors 10
#define pReplaceRandom 0.25


/*
	Basic linked-list struct for adjacency list representation of the network
    Each struct will represent a node in our network
    The nodes will be connected via a linked list
    Each node has a unique vertex number that we use to identify it
*/
typedef struct _adj_node {
    struct _adj_node **o_edges; // store the edges to which the current node connects
    struct _adj_node **next_o_edges; // store the edges to which the current node to connects for the next iteration
    int n_out; // gives the number of out-going edges from a node
    struct _adj_node *head; //head points to the first element in adjacency list
	struct _adj_node *tail; //tail points to last element in adjacency list
	struct _adj_node *next; // next points to the next element in adjacency list
	int vertex; //vertex is the value of the current element
	int healthStatus; // healthStatus tells us whether the node is susceptible (0), infected (1), or recovered (2)
	int nextHealthStatus; // nextHealthStatus tell us the health status of the node for the next iteration (so that we don't make premature updates in the current iteration)

} adj_node;

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
int Search_Node(adj_node *list, int data);

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
unsigned int node_count(adj_node *list);

 // Frees all nodes in the given adjacency linked list.
 void freeAll(adj_node *list);

#endif