/*
 * CSE 6010 Assignment 6
 * Team: Sarah and Saurabh
 * Created by Sarah
 * Last edited on 30 October 2020
 */

#include "network.h"
#include "model.h"

/*
 * Function:  findInfected
 * --------------------
 * Description:
 *      Find how many nodes are infected
 * Parameters:
 *      adj_list: the linked list which contains the elements/neighbors of specific node
 * Returns:
 *      Number of infected nodes
 */
int findInfected(adj_node ***adj_list){
    int currentlyInfected = 0;
    for (int i=0; i<numAgents; i++){
        if ((*adj_list)[i]->healthStatus == 1){
            currentlyInfected++;
        }
    }
    return currentlyInfected;
}

/*
 * Function:  findRecovered
 * --------------------
 * Description:
 *      Find how many nodes are recovered
 * Parameters:
 *      adj_list: the linked list which contains the elements/neighbors of specific node
 * Returns:
 *      Number of recovered nodes
 */
int findRecovered(adj_node ***adj_list){
    int currentlyRecovered = 0;
    for (int i=0; i<numAgents; i++){
        if ((*adj_list)[i]->healthStatus == 2){
            currentlyRecovered++;
        }
    }
    return currentlyRecovered;
}
