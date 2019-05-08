#Evan M. Baule
#C428 - Computer Networks Project 2

all: comp_all
comp_all: fw.cpp
	g++ --std=c++17 fw.cpp -o fw
	# g++ --std=c++17 -Wall -Wextra -pedantic -fopenmp fw.cpp -o fw

clean:
	rm -f *.out *.o fw

run: all
	./fw 10 50

runs: all	
	./fw 5 50