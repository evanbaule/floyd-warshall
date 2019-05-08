// C++ Program to check if there is a negative weight
// cycle using Floyd Warshall Algorithm
#include<iostream>
#include<stdlib.h>
#include <time.h>

#include "fw.hpp"

using namespace std;


// returns encapsulated results for each test case
result*
floyd_warshall(int v, int edgeChance)
{
    result* res = new result(); //encapsulated results

    int g[v][v]; //graph adjacency matrix
    //int dist[v][v]; //holds distance of shortest path between two given nodes i & j for dist[i][j]

    //util/results for path reconstruction
    int next[v][v];
    int paths[v][v];

    //randomly generated values
    int generated;
    int weight;

    srand(time(NULL));
    for(int i = 0; i < v; i++)
    {
        for(int j = 0; j < v; j++)
        {
            generated = rand() % 99;
            weight = (rand() % 6) - 1;
            if (i == j)
            {
                g[i][j] = 0;
            }
            else if ( generated <= edgeChance )
            {
                g[i][j] = weight;
            }
            else 
            {
                g[i][j] = INF;
            }

            //Path reconstruction initialization
            paths[i][j] = 0;
        }
    }

    // Print out the original matrix
    for(int i = 0; i < v; i++)
    {
        for(int j = 0; j < v; j++)
        {
            if(g[i][j] < INF - 100)
            {
                cout << g[i][j] << ",";
            }
            else
            {
                cout << "INF" << ",";
            }
        }
        cout << endl;
    }
    std::cout << "------------------------------------------------------" << std::endl;

    // V[k] = node to be considered as intermediary
    for (int k = 0; k < v; k++)
    {
        // V[i] = source node for the given path
        for (int i = 0; i < v; i++)
        {
            // V[j] = destination node for the given path
            for (int j = 0; j < v; j++)
            {
                // If vertex V[k] is on the shortest path from i to j update the value of dist
                if (g[i][k] + g[k][j] < g[i][j])
                {
                    g[i][j] = g[i][k] + g[k][j];
                    paths[i][j] = k;
                } 
            }
        }
    }

    //Check for a negative cycle in the resulting matrix
    //Negative cycles represented by negative path between a vertex and itself
    res->neg_cycle = false;
    for (int i = 0; i < v; i++)
    {
        if (g[i][i] < 0)
        {
            res->neg_cycle = true;
            std::cout << "||||||INVALID INPUT|||||| :: Negative Cycles Detected !!! ||||||INVALID INPUT|||||| " << std::endl;
            return res;
        }
    }

    // Print out the resulting matrix
    for(int i = 0; i < v; i++)
    {
        for(int j = 0; j < v; j++)
        {
            if(g[i][j] < INF - 100)
            {
                cout << g[i][j] << ",";
            }
            else
            {
                cout << "INF" << ",";
            }
        }
        cout << endl;
    }

    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Printing path matrix: " << std::endl;
    // Print out the path matrix
    for(int i = 0; i < v; i++)
    {
        for(int j = 0; j < v; j++)
        {
            std::cout << "{ " << paths[i][j] << " } ";
        }
        std::cout << std::endl;
    }


    //encapsulated results from computation
    return res;
}

int
main(int argc, char** argv)
{
    int v = 5;
    int w = 55;

    int num_tests = 10'000;
    // int num_tests = 10;

    std::cout << " hello " << std::endl;

    int invalid = 0;
    result* _res = new result();

    // do
    // {
    //     _res = floyd_warshall(v, w);
    // } while (_res->neg_cycle == false);

    for(int i = 0; i < num_tests; i++)
    {
        _res = floyd_warshall(v, w);
        if(_res->neg_cycle) invalid++;
    }

    float perc = (float)invalid / num_tests;
    std::cout << "Invalid Graphs Generated: " << std::setprecision(3) << perc << std::endl;
    
    std::cout << "goodbye " << std::endl;

}
