# Entfernenn Sie das '#' in der n�chsten Zeile, um Compileroptimierungen
# einzuschalten.
#OPT = -O

# all: integrate

# integrate: integrate.cpp
# 	mpic++ $(OPT) -o integrate integrate.cpp

# clean:
# 	rm -f *.o *.c~ integrate
 

# Entfernen Sie das '#' in der nächsten Zeile, um Compileroptimierungen einzuschalten.
#OPT = -O

# Compiler
CXX = mpic++
OPT ?=

# Targets
all: integrate temp

integrate: integrate.cpp
	$(CXX) $(OPT) -o integrate integrate.cpp

temp: temp.cpp
	$(CXX) $(OPT) -o temp temp.cpp

clean:
	rm -f *.o *.c~ integrate temp

