#include <headerFile.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <LEDA/graph/graph.h>
#include <LEDA/graph/node_array.h> 
#include <LEDA/core/list.h>
#include <LEDA/core/random_source.h>
#include <LEDA/core/set.h> 
#include <LEDA/graph/node_set.h> 
#include <LEDA/system/timer.h>

// Create a shortcut for new line.
#define newline std::cout << "\n"

using namespace leda;

bool my_bipar_checker(const graph& G, list<node>& V1, list<node>& V2, node_array<int>& color){
    // Initialize distances with -1 and predecessors with nil to use in BFS
    node_array<int> dist(G,-1);
    node_array<edge> pred(G, nil);

    // Choose a random node of G to start BFS
    node start_node = G.choose_node();
    

    // Create a node list to store results of BFS
    list<node> resultList = my_BFS(G, start_node ,dist, pred, color);


    // Temporary variables for edge iteration
    edge currentEdge;

    // Create a set of nodes to check if a node has already been inserted in V1 or V2
    node_set tmpSet(G);
    
    forall_edges(currentEdge, G){

        // Check if nodes of the current edge have the same color 
        // If true, the graph is not bipartite 
        if(color[G.source(currentEdge)] == color[G.target(currentEdge)]){
            

            // Back represents the path before the current edge 
            // Front represents the path after the current edge 
            // Create temporary nodes to store previous nodes for both front and back 
            node frontPrev = G.target(currentEdge);
            node backPrev = G.source(currentEdge);
            edge backEdge = pred[backPrev];
            edge frontEdge = pred[frontPrev];

            // Clear V1 and V2
            V1.clear();
            V2.clear();

            // Store the source and the target of the current edge in V1
            V1.append(backPrev);
            V1.append(frontPrev);

            int lastCheck = 0;
            // Check if the previous back node is the same as the previous front node 
            // If true, a circle is found  
            while(lastCheck != 1) {

                // Check if the next edge has the source or target as the same node 
                // So, select the other node of both back and front to get the pred edge 
                if(backPrev == G.source(backEdge)){
                    backPrev = G.target(backEdge);
                    backEdge = pred[backPrev];
                }
                else{
                    backPrev = G.source(backEdge);
                    backEdge = pred[backPrev];
                }

                if(frontPrev == G.source(frontEdge)){
                    frontPrev = G.target(frontEdge);
                    frontEdge = pred[frontPrev];
                }
                else{
                    frontPrev = G.source(frontEdge);
                    frontEdge = pred[frontPrev];
                }


                // Store in V1 every node of the circle
                if(backPrev != frontPrev){
                    V1.push(backPrev);
                    V1.append(frontPrev);
                }
                else{
                    lastCheck = 1;
                    V1.append(frontPrev);
                }
            }   
            return false;
        }        
    }

    // Organize nodes in the list based on their color    
    node currentNode;
    forall_nodes(currentNode, G){
            if(color[currentNode] == 0){
                V1.append(currentNode);
            }
            else{
                V2.append(currentNode);
            }

    }
    
    return true;
}

// Function to create a graph representing nested squares
graph nested_square_graph(const int n){

    graph G1;

    std::vector<node> cycleNode; 
    // Creates all nodes of the graph and store them in a vector.
    for(int j = 0; j<n; ++j){
        cycleNode.push_back(G1.new_node());
    }

    for(int j = 0; j<n; ++j){
        // If the loop is in the first square, create only edges to make a square.
        if(j<4){
            if(j%4 !=3){
                G1.new_edge(cycleNode[j], cycleNode[j+1]);
            }
            else{
                G1.new_edge(cycleNode[j],cycleNode[j-3]);
            }
        }
        // If the first square has already been created, create edges to connect the square and the outer nodes.
        else{
            G1.new_edge(cycleNode[j],cycleNode[j-4]);


            // Create edges to make a square.
            if(j%4 !=3){
                G1.new_edge(cycleNode[j], cycleNode[j+1]);
            }
            else{
                G1.new_edge(cycleNode[j],cycleNode[j-3]);
            }
        }
    }

    // Return the created graph.
    return G1;

}

// Function to create a graph representing an odd ring
graph odd_ring_graph(const int n){
    graph G2;

    // Create a prev and a next node, so can create the nodes and the edges simultaneously.
    node vPrev;
    node vNext;

    for(int i = 0; i<n; ++i){
        if(i == 0){
            // If no nodes have been created yet, create the 1st and the 2nd 
            vPrev = G2.new_node();
            vNext = G2.new_node();
        }
        else if(i == (n-1)){
            // If the loop is in the last node, connect the last node 
            // Set prev with the current next and the next with the first node of the graph
            vPrev = vNext;
            vNext = G2.first_node();
        }
        else{
            // Set prev with the current next node and create a new node
            vPrev = vNext;
            vNext = G2.new_node();
        }
        // Create an edge to connect prev with next.
        G2.new_edge(vPrev,vNext);
     }
    
    // Return the created graph.
    return G2;
}

// Function to create a graph representing a complex structure with 4 levels
graph complex_graph_4levels(const int k){
    int numOfLevels = 4;

    // Initilize two vector, first stores each node for each level and the seconds stores every vector for each level.
    std::vector<std::vector<node> > levels;
    std::vector<node> levelN;
    graph G3;

    // Create all nodes for each level and store them in a vector.
    for(int i=0; i<numOfLevels; ++i){
        levelN.clear();
        for(int m = 0; m<k; ++m){ levelN.push_back(G3.new_node()); }
        levels.push_back(levelN);
    }

    // Instance of random source
    // S(0, k-1) return a random integer from 0 to k-1
    random_source S;
    for(int i=0; i<numOfLevels-1; ++i){
        int randomNumNode = S(0,k-1);
        for(int j=0; j<k; ++j){
            // Create an edge which connects each node of a level connected to each node of the next level.
            G3.new_edge(levels[i][j],levels[i+1][j]);
            if(randomNumNode!=j){
                // Create an edge which connects a random node of a level with all nodes of the next level.
                G3.new_edge(levels[i][randomNumNode],levels[i+1][j]);
            }
        }
        // Create an edge which connects a random node of the first level with a random node of the third level.
        if(i == 0){
                G3.new_edge(levels[i][S(0,k-1)], levels[i+2][S(0,k-1)]);
        }
        // Create an edge which connects a random node of the second level with a random node of the fourth level.
        else if(i==1){
                G3.new_edge(levels[i][S(0,k-1)], levels[i+2][S(0,k-1)]);
        }
    }

    // Return the created graph.
    return G3;
}

int main() {
    // Initialize the graph and the required variables
    graph G;

    // Varibles to store the choice of the use to create the graph.
    int choice;
    int input;
    
    // Clear terminal window.
    system("clear");


    // Printing Menu
    std::cout << "##### GRAPH CREATION MENU #####" << std::endl;
    std::cout << "1. Nested Squares" << "\n2. Odd Ring" << "\n3. Complex 4 Levels" << std::endl;
    std::cout << "Enter the number corresponding to the type of the graph you want to create: ";
    std::cin >> choice;


    // Check the choice and create each graph.
    switch(choice) {
        case 1:    
            std::cout << "Enter the number of nodes (must be a multiple of 4): ";
            std::cin >> input;
            
            while(input % 4 != 0) {
                std::cout << "Error: Please enter a number that is a multiple of 4: ";
                std::cin >> input;
                newline;
            }

            // Create the nested squares graph ;
            G = nested_square_graph(input);

            newline;
            std::cout << "##### GRAPH DETAILS #####" << std::endl;
            std::cout << "Graph Type: Nested Squares" << std::endl;

            break;
        case 2:
            std::cout << "Enter the number of nodes (must be odd): ";
            std::cin >> input;
            
            while(input % 2 == 0) {
                std::cout << "Error: Please enter an odd number of nodes: ";
                std::cin >> input;
                newline;
            }

            // Create the odd ring graph            
            G = odd_ring_graph(input);

            
            newline;
            std::cout << "##### GRAPH DETAILS #####" << std::endl;
            std::cout << "Graph Type: Odd Ring Nodes" << std::endl;

            break;
        case 3:
            std::cout << "Enter the number of nodes for a single level: ";
            std::cin >> input;

            // Create the complex 4 levels graph 
            G = complex_graph_4levels(input);
            
            newline;
            std::cout << "##### GRAPH DETAILS #####" << std::endl;
            std::cout << "Graph Type: Complex 4 Levels" << std::endl;

            break;
        default:
            std::cout << "Invalid choice. Exiting program." << std::endl;
            return 0;
    }


    // Exiting programm if graph is empty.
    if(G.empty()) {
        std::cout << "Error: Graph creation failed. The graph is empty!" << std::endl;
        return 0;
    }

    std::cout << "Number of nodes: " << G.number_of_nodes() << std::endl;
    std::cout << "Number of edges: " << G.number_of_edges() << std::endl;
    newline;

    // Initialize the node array color with -1
    node_array<int> color(G, -1);
    // Initialize lists to store the circle or disjoin sets.
    list<node> V1;
    list<node> V2;
    list<node> A;
    list<node> B;


    // Use result1 to store result value of my checker. 
    bool result1;
    // Use result3 to store result value of my checker.
    bool result2;
    

    // Use the following variables to calculate the runtime.
    long counter;
    float secondsRes1;
    float secondsRes2;
    clock_t start, finish;
    int mulNum = 10;    
    
    // Call my bipartite checker and the timer calculate its runtime.
    start = clock();
    counter = 0;
    while(clock() - start < mulNum*CLOCKS_PER_SEC){
        counter+=1;
        V1.clear();
        V2.clear();
        result1 = my_bipar_checker(G, V1, V2, color);
    }
    finish = clock();
    secondsRes1 = float(finish - start) / CLOCKS_PER_SEC;
    secondsRes1 = secondsRes1 / counter;

    // Print the Results
    std::cout << "##### MY BIPARTITE CHECKER RESULTS #####" << std::endl;
    if(result1) {
        std::cout << "The graph is bipartite." << std::endl;
    } else {
        std::cout << "The graph is not bipartite." << std::endl;
    }
    std::cout << "Bipartite checker runtime: " << std::fixed << secondsRes1 << std::setprecision(9);
    std::cout << " seconds" << std::endl;
    std::cout << "Lenght of V1: " << V1.length() << std::endl;
    std::cout << "Lenght of V2: " << V2.length() << std::endl;
    if(!result1 && V1.length() <= 30) {
        std::cout << "V1:\t";
        node v;
        forall(v, V1)
            G.print_node(v, std::cout);
        
        newline;
    }
    else if(result1 && V1.length() <= 30){
        std::cout << "V1:\t";
        node v1;
        forall(v1, V1)
            G.print_node(v1, std::cout);
        
        newline;
        std::cout << "V2:\t";
        node v2;
        forall(v2, V2)
            G.print_node(v2, std::cout);
        
        newline;

    }
    
    //Call the LEDA bipartite checker and calculate its runtime.
    start = clock();
    counter = 0;
    while(clock() - start < mulNum*CLOCKS_PER_SEC){
        counter+=1;
        A.clear();
        B.clear();
        result2 = Is_Bipartite(G, A, B);;
    }
    finish = clock();
    secondsRes2 = float(finish - start) / CLOCKS_PER_SEC;
    secondsRes2 = secondsRes2 / counter;

    newline;
    std::cout << "##### LEDA BIPARTITE CHECKER RESULTS #####" << std::endl;
    if(result2) {
        std::cout << "The graph is bipartite." << std::endl;
    } else {
        std::cout << "The graph is not bipartite." << std::endl;
    }
    std::cout << "Bipartite checker runtime: " << std::fixed << secondsRes2 << std::setprecision(10);
    std::cout << " seconds" << std::endl;
    std::cout << "Lenght of A: " << A.length() << std::endl;
    std::cout << "Lenght of B: " << B.length() << std::endl;
    if(!result2 && A.length() <= 30) {
        std::cout << "A:\t";
        node w;
        forall(w, A)
            G.print_node(w, std::cout);
        newline;
    }
    else if(result2 && A.length() <= 30){
        std::cout << "A:\t";
        node a;
        forall(a, A)
            G.print_node(a, std::cout);
        
        newline;
        std::cout << "B:\t";
        node b;
        forall(b, B)
            G.print_node(b, std::cout);
        
        newline;

    }

    if(input <= 16){
        newline;
        std::cout << "##### GRAPH PRINTING #####";
        G.print(std::cout);
    }

    newline;
    return 0;
}