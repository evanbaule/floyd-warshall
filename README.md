# floyd-warshall
# CS375 Presentation source code : Floyd-Warshall Algorithm
# Evan Baule, Colin Sherland

Type 'make' to compile the source fw.cpp into fw
Type 'make run' or ./fw to run the program
    - as it stands the program takes ~2 minutes to run on my computer with macos
    - the current state of the program generates and runs tests from the sizes in     std::vector<int>sample_sizes on line 258, if you want to tweak them so that the program runs faster you can change those values
        //Multiple each # by 4 since we run for 4 different density groups
        sample_sizes[0] = # of tests where V = 10
        sample_sizes[1] = # of tests where V = 100
        sample_sizes[2] = # of tests where V = 1000
        sample_sizes[3] = # of tests where V = 10'000 (this code doesnt even exist so you can ignore this number I think, 10'000x10'0000 is way too big)

    Changing dev_print to 'true' in fw.hpp will make the program print out tests results as it processes them (this will spam the output stream unless the test case #s are very low, it should output 3 matrices per test)

The uncommented portion of the code only runs the simulation with positive weights
if you want to try and run the rejection method graph generation function (detect_neg_floyd_warshall() instead of floyd_warshall), you can try uncommenting out some of the commented portions of the main function but those haven't been maintaind through the development process and might not work, the primary goal of that section was to determine the % of graphs we were generating that were unusable