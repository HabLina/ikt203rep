#include <iostream>
#include <vector>
#include <string>

//Assign a high number to Inf so The Floyd-Warshall algorithm function looks for other paths with smaller costs
float Inf = 999;

//The Floyd-Warshall algorithm function, takes the graph vector and next hop vector as parameters
void floydWarshall(std::vector<std::vector<float>>& graph, std::vector<std::vector<int>>& nextHop) {
    int V = graph.size();  //Number of routers

    //Triple-nested loop to iterate over all pairs of routers
    for (int k = 0; k < V; ++k) { //The k variable represents the intermediate vertex, the alternate path
        for (int i = 0; i < V; ++i) {//The i variable represents the starting vertex, the current router
            for (int j = 0; j < V; ++j) {//The j variable represents the destination vertex, the destination of a potential path

                //Checks if there is a shorter path through router 'k'
                if (graph[i][j] != Inf && graph[i][k] + graph[k][j] < graph[i][j]) {

                    //Updates the shortest path and next hop information
                    graph[i][j] = graph[i][k] + graph[k][j];
                    nextHop[i][j] = k + 1;  //Adds 1 to router index for 1-based indexing
                }
            }
        }
    }
}

//Function that prints the routing tables
void printRoutingTable(const std::vector<std::vector<float>>& graph, const std::vector<std::vector<int>>& nextHop, int routerId) {
    int V = graph.size();  //The number of routers

    //The header for the routing table
    std::cout << "Routing Table for Router " << routerId + 1 << ":\n";
    std::cout << "Destination Router ID\tNext Hop Router ID\tTotal Cost to Destination\n";

    //Iterates over all destinations for the current router
    for (int dest = 0; dest < V; ++dest) {
        int next = nextHop[routerId][dest];
        //Prints the destination, next hop, and total cost information
        std::cout << dest + 1 << "\t\t\t" << next << "\t\t\t" << graph[routerId][dest] << "\n";
    }
    //The separator line for better readability
    std::cout << "--------------------------------\n";
}

int main() {
    const int V = 7;  //The number of routers

    //The user input of the edges of the routing table, Chose to ask the user to write it as a line as we think that easier for the user to write in
    std::cout << "Enter the values in a line:" << std::endl;
    std::vector<std::vector<float>> graph(V, std::vector<float>(V));

    //Nested loop used to populate the graph matrix
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            std::string input;
            std::cin >> input;

            //Converts the input to float and handle zero values
            graph[i][j] = std::stof(input);
            if (graph[i][j] == 0 && i != j) {
                graph[i][j] = Inf;  //Inf represents the absence of direct connection
            }
        }
    }

    //Initializes the nextHop matrix with default value -1, If next hop remains as -1 it means that the next hop is the same as the destination vertex
    std::vector<std::vector<int>> nextHop(V, std::vector<int>(V, -1));

    //Runs the Floyd-Warshall algorithm
    floydWarshall(graph, nextHop);

    //Prints routing table for each router
    for (int routerId = 0; routerId < V; ++routerId) {
        printRoutingTable(graph, nextHop, routerId);
    }

    return 0;
}