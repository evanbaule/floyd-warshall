//libraries

//headers
#include "fw.hpp"

void
brk(int len)
{
    for(int i = 0; i < len; i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;
}

/*
@ g = graph adjacency matrix
@ w = weighted probability of an edge existing
*/
void
generate(std::vector< std::vector <int> > &g, int w)
{
    //prepare random sample
    //probability of an edge existing
    std::default_random_engine re_edge;
    re_edge.seed(e_seed);
    std::uniform_int_distribution<int> d_edge(0, 100);

    //random weight assigned to each edge
    std::default_random_engine re_weight;
    re_weight.seed(w_seed);
    std::uniform_int_distribution<int> d_weight (1, 10); //negative weights?

    for(unsigned int i = 0; i < g.size(); i++)
    {
        for(unsigned int j = 0; j < g[i].size(); j++)
        {
            // int w = d_weight(re_weight);
            // g[i][j] = w;
            float e = d_edge(re_edge);
            if(i == j)
                g[i][j] = 0;
            else if(e > w)
                g[i][j] = infinity; //no edge
            else
                g[i][j] = d_weight(re_weight); //random weighted edge between ith & jth nodes
        }
    }
}

// prints a semi-formatted matrix to cout
void
print_matrix(std::vector< std::vector <int> > g)
{
    for(unsigned int i = 0; i < g.size(); i++)
    {
        for(unsigned int j = 0; j < g[i].size(); j++)
        {
            if(g[i][j] == 0)
                std::cout << " [ 0 ]";
            else if(g[i][j] == infinity)
                std::cout << " [INF]";
            else
                std::cout << " [ " <<  g[i][j] << " ]";
        }
        std::cout << std::endl;
    }
}

bool floyd_warshall(std::vector< std::vector <int> > g, std::vector< std::vector<int > > &dist)
{
    unsigned int V = g[0].size();
    unsigned int i, j, k;
    /* Initialize the solution matrix same as input 
    graph matrix. Or we can say the initial values  
    of shortest distances are based on shortest
    paths considering no intermediate vertex. */
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
        {
            if(g[i][j] == infinity)
                dist[i][j] = 0;
            else
                dist[i][j] = g[i][j];

            //std::cout << "Updated value: " << dist[i][j] << std::endl;
        }

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
            } 
        } 
    } 

    // If distance of any verex from itself 
    // becomes negative, then there is a negative 
    // weight cycle. 
    for (int i = 0; i < V; i++) 
        if (dist[i][i] < 0) 
            return true;
    return true;  
}

int
main(int argc, char** argv)
{
    std::cout << ".fw <n_nodes>" << std::endl;
    if( argc < 3 ) exit(EXIT_FAILURE);

    int v = atoi(argv[1]); // number of nodes in g
    std::vector< std::vector <int> > g (v, std::vector<int>(v));
    //std::vector< std::vector <float> > g (v, std::vector<float>(v)); // g adj matrix
    int w = atoi(argv[2]); //weighted p of an edge existing

    std::cout << "Matrix construction complete : " << std::endl;
    std::cout << "g = [ " << g.size() << " ]" << " [ " << g[0].size() << " ]" << std::endl;
    print_matrix(g);

    std::cout << "Randomizing g : " << std::endl;
    generate(g, w);
    print_matrix(g);

    brk(brk_len);

    std::vector< std::vector <int> > paths(v, std::vector<int>(v)); // results for fw alg
    print_matrix(paths);
    std::cout << "Running fw algo..." << std::endl;
    if(floyd_warshall(g, paths))
        print_matrix(paths);
}
