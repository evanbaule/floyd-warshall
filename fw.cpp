// C++ Program to check if there is a negative weight
// cycle using Floyd Warshall Algorithm
#include <iostream>
#include <stdlib.h>
#include <time.h>
//#include <omp.h>

#include "fw.hpp"

using namespace std;

// returns encapsulated results for each test case
result*
floyd_warshall(int v, int edge_chance, int i)
{
    result* res = new result(); //encapsulated results

    // int dist[v][v]; //holds distance of shortest path between two given nodes i & j for dist[i][j]
    // util/results for path reconstruction
    // int next[v][v];
    int g[v][v]; //graph adjacency matrix
    int paths[v][v];
    

    //randomly generated values
    int generated;
    int weight;

    unsigned long long seed = (i*i) ^ std::chrono::system_clock::now().time_since_epoch().count();
    srand(seed);
    //#pragma omp parallel for
    for(int i = 0; i < v; i++)
    {
        //#pragma omp parallel for
        for(int j = 0; j < v; j++)
        {
            generated = rand() % 99;
            weight = (rand() % 8) - 1;
            if (i == j)
            {
                g[i][j] = 0;
            }
            else if ( generated <= edge_chance )
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
    std::cout << "Path matrix: " << std::endl;
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

inline bool
detect_neg_floyd_warshall(int v, int edge_chance, int i)
{
    //randomly generated values
    int g[v][v]; //graph adjacency matrix randomly generated
    int generated;
    int weight;

    unsigned long long seed = (i*i) ^ std::chrono::system_clock::now().time_since_epoch().count();
    srand(seed);

    for(int i = 0; i < v; i++)
    {
        for(int j = 0; j < v; j++)
        {
            generated = rand() % 99;
            weight = (rand() % 10) - 1;
            if (i == j)
            {
                g[i][j] = 0;
            }
            else if ( generated <= edge_chance )
            {
                g[i][j] = weight;
            }
            else 
            {
                g[i][j] = INF;
            }
        }
    }

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
                } 
            }
        }
    }

    //Check for a negative cycle in the resulting matrix
    //Negative cycles represented by negative path between a vertex and itself
    for (int i = 0; i < v; i++)
        if (g[i][i] < 0)
            return true;
    return false;
}

int
main(int argc, char** argv)
{
    int v = 10;
    int w = 10;

    //int num_tests = 1'000;
    //int num_tests = 10;

    std::cout << " Simulation Start: " << std::endl;

    //Generate results for invalid graph generation
    int invalid = 0;
    int invalid_results_25[4] = {0, 0, 0, 0};
    int invalid_results_50[4] = {0, 0, 0, 0};
    int invalid_results_75[4] = {0, 0, 0, 0};
    int invalid_results_100[4] = {0, 0, 0, 0};
    result* _res = new result();

    int density, d;
    for(int i = 0; i < 3; i++)
    {
        v = std::pow(10, i);
        std::cout << "Graph size: " <<  v << std::endl;
        for(int j = 0; j < 10'000; j++)
        {
            if(detect_neg_floyd_warshall(v, 25, j)) invalid_results_25[i]++;
            if(detect_neg_floyd_warshall(v, 50, j)) invalid_results_50[i]++;
            if(detect_neg_floyd_warshall(v, 75, j)) invalid_results_75[i]++;
            if(detect_neg_floyd_warshall(v, 100, j)) invalid_results_100[i]++;
        }
    }

    std::cout << "Results for neg cycle detection: " << std::endl;

    for(int i = 0; i < vexp; i++)
    {
        std::cout << invalid_results_25[i];
        if(i < vexp - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    
    for(int i = 0; i < vexp; i++)
    {
        std::cout << invalid_results_50[i];
        if(i < vexp - 1) std::cout << ", ";
    }
    std::cout << std::endl;

    for(int i = 0; i < vexp; i++)
    {
        std::cout << invalid_results_75[i];
        if(i < vexp - 1) std::cout << ", ";
    }
    std::cout << std::endl;

    for(int i = 0; i < vexp; i++)
    {
        std::cout << invalid_results_100[i];
        if(i < vexp - 1) std::cout << ", ";
    }
    std::cout << std::endl;


    // Timing stuff
    // auto start_outer = std::chrono::system_clock::now();
    // auto end_outer = std::chrono::system_clock::now();
    // double tdiff_outer = std::chrono::duration<double>(end_outer-start_outer).count();
    // std::cout << "Total time taken for " << num_tests << " graphs: " << std::setprecision(4) << tdiff_outer << " ns" << std::endl;

    // for(int i = 0; i < num_tests; i++)
    // {
    //     _res = floyd_warshall(v, w, i);

    //     //keep track of how many bad graphs we get
    //     if(_res->neg_cycle) invalid++;
    // }
    
    // float perc = (float)invalid / num_tests; //% of all graphs generated 
    // perc *= 100;
    // std::cout << "Invalid Graphs Generated: " << std::setprecision(3) << perc  << "\%"<< std::endl;
    
    std::cout << "goodbye " << std::endl;

}
