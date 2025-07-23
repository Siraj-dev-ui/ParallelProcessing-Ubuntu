all: optimize1 optimize2

optimize1: optimize1.cpp functions.cpp
	mpic++ $(OPT) -o optimize1 optimize1.cpp functions.cpp

optimize2: optimize2.cpp functions.cpp
	mpic++ $(OPT) -o optimize2 optimize2.cpp functions.cpp

clean:
	rm -f *.o *~ optimize1 optimize2

