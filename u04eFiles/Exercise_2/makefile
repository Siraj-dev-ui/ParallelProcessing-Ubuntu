# Entfernenn Sie das '#' in der n�chsten Zeile, um Compileroptimierungen
# einzuschalten.
#OPT = -O

all: heat

heat: heat.cpp solver-gauss.cpp
	g++ $(OPT) -fopenmp -o heat heat.cpp solver-gauss.cpp

ViewMatrix.class: ViewMatrix.java
	javac ViewMatrix.java

clean:
	rm -f *.o *~ heat Matrix.txt
	rm -f ViewMatrix.class
 
