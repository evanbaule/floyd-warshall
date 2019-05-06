// C++ Program to check if there is a negative weight
// cycle using Floyd Warshall Algorithm
#include<iostream>
using namespace std;
#include <time.h>
// Number of vertices in the graph
#define V 4

/* Define Infinite as a large enough value. This
   value will be used for vertices not connected
   to each other */
#define INF 99999

// A function to print the solution matrix
void printSolution(int dist[][V]);

// Returns true if graph has negative weight cycle
// else false.
bool negCyclefloydWarshall(int graph[][V]){
    /* dist[][] will be the output matrix that will
       finally have the shortest
    distances between every pair of vertices */
    int dist[V][V], i, j, k;
    int next[V][V];

    /* Initialize the solution matrix same as input
      graph matrix. Or we can say the initial values
      of shortest distances are based on shortest
      paths considering no intermediate vertex. */
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    /* Add all vertices one by one to the set of
       intermediate vertices.
    ---> Before start of a iteration, we have shortest
         distances between all pairs of vertices such
         that the shortest distances consider only the
         vertices in set {0, 1, 2, .. k-1} as intermediate
         vertices.
    ----> After the end of a iteration, vertex no. k is
          added to the set of intermediate vertices and
          the set becomes {0, 1, 2, .. k} */
    for (k = 0; k < V; k++)
    {
        // Pick all vertices as source one by one
        for (i = 0; i < V; i++)
        {
            // Pick all vertices as destination for the
            // above picked source
            for (j = 0; j < V; j++)
            {
                // If vertex k is on the shortest path from
                // i to j, then update the value of dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
            }
        }
    }

    // If distance of any verex from itself
    // becomes negative, then there is a negative
    // weight cycle.
    for (int i = 0; i < V; i++)
        if (dist[i][i] < 0)
            return true;

    for(int i = 0; i < V; i++){
      for(int j = 0; j < V; j++){
        if(dist[i][j] != INF){
          cout << dist[i][j] << ",";
        }else{
          cout << "INF" << ",";
        }
      }
      cout << endl;
    }

    return false;
}

 // driver program
int main(){
    int graph[V][V];
    int generated;
    int edgeChance = 55;
    int weight;
    srand (time(NULL));
    for(int i = 0; i < V; i++){
      for(int j = 0; j < V; j++){
        generated = rand() % 99;
        weight = (rand() % 6) - 2;
        if(i == j){
          graph[i][j] = 0;
        }else if(generated <= edgeChance){
          graph[i][j] = weight;
        }else{
          graph[i][j] = INF;
        }
      }
    }
    for(int i = 0; i < V; i++){
      for(int j = 0; j < V; j++){
        if(graph[i][j] != INF){
          cout << graph[i][j] << ",";
        }else{
          cout << "INF" << ",";
        }
      }
      cout << endl;
    }
    cout << "====================" << endl;

    if (negCyclefloydWarshall(graph))
       cout << "Yes" << endl;
    else
       cout << "No" << endl;
    return 0;
}
