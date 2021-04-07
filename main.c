/*
 * CSE 6010 Assignment 6
 * Team: Sarah and Saurabh
 * Created by Saurabh and Sarah
 * Last edited on 30 October 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h> // for seeding random number generator

#include "network.h"
#include "model.h"
//#include "network.c"
//#include "model.c"


int main(int argc, char const *argv[]){

    // Checking values of parameters
	int a = numNearestNeighbors;
	int m;
    srand(time(NULL)); // seed the random number generator

	//Checking that numNearestNeighbors value is even
	if(a % 2 != 0){
		a = a + 1;
		printf("numNearestNeighbors value is not even, hence taking the next even number\n");
	}

	//Checking that numNearestNeighbors value is less than numAgents
	if(a >= numAgents){
		a = numAgents - 1;

		//If a becomes odd, then making it even by reducing one 
		if(a % 2 != 0){
			a = a -1;
		}
		printf("As numNearestNeighbors is more than or equal to numAgents, making numNearestNeighbors value as (numAgents-1)\n");
	}

    // Check pInfection, pRecovery, pDisconnect, and pReplaceRandom
    // If the values are greater than 1, set them to 1
    // If the values are less than 0, set them to 0
    double pInfection_actual = pInfection;
    double pRecover_actual = pRecovery;
    double pDisconnect_actual = pDisconnect;
    double pReplaceRandom_actual = pReplaceRandom;

    if (pInfection_actual > 1){
        pInfection_actual = 1;
        printf("pInfection was greater than 1, so it has been set to 1\n");
    }
    if (pRecover_actual > 1){
        pRecover_actual = 1;
        printf("pRecover was greater than 1, so it has been set to 1\n");
    }
    if (pDisconnect_actual > 1){
        printf("pDisconnect was greater than 1, so it has been set to 1\n");
    }
    if (pReplaceRandom_actual > 1){
        printf("pReplaceRandom was greater than 1, so it has been set to 1\n");
    }
    if (pInfection_actual < 0){
        pInfection_actual = 0;
        printf("pInfection was less than 0, so it has been set to 0\n");
    }
    if (pRecover_actual < 0){
        pRecover_actual = 0;
        printf("pRecover was less than 0, so it has been set to 0\n");
    }
    if (pDisconnect_actual < 0){
        pDisconnect_actual = 0;
        printf("pDisconnect was less than 0, so it has been set to 0\n");
    }
    if (pReplaceRandom_actual < 0){
        pDisconnect_actual = 0;
        printf("pReplaceRandom was less than 0, so it has been set to 0\n");
    }

	// ---------------------------- NETWORK GENERATION ----------------------------
	// Allocate size for each agent. This agent carries the node/vertex value which will
	// be used to assign appropriate neighbors to each node/agent.

	// Allocate size for the adjacency list. First, an array of pointers, each
	// pointer will be the start of a linked list constructed for each line of the
	// adjacency list.

    adj_node *agent = (adj_node*)malloc(numAgents * sizeof(adj_node));
    adj_node **adj_list = (adj_node**)malloc(numAgents * sizeof(adj_node*));
    

    int random_node;
    float b;
    for (int i = 0; i < numAgents; i++){
        agent[i].vertex = i;
		adj_list[i] = (adj_node*)malloc(numAgents * sizeof(adj_node));
        adj_list[i]->n_out = 0;
        adj_list[i]->head = NULL;
		adj_list[i]->tail = NULL;
		adj_list[i]->healthStatus = 0; // originally set all nodes to being susceptible
		adj_list[i]->nextHealthStatus = 0; // originally set to 0
    }

	// For loop will be used to assign neighbors to each node/agent
	// through adjacency list. Here, we have made cases based on the position 
	// of the node/agent we are at. The outer for loop will cover each and every
	// node/agent and assign an array to each node of their neighbor nodes.
	// This will cover all agents upto numAgents
	// The inner for loop will assign 2 neighbors to the node/agent in one go, i.e.
	// if we are at node j, we will assign j+1 and j-1 nodes as neighbor in one
	// iteration of for loop. This will go on until all neighbors are assigned as
	// per numNearestNeighbors.

	// Inside the inner for loop, we will have cases for assigning a neighbor
	// depending on the position of node/agent. For example, the first agent 0, will
	// have neighbors as 1 and the last node in the network. Hence, we are implementing 
	// both of them in different ways through if and else loop.

    //Outer for loop
    for (int i = 0; i < numAgents; i++){
        //Allocating space for the adjacency list corresponding to each node/agent i
        adj_list[i] = (adj_node*)malloc(numAgents * sizeof(adj_node));
        //node_list[i] = (adj_node*)malloc(numAgents * sizeof(adj_node));

        //Variables k and m are used in calculation to determine which node will be allocated as neighbor
        int k =-1;
        m = 1;
        

        // If loop to check whether present node was there as neighbor any
        // previous node. If yes, we will assign that previous node as
        // neighbor of present node, as our graph is undirected.
        if(i > 0 && pReplaceRandom_actual > 0 ){
            for(int j = i; j>=1; j--){
                adj_node *temp = (adj_node*)malloc(sizeof(adj_node));

                // We will search the present node in the list of previous nodes
                // If we find it, we will add it to the adjacency list foor the current node
                if (Search_Node(adj_list[j-1], i) == i) {
                    temp->vertex = j-1;
                    temp->next = NULL;
                    if (node_count(adj_list[i]) == 0){
                        adj_list[i]->head = adj_list[i]->tail = temp;
                    }
                    else{
                        adj_list[i]->tail->next = temp;
                        adj_list[i]->tail = temp;
                    }
                    temp = temp->next;
                }
                if(node_count(adj_list[i]) == a)
                {
                    break;
                }
            }
        }

        //Inner For Loop
        for(int j = 0; j < (a/2); j++){

            b = (double)rand()/(double)RAND_MAX; // generate random number between 0 and nNodes

            if(node_count(adj_list[i]) < a){
                if(b > pReplaceRandom_actual){

                    //If-else loop to assign j+1 neighbor to the node/agent j
                    if(i + j + 1 > numAgents - 1){

                        //Assigning the neighbor node value to *temp
                        adj_node *temp = (adj_node*)malloc(sizeof(adj_node));
                        temp->vertex = agent[numAgents - i - j + k].vertex;

                        //To see that the selected node is not already present in the list and it's value is not same as i
                        while(Search_Node(adj_list[i],temp->vertex) == temp->vertex || temp->vertex == i ){
                            if(temp->vertex > 0){
                                temp->vertex = temp->vertex - 1;
                                
                            }
                            else{
                                temp->vertex = numAgents -1;
                            }
                        }
                        temp->next = NULL;
                        
                        //if(i==499){printf("1. %d and %d and %d and %d and %d\n", temp->vertex,i,j,k,Search_Node(adj_list[i],temp->vertex));}

                        //If the list is filled for the very first time
                        // head and tail are same
                        if(node_count(adj_list[i]) == 0){
                            adj_list[i]->head = adj_list[i]->tail = temp;
                        }

                            //If the list has at least one element
                        else{
                            // Adding the node neighbor at the end of the list
                            adj_list[i]->tail->next = temp;
                            adj_list[i]->tail = temp;
                            // adj_list[i]->tail->visitStatus =1;
                        }

                        
                        //Increasing k value by 2 as second neighbor will be assigned in this for loop
                        k = k + 2;
                        //Assigning temp to point to next position
                        temp = temp->next;

                        //printf("%d\n", adj_list[i]->tail->vertex);
                    }

                    //Developed on the same basis as if part, but differs in neighbor node value
                    else{
                        adj_node *temp = (adj_node*)malloc(sizeof(adj_node));
                        temp->vertex = agent[i + j + 1].vertex;

                        //To see that the selected node is not already present in the list and it's value is not same as i
                        while(Search_Node(adj_list[i],temp->vertex) == temp->vertex || temp->vertex == i) {
                            if(temp->vertex < (numAgents - 1)){
                                temp->vertex = temp->vertex + 1;
                            }
                            else{
                                temp->vertex = 0;
                            }
                        }
                        //if(i==499){printf("2. %d\n", temp->vertex);}
                        temp->next = NULL;
                        if(node_count(adj_list[i]) == 0){
                            adj_list[i]->head = adj_list[i]->tail = temp;
                            //adj_list[i]->head->visitStatus = 1;
                        }
                        else{
                            adj_list[i]->tail->next = temp;
                            adj_list[i]->tail = temp;
                            //adj_list[i]->tail->visitStatus =1;
                        }
                        
                        temp = temp->next;

                        //printf("%p\n", adj_list);
                    }
                }

                //else loop to assign the node randomly
                else{
                    random_node = rand() % numAgents; // generate random number between 0 and numAgents

                    //Assigning the neighbor node value to *temp
                    adj_node *temp = (adj_node*)malloc(sizeof(adj_node));
                    temp->vertex = agent[random_node].vertex;

                    //To see that the selected node is not already present in the list and it's value is not same as i
                    while(Search_Node(adj_list[i],temp->vertex) == temp->vertex || temp->vertex == i ){
                        srand(time(NULL));
                        random_node = rand() % numAgents;
                        temp->vertex = agent[random_node].vertex;

                    }
                    if(i==499){printf("3. %d\n", temp->vertex);}
                    temp->next = NULL;

                    //If the list is filled for the very first time
                    // head and tail are same
                    if(node_count(adj_list[i]) == 0) {
                        adj_list[i]->head = adj_list[i]->tail = temp;
                        //adj_list[i]->head->visitStatus = 1;
                    }
                        //If the list has at least one element
                    else {
                        // Adding the node neighbor at the end of the list
                        adj_list[i]->tail->next = temp;
                        adj_list[i]->tail = temp;
                        //adj_list[i]->tail->visitStatus =1;
                    }


                }
                adj_list[i]->n_out = adj_list[i]->n_out + 1;
            }

            b = (double)rand()/(double)RAND_MAX; // generate random number between 0 and 1

            //printf("%d\n", node_count(adj_list[i]));

            if(node_count(adj_list[i]) < a){
                if(b > pReplaceRandom_actual){
                    ////If-else loop to assign j-1 neighbor to the node/agent j
                    if(i-j-1 < 0){

                        //Assigning the neighbor node value to *temp
                        adj_node *temp = (adj_node*)malloc(sizeof(adj_node));
                        temp->vertex = agent[numAgents - m].vertex;
                        m =m+1;

                        //To see that the selected node is not already present in the list and it's value is not same as i
                        while(Search_Node(adj_list[i],temp->vertex) == temp->vertex || temp->vertex == i ){
                            if(temp->vertex > 0) {
                                temp->vertex = temp->vertex -1;
                            }
                            else {
                                temp->vertex = 0;
                            }
                        }
                        //if(i==499){printf("4. %d\n", temp->vertex);}
                        temp->next = NULL;


                        //As list already has at least one value, we add the next value to the end of list
                        adj_list[i]->tail->next = temp;
                        adj_list[i]->tail = temp;
                        
                        temp = temp->next;

                    }

                    //Developed on the same basis as if part, but differs in neighbor node value
                    else {
                        adj_node *temp = (adj_node*)malloc(sizeof(adj_node));
                        temp->vertex = agent[ i - j - 1].vertex;

                        //To see that the selected node is not already present in the list and it's value is not same as i
                        while(Search_Node(adj_list[i],temp->vertex) == temp->vertex || temp->vertex == i ){
                            if(temp->vertex >0) {
                                temp->vertex = temp->vertex - 1;
                            }
                            else {
                                temp->vertex = numAgents-1;
                            }
                        }
                        if(i==499){printf("5. %d\n", temp->vertex);}
                        temp->next = NULL;

                        adj_list[i]->tail->next = temp;
                        adj_list[i]->tail = temp;

                        temp = temp->next;
                    }

                    // We increase the number of out edges for the node, as
                    // every time the for loop adds two neighbors

                }
                //else loop to assign the node randomly
                else {
                    random_node = rand() % numAgents; // generate random number between 0 and numAgents

                    //Assigning the neighbor node value to *temp
                    adj_node *temp = (adj_node*)malloc(sizeof(adj_node));
                    temp->vertex = agent[random_node].vertex;

                    //To see that the selected node is not already present in the list and it's value is not same as i
                    while(Search_Node(adj_list[i],temp->vertex) == temp->vertex || temp->vertex == i ) {
                        srand(time(NULL));
                        random_node = rand() % numAgents;
                        temp->vertex = agent[random_node].vertex;
                    }

                    //if(i==499){printf("6. %d\n", temp->vertex);}
                    temp->next = NULL;

                    //If the list is filled for the very first time
                    // head and tail are same
                    if(node_count(adj_list[i]) == 0) {
                        adj_list[i]->head = adj_list[i]->tail = temp;
                        //adj_list[i]->head->visitStatus = 1;
                    }
                        //If the list has at least one element
                    else {
                        // Adding the node neighbor at the end of the list
                        adj_list[i]->tail->next = temp;
                        adj_list[i]->tail = temp;
                        //adj_list[i]->tail->visitStatus =1;
                    }

                    
                }
                adj_list[i]->n_out = adj_list[i]->n_out + 1;
            }

        }

    }

	// Print out the adjacency list we just created
	// to check neighbors are assigned correctly
    
	for (int i = 0; i < numAgents; ++i) {
		printf("Vertex %d is adjacent to:\t",i);
		adj_node *neighbors = adj_list[i];
		if(neighbors->vertex == -1) {
			printf("No other vertices.\n");
		}
		else{
		    adj_node *ptr;
		    ptr = neighbors->head;
			while(ptr != NULL) {
				printf("%d, ",ptr->vertex);
				ptr = ptr->next;
			}
			printf("\n");
		}
	}

    // ---------------------------- EPIDEMIC MODELING ----------------------------

    // Initialize variables to start the epidemic modeling
	adj_list[0]->healthStatus = 1; // set the 0th node to be infected to start the cycle
	adj_list[0]->nextHealthStatus = 1; // set 0th node to be infected to start the cycle
    int iterations = 1; // keep track of how many iterations have passed
    double probability = 0;
    int maxInfected = 0; // maximum number of infected individuals in a single iteration
    int maxInfectedIter = 1; // iteration number at which the maximum number of infected individuals occurs.
    int currentlyInfected = 0;
    int currentlyRecovered = 0;
    adj_node *neighbors; // points to adjacency list of neighbors for node
    adj_node *ptr; // allows us to iterate through adjacency list of neighbors for node

    /*
     * General steps of the epidemic modeling loop
     * 1. Check if the node is infected
     *      1a. If the node was not infected, move on to the next node (skip to step 5)
     * 2. Check for disconnection
     *      2a. Each infected node (did not recover from the end of the last iteration) has the potential to disconnect from neighbors
     *      2b. For iteration 2 and beyond, roll the probability to see if the node will be disconnected
     *      2c. If the probability is less than/equal to pDisconnect, the node will be disconnected
     *      2d. A disconnected node can no longer infect others
     *      2e. Skip to step 4
     * 3. Check for infection
     *      3a. If the node was not disconnected, it still has the potential to infect others
     *      3b. For each neighbor that the node is connected to, roll the probability
     *      3c. If the probability rolled is less than/equal to pInfection, that neighbor becomes infected also
     * 4. Check for recovery
     *      4a. Any node that was already infected at the beginning of the iteration has the potential to recover (including disconnected nodes)
     *      4b. For each infected node, roll the probability
     *      4c. If the probability is less than/equal to pRecovery, that node has recovered
     *      4d. Recovered nodes can no longer infect any neighbors or be infected again
     * 5. Repeat steps 1-4 for all nodes
     * 6. At the end of the iteration, calculate number of infected nodes
     *      6a. If the current number of infected nodes is less than the max infected nodes, it becomes the max infected nodes
     *      6b. Save the current iteration as the iteration where the max infection occurs
     */
    while (iterations <= numIterations) {

        // For each node, check for disconnect, infection, and recovery
        for (int i = 0; i < numAgents; i++) {

            // A node can only infect, disconnect, or recover if it is already infected
            // If the health status of the node is not 1, move on to the next node
            if (adj_list[i]->healthStatus == 1) {

                // Check for disconnect
                // For iterations 2 and beyond, if the node was already infected at the start of the iteration, it might disconnect from neighbors
                // This is assuming it did not recover at the end of the last iteration
                // If it disconnects from neighbors, it won't infect any neighbors
                if (iterations > 1) {

                    // Roll probability
                    // If probability rolled is less than/equal to pDisconnect, then disconnect the node
                    probability = (double) rand() / (double) ((unsigned) RAND_MAX + 1);
                    // probability = 0.4;
                    if (probability <= pDisconnect_actual) {

                        // Get the adjacency list of neighbors for the node so we know which nodes to disconnect
                        neighbors = adj_list[i];
                        ptr = neighbors->head;
                        while (ptr != NULL) {
                            adj_node *neighborNode = adj_list[ptr->vertex];
                            if (neighborNode->head->vertex == i) {
                                neighborNode->head = neighborNode->head->next;
                            } else {
                                adj_node *neighborPrev = neighborNode->head;
                                adj_node *neighborPtr = neighborNode->head->next;
                                while (neighborPtr != NULL) {
                                    if (neighborPtr->vertex == i) {
                                        neighborPrev->next = neighborPtr->next;
                                        break; // once we have found the node to disconnect, break out of the loop
                                    }
                                    neighborPtr = neighborPtr->next;
                                    neighborPrev = neighborPrev->next;
                                }
                            }
                            ptr = ptr->next;
                        }
                        neighbors->head = NULL; // disconnect all the node's neighbors
                    }

                }

                // Find all the neighbors of the node
                // If the node was disconnected, neighbors will be empty
                // Reset ptr to the beginning of the adjacency list
                neighbors = adj_list[i];
                ptr = neighbors->head;

                // If the node is infected, roll the probability for each of its neighbors to see if the neighbors will be infected
                while(ptr != NULL){

                    // Roll probability
                    // If probability rolled is less than/equal to pInfection, then that node has become infected
                    probability = (double) rand() / (double) ((unsigned) RAND_MAX + 1);
                    if (probability <= pInfection_actual) {
                        if (adj_list[ptr->vertex]->healthStatus == 0){ // only update infect the node if it is not currently infected and has not recovered
                            adj_list[ptr->vertex]->nextHealthStatus = 1;
                        }
                    }
                    ptr = ptr->next; // move to the next neighbor
                }

                // See if the infected node will recover
                // Node will recover if it was already infected by the start of the iteration
                // Probability must be less than/equal to pRecover
                probability = (double) rand() / (double) ((unsigned) RAND_MAX + 1);
                if (probability <= pRecover_actual){
                    adj_list[i]->nextHealthStatus = 2;
                }
            }
        }

        // We kept a separate number called nextHealthStatus, so that we could keep track of the changed health status without affecting the current iteration
        // Now, update all the healthStatus with nextHealthStatus so that it can be updated for the next iteration
        // Reset the nextHealthStatus for each node
        for (int i=0; i<numAgents; i++){
            adj_list[i]->healthStatus = adj_list[i]->nextHealthStatus;
        }

        // Count how many nodes are currently infected and recovered
        currentlyInfected = 0;
        currentlyRecovered = 0;
        currentlyInfected = findInfected(&adj_list);
        currentlyRecovered = findRecovered(&adj_list);

        // Keep track of which iteration has had the most infections so far
        // And how many infections there were
        if (currentlyInfected > maxInfected){
            maxInfected = currentlyInfected;
            maxInfectedIter = iterations;
        }

        // For testing- take out when done
        // printf("%s %d\n", "Iteration:", iterations);
        // printf("%s %d\n", "Number of infected nodes:", currentlyInfected);
        // printf("%s %d\n", "Number of recovered nodes:", currentlyRecovered);

        iterations = iterations + 1;

    }

    // After all iterations are done
    // Count final number of infected and recovered nodes
    currentlyInfected = 0;
    currentlyRecovered= 0;
    currentlyInfected = findInfected(&adj_list);
    currentlyRecovered = findRecovered(&adj_list);

    // Print final results
    // The maximum number of infected individuals in a single iteration
    // The iteration number at which the maximum number of infected individuals occurs
    // The sum of the number of currently infected and recovered individuals after the last iteration
    printf("%s %d\n", "The maximum number of infected individuals in a single iteration:", maxInfected);
    printf("%s %d\n", "The iteration number at which the maximum number of infected individuals occurs:", maxInfectedIter);
    printf("%s %d\n", "The sum of number of currently infected and recovered individuals after the last iteration:", currentlyInfected+currentlyRecovered);

	// Free all memory
	for (int i = 0; i < numAgents; i++){
		freeAll(adj_list[i]);
	}

	free(adj_list);
	free(agent);

	return 0;
}