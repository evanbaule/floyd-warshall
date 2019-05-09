// C++ Program to check if there is a negative weight
// cycle using Floyd Warshall Algorithm
#include <iostream>
#include <stdlib.h>
#include <time.h>
//#include <omp.h>
#include <iomanip>

#include "fw.hpp"

using namespace std;

// returns encapsulated results for each test case
result*
floyd_warshall(int v, int edge_chance, unsigned long long seed, bool p)
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

    srand(seed);
    //#pragma omp parallel for
    for(int i = 0; i < v; i++)
    {
        //#pragma omp parallel for
        for(int j = 0; j < v; j++)
        {
            generated = rand() % 99;
            weight = (rand() % 8);
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
    if(p)
    {
        std::cout << "------------------------------------------------------" << std::endl;
        std::cout << "Randomized Matrix: " << std::endl;
        for(int i = 0; i < v; i++)
        {
            for(int j = 0; j < v; j++)
            {
                if(g[i][j] < INF - 100)
                {
                    std::cout << "{ " << g[i][j] << " } ";
                }
                else
                {
                    std::cout << "{INF} ";
                }
            }
            cout << endl;
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
    if(p)
    {
        std::cout << "------------------------------------------------------" << std::endl;
        std::cout << "Path Length Matrix: " << std::endl;
        for(int i = 0; i < v; i++)
        {
            for(int j = 0; j < v; j++)
            {
                if(g[i][j] < INF - 100)
                {
                    std::cout << "{ " << g[i][j] << " } ";
                }
                else
                {
                    std::cout << "{INF} ";
                }
            }
            std::cout << std::endl;
        } 
    
        std::cout << "------------------------------------------------------" << std::endl;
        std::cout << "Path Matrix: " << std::endl;
        // Print out the path matrix
        for(int i = 0; i < v; i++)
        {
            for(int j = 0; j < v; j++)
            {
                std::cout << "{ " << paths[i][j] << " } ";
            }
            std::cout << std::endl;
        }

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

    // std::cout << " Simulation Start: " << std::endl;

    // //Generate results for invalid graph generation
    // int invalid = 0;
    // int invalid_results_25 = 0;
    // int invalid_results_50 = 0;
    // int invalid_results_75 = 0;
    // int invalid_results_100 = 0;
    // //result* _res = new result();

    // std::cout << "Graph size: " <<  v << " * " << v << std::endl;
    // int num_tests = 100'000;
    // for(int i = 0; i < num_tests; i++)
    // {
    //     //std::cout << "Test Number: " << j << std::endl;
    //     if(detect_neg_floyd_warshall(v, 25, 25*i)) invalid_results_25++;
    //     if(detect_neg_floyd_warshall(v, 50, 50*i)) invalid_results_50++;
    //     if(detect_neg_floyd_warshall(v, 75, 75*i)) invalid_results_75++;
    //     if(detect_neg_floyd_warshall(v, 100, i)) invalid_results_100++;
    // }

    // std::cout << "Results for neg cycle detection: " << std::endl;

    // float perc = ((float) invalid_results_25 / num_tests) * 100;
    // std::cout << "  - .25 Density Graphs: " << std::setprecision(4) << perc << "% generated are invalid." << std::endl;

    // perc = ((float) invalid_results_50 / num_tests) * 100;
    // std::cout << "  - .50 Density Graphs: " << std::setprecision(4) << perc << "% generated are invalid." << std::endl;

    // perc = ((float) invalid_results_75 / num_tests) * 100;
    // std::cout << "  - .75 Density Graphs: " << std::setprecision(4) << perc << "% generated are invalid." << std::endl;
    
    // perc = ((float) invalid_results_100 / num_tests) * 100;
    // std::cout << "  - 1.00 Density Graphs: " << std::setprecision(4) << perc << "% generated are invalid." << std::endl;

    // std::cout << "--------------------------------------------------------------------------" << std::endl;
    // std::cout << "--------------------------------------------------------------------------" << std::endl;
    // std::cout << "--------------------------------------------------------------------------" << std::endl;
    // auto start_outer = std::chrono::system_clock::now();
    
    unsigned long long seed;
    for(int i = 0; i < 100; i++)
    {
        seed = (i*i*i*i) & ((std::chrono::system_clock::now().time_since_epoch().count()));
        if(dev_print)
        {
            std::cout << "------------------------------------------------------" << std::endl;
            std::cout << "----------------------- i: " << i << " ------------------------" << std::endl;
            std::cout << "------------------------------------------------------" << std::endl;
            std::cout << "Random Generator Seed: " << seed << std::endl;
        }

        //run algorithm
        floyd_warshall(5, 35, seed, false);
    }

    // auto end_outer = std::chrono::system_clock::now();
    // double tdiff_outer = std::chrono::duration<double>(end_outer-start_outer).count();
    // std::cout << "Total time taken for " << num_tests << " graphs: " << std::setprecision(4) << tdiff_outer << " ns" << std::endl;

    std::cout << "------------------------------------------------------" << std::endl;

    /*
        Force Spawn Specific Matrices known to have demonstrable results
    */
    std::vector<unsigned long long> seeds = 
    { 
        62135695,
        22382654,
        98039086,
        2710561,
        6948897,
        659456,
        2670848
    };
    for(unsigned int i = 0; i < seeds.size(); i++)
    {
        
        std::cout << "------------------------------------------------------" << std::endl;
        std::cout << "----------------------- i: " << i << " ------------------------" << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;

        //try to get as 'random' seed as possible
        seed = seeds[i];

        //print seed given
        std::cout << "Random Generator Seed: " << seed << std::endl;

        //run algorithm
        floyd_warshall(5, 35, seed, true);
    }
    std::cout << "------------------------------------------------------" << std::endl;

    std::cout << "goodbye" << std::endl;
}