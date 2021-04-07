# Epidemic Network Model

Authors :

Sarah Bi

Saurabh Parimal Doodhwala 

Program description:
This program will generate a network and perform the epidemic modelling on that network. This program is divided into two parts. 

The network generation program will create a network and epimdemic modelling part will use that network generated. There is one main executable file called main.c to get the results of the network generated and the modelling of that. Necessary functions for network generation are written in network.c and network.h, while that for modelling part are written in model.h and model.c.

How to compile and run (in Linux): 
1. Navigate to the directory containing the files main.c, network.c, network.h, model.c and model.h 
2. Ensure that the file titled "makefile" is also in the same directory
3. Type the following command to compile the program: make
4. Type the following command to run the program: ./main

The following global variables are defined in network.h file:

#define numAgents 10

#define numIterations 100

#define numNearestNeighbors 4

#define pReplaceRandom 0

The following global variables are defined in model.h file:

#define pInfection 0.05

#define pRecovery 0.1

#define pDisconnect 0

These values can be changed by the user. If any invalid value is added, then a message will be printed in the terminal, indicating that value was wrong and an appropriate value will be taken. Sample output is as follows for the above shown values:

Vertex 0 is adjacent to:        1, 9, 2, 8, 

Vertex 1 is adjacent to:        2, 0, 3, 9, 

Vertex 2 is adjacent to:        3, 1, 4, 0, 

Vertex 3 is adjacent to:        4, 2, 5, 1, 

Vertex 4 is adjacent to:        5, 3, 6, 2, 

Vertex 5 is adjacent to:        6, 4, 7, 3, 

Vertex 6 is adjacent to:        7, 5, 8, 4, 

Vertex 7 is adjacent to:        8, 6, 9, 5, 

Vertex 8 is adjacent to:        9, 7, 0, 6, 

Vertex 9 is adjacent to:        0, 8, 1, 7, 

The maximum number of infected individuals in a single iteration: 5

The iteration number at which the maximum number of infected individuals occurs: 23

The sum of number of currently infected and recovered individuals after the last iteration: 8



Network Generation:
The network generation code was written on a computer with: 
1) Operating system: Windows 10
2) compiler used: GCC
3) C IDE: VS Code
4) Testing: Linux Darwin 19.5.0



Epidemic Modelling:
The maze solution code was written on a computer with: 
1) Operating system : macOS Catalina Version 10.15.6
2) Compiler: Clang Version 11.0.3
3) C IDE: CLion Version 2020.2 
4) Testing: Linux Darwin 19.5.0
