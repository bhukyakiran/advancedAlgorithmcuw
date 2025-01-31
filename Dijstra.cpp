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

void printtheSolution(int dist[], int parent[]) {
    cout << "Vertex\tMinimum of the Cost\tRoute\n";
    for (int i = 1; i < V; i++) {
        cout << "A → " << char('A' + i) << "\t" << dist[i] << "\t\t";

        vector<char> path;
        int j = i;
        while (j != -1) {
            path.push_back('A' + j);
            j = parent[j];
        }

        for (int k = path.size() - 1; k >= 0; k--) {
            cout << path[k];
            if (k != 0) cout << " → ";
        }
        cout << endl;
    }
}


void dijkstralgorithm(int graph[V][V], int src) {
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
                parent[v] = u; 
            }
        }
    }

    
    printtheSolution(dist, parent);
}

int main() {
    
    int graph[V][V] = {
        {0, 10, 0, 0, 3},  
        {10, 0, 2, 0, 1},  
        {0, 2, 0, 9, 8},   
        {0, 0, 9, 0, 2},   
        {3, 4, 8, 2, 0}    
    };

    int source = 0; 
    dijkstralgorithm(graph, source);

    return 0;
}
