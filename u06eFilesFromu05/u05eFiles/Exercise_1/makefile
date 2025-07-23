#OPT = -O3

all: optimize

optimize: optimize.cpp functions.cpp
	g++ $(OPT) -fopenmp -o optimize optimize.cpp functions.cpp

clean:
	rm -f *.o *~ optimize

