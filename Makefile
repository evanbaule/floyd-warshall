#Evan M. Baule
#C428 - Computer Networks Project 2

all: comp_all
comp_all: fw.cpp
	g++ fw.cpp -o fw

clean:
	rm -f *.out *.o fw

run: all
	./fw 10