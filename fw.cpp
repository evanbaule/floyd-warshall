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
            weight = (rand() % 10);
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
                    std::cout << "{ " << g[i][j] << " }\t";
                }
                else
                {
                    std::cout << "{ \u221E }\t"; 
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
                    std::cout << "{ " << g[i][j] << " }\t";
                }
                else
                {
                    std::cout << "{ \u221E }\t"; 
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
                std::cout << "{ " << paths[i][j] << " }\t";
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
    int v = 25;
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
    
    int timing_sample_size = 10'000;
    std::vector<int>sample_sizes = {1'000, 10, 5, 3};
    unsigned long long seed;
    result* _res = new result();
    double tdiff;

    /*

    BEGIN 10x10

    */

    //Simulate with 25% density
    v = 10;
    std::vector<double> total_times = { 0, 0, 0, 0};
    for(int i = 0; i < sample_sizes[0]; i++)
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
        auto start_time = std::chrono::system_clock::now();
        floyd_warshall(v, 25, seed, false);
        auto end_time = std::chrono::system_clock::now();
        tdiff = std::chrono::duration_cast<std::chrono::microseconds>(end_time-start_time).count();
        std::cout << "Test #: " << i << ", " << v << " nodes, " << "25% density, " << std::setprecision(5) << tdiff << " \u03BCs taken. " << std::endl;
        total_times[0] += tdiff;
    }

    //Simulate with 50% density
    for(int i = 0; i < sample_sizes[0]; i++)
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
        auto start_time = std::chrono::system_clock::now();
        floyd_warshall(v, 50, seed, false);
        auto end_time = std::chrono::system_clock::now();
        tdiff = std::chrono::duration_cast<std::chrono::microseconds>(end_time-start_time).count();
        std::cout << "Test #: " << i << ", " << v << " nodes, " << "50% density, " << std::setprecision(5) << tdiff << " \u03BCs taken. " << std::endl;
        total_times[1] += tdiff;
    }

    //
    //Simulate with 75% density
    for(int i = 0; i < sample_sizes[0]; i++)
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
        auto start_time = std::chrono::system_clock::now();
        floyd_warshall(v, 75, seed, false);
        auto end_time = std::chrono::system_clock::now();
        tdiff = std::chrono::duration_cast<std::chrono::microseconds>(end_time-start_time).count();

        std::cout << "Test #: " << i << ", " << v << " nodes, " << "75% density, " << std::setprecision(5) << tdiff << " \u03BCs taken. " << std::endl;
        total_times[2] += tdiff;
    }

    //
    //Simulate with 100% density
    for(int i = 0; i < sample_sizes[0]; i++)
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
        auto start_time = std::chrono::system_clock::now();
        floyd_warshall(v, 100, seed, false);
        auto end_time = std::chrono::system_clock::now();
        tdiff = std::chrono::duration_cast<std::chrono::microseconds>(end_time-start_time).count();

        std::cout << "Test #: " << i << ", " << v << " nodes, " << "100% density, " << std::setprecision(5) << tdiff << " \u03BCs taken. " << std::endl;
        total_times[3] += tdiff;
    }

    /*

    BEGIN 100X100

    */

    //Simulate with 25% density
    v = 100;
    std::vector<double> total_times2 = { 0, 0, 0, 0}; //100x100
    for(int i = 0; i < sample_sizes[1]; i++)
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
        auto start_time = std::chrono::system_clock::now();
        floyd_warshall(v, 25, seed, false);
        auto end_time = std::chrono::system_clock::now();
        tdiff = std::chrono::duration_cast<std::chrono::microseconds>(end_time-start_time).count();

        std::cout << "Test #: " << i << ", " << v << " nodes, " << "25% density, " << std::setprecision(5) << tdiff << " \u03BCs taken. " << std::endl;
        total_times2[0] += tdiff;
    }

    //Simulate with 50% density
    for(int i = 0; i < sample_sizes[1]; i++)
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
        auto start_time = std::chrono::system_clock::now();
        floyd_warshall(v, 50, seed, false);
        auto end_time = std::chrono::system_clock::now();
        tdiff = std::chrono::duration_cast<std::chrono::microseconds>(end_time-start_time).count();

        std::cout << "Test #: " << i << ", " << v << " nodes, " << "50% density, " << std::setprecision(5) << tdiff << " \u03BCs taken. " << std::endl;
        total_times2[1] += tdiff;
    }

    //
    //Simulate with 75% density
    for(int i = 0; i < sample_sizes[1]; i++)
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
        auto start_time = std::chrono::system_clock::now();
        floyd_warshall(v, 75, seed, false);
        auto end_time = std::chrono::system_clock::now();
        tdiff = std::chrono::duration_cast<std::chrono::microseconds>(end_time-start_time).count();

        std::cout << "Test #: " << i << ", " << v << " nodes, " << "75% density, " << std::setprecision(5) << tdiff << " \u03BCs taken. " << std::endl;
        total_times2[2] += tdiff;
    }

    //
    //Simulate with 100% density
    for(int i = 0; i < sample_sizes[1]; i++)
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
        auto start_time = std::chrono::system_clock::now();
        floyd_warshall(v, 100, seed, false);
        auto end_time = std::chrono::system_clock::now();
        tdiff = std::chrono::duration_cast<std::chrono::microseconds>(end_time-start_time).count();

        std::cout << "Test #: " << i << ", " << v << " nodes, " << "100% density, " << std::setprecision(5) << tdiff << " \u03BCs\t taken. " << std::endl;
        total_times2[3] += tdiff;
    }

    /*

    BEGIN 1000X1000

    */

    //
    //Simulate with 25% density
    v = 1000;
    std::vector<double> total_times3 = { 0, 0, 0, 0}; //100x100
    for(int i = 0; i < sample_sizes[2]; i++)
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
        auto start_time = std::chrono::system_clock::now();
        floyd_warshall(v, 25, seed, false);
        auto end_time = std::chrono::system_clock::now();
        tdiff = std::chrono::duration_cast<std::chrono::microseconds>(end_time-start_time).count();

        std::cout << "Test #: " << i << ", " << v << " nodes, " << "25% density, " << std::setprecision(5) << tdiff << " \u03BCs taken. " << std::endl;
        total_times3[0] += tdiff;
    }

    //Simulate with 50% density
    for(int i = 0; i < sample_sizes[2]; i++)
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
        auto start_time = std::chrono::system_clock::now();
        floyd_warshall(v, 50, seed, false);
        auto end_time = std::chrono::system_clock::now();
        tdiff = std::chrono::duration_cast<std::chrono::microseconds>(end_time-start_time).count();

        std::cout << "Test #: " << i << ", " << v << " nodes, " << "50% density, " << std::setprecision(5) << tdiff << " \u03BCs taken. " << std::endl;
        total_times3[1] += tdiff;
    }

    //
    //Simulate with 75% density
    for(int i = 0; i < sample_sizes[2]; i++)
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
        auto start_time = std::chrono::system_clock::now();
        floyd_warshall(v, 75, seed, false);
        auto end_time = std::chrono::system_clock::now();
        tdiff = std::chrono::duration_cast<std::chrono::microseconds>(end_time-start_time).count();

        std::cout << "Test #: " << i << ", " << v << " nodes, " << "75% density, " << std::setprecision(5) << tdiff << " \u03BCs taken. " << std::endl;
        total_times3[2] += tdiff;
    }

    //
    //Simulate with 100% density
    for(int i = 0; i < sample_sizes[2]; i++)
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
        auto start_time = std::chrono::system_clock::now();
        floyd_warshall(v, 100, seed, false);
        auto end_time = std::chrono::system_clock::now();
        tdiff = std::chrono::duration_cast<std::chrono::microseconds>(end_time-start_time).count();

        std::cout << "Test #: " << i << ", " << v << " nodes, " << "100% density, " << std::setprecision(5) << tdiff << " \u03BCs\t taken. " << std::endl;
        total_times3[3] += tdiff;
    }

    /*
    REPORT RESULTS
    */

    std::cout << "---------------------------------------------------------------------------------" << std::endl;
    std::cout << "| Density(%)\t| 10x10\t\t| 100x100\t| 1000x1000\t|" << std::endl;
    
    std::cout << "---------------------------------------------------------------------------------" << std::endl;
    for(unsigned int i = 0; i < total_times.size(); i++)
    {
        int d = i + 1;
        d *= 25;
        std::cout 
            << "| " << d << "\t\t|" 
            << std::setprecision(5) << total_times[i] / sample_sizes[0] << " \u03BCs\t|" 
            << std::setprecision(5) << (total_times2[i] / sample_sizes[1]) / 1'000 << " ms\t|" 
            << std::setprecision(5) << (total_times3[i] / sample_sizes[2]) / 1'000'000 << " s\t|"
            << std::endl;
    }
    std::cout << "---------------------------------------------------------------------------------" << std::endl;

    delete _res;

    // auto end_outer = std::chrono::system_clock::now();
    // double tdiff_outer = std::chrono::duration<double>(end_outer-start_outer).count();
    // std::cout << "Total time taken for " << num_tests << " graphs: " << std::setprecision(4) << tdiff_outer << " ns" << std::endl;

    // std::cout << "------------------------------------------------------" << std::endl;

    // /*
    //     Force Spawn Specific Matrices known to have demonstrable results
    // */
    // std::vector<unsigned long long> seeds = 
    // { 
    //     62135695,
    //     22382654,
    //     98039086,
    //     2710561,
    //     6948897,
    //     659456, //example seed
    //     2670848
    // };
    // for(unsigned int i = 0; i < seeds.size(); i++)
    // {
        
    //     std::cout << "------------------------------------------------------" << std::endl;
    //     std::cout << "------------------------ i: " << i << " ------------------------" << std::endl;
    //     std::cout << "------------------------------------------------------" << std::endl;

    //     //try to get as 'random' seed as possible
    //     seed = seeds[i];

    //     //print seed given
    //     std::cout << "Random Generator Seed: " << seed << std::endl;

    //     //run algorithm
    //     floyd_warshall(5, 25, seed, true);
    // }

    // std::cout << "------------------------------------------------------" << std::endl;
}