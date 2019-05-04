//libraries

//headers
#include "fw.hpp"

/*
@ g = graph adjacency matrix
@ w = weighted probability of an edge existing
*/
void
generate(std::vector< std::vector <float>> &g, float w)
{
    //prepare random sample
    //probability of an edge existing
    std::default_random_engine re_edge;
    std::uniform_real_distribution<float> d_edge(0.0, 1.0);

    //random weight assigned to each edge
    std::default_random_engine re_weight;
    std::uniform_real_distribution<float> d_weight (0.0, 1.0); //negative weights?

    for(unsigned int i = 0; i < g.size(); i++)
    {
        std::cout << "row: " << i << std::endl;
        for(unsigned int j = 0; j < g[i].size(); j++)
        {
            std::cout << "col: " << j << std::endl;
            float e = d_edge(re_edge);
            std::cout << "e = " << e << std::endl;
            if(e < w)
                g[i][j] = 0; //no edge
            else
                g[i][j] = d_weight(re_weight); //random weighted edge between ith & jth nodes
        }
    }
}

// prints a semi-formatted matrix to cout
void
print_matrix(std::vector< std::vector <float> > g)
{
    for(unsigned int i = 0; i < g.size(); i++)
    {
        for(unsigned int j = 0; j < g[i].size(); j++)
        {
            std::cout << " [ " << g[i][j] << " ]";
        }
        std::cout << std::endl;
    }
}

int
main(int argc, char** argv)
{
    std::cout << ".fw <n_nodes>" << std::endl;
    if( argc == 1 ) exit(EXIT_FAILURE);

    int v = atoi(argv[1]); //|v|  
    std::vector< std::vector <float>> g (v, std::vector<float>(v));
    float w = 0.50;
    std::cout << "Matrix construction complete : " << std::endl;
    std::cout << "g = [ " << g.size() << " ]" << " [ " << g[0].size() << " ]" << std::endl;
    print_matrix(g);
    std::cout << "Randomizing g : " << std::endl;
    generate(g, w);
    print_matrix(g);

}
