#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

#define V 5  


int minDistanceof(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}


void printthePath(int parent[], int j) {
    if (parent[j] == -1) {
        cout << char('A' + j);
        return;
    }
    printthePath(parent, parent[j]);
    cout << " → " << char('A' + j);
}


void dijkstralgorthim(int graph[V][V], int src, int dest) {
    int dist[V];      
    bool sptSet[V];  
    int parent[V];    

    
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistanceof(dist, sptSet);
        sptSet[u] = true; 

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u; // Store path
            }
        }
    }

    
    cout << "Shortest Path from " << char('A' + src) << " to " << char('A' + dest) << ":\n";
    cout << "Cost: " << dist[dest] << "\nPath: ";
    printthePath(parent, dest);
    cout << endl;
}

int main() {
    int graph[V][V] = {
        {0, 10, 0, 0, 3},  
        {10, 0, 2, 0, 1},  
        {0, 2, 0, 9, 8},   
        {0, 0, 9, 0, 2},   
        {3, 4, 8, 2, 0}    
    };

    char start, end;
    cout << "Enter starting node (A-E): ";
    cin >> start;
    cout << "Enter ending node (A-E): ";
    cin >> end;

    int src = start - 'A';
    int dest = end - 'A';

    if (src >= 0 && src < V && dest >= 0 && dest < V) {
        dijkstralgorthim(graph, src, dest);
    } else {
        cout << "Invalid input! Please enter nodes between A and E.\n";
    }

    return 0;
}
