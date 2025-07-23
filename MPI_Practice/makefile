PROGS = rahmen pingpong ring ring1 ring2 vecmult vecmult2 vecmult3 \
        pingpong2 ring3 mpi_practice
SRC = makefile $(addsuffix .cpp, $(PROGS))
PRE =

all: $(PROGS)

%: %.cpp
	$(PRE) mpic++ -o $* $*.cpp

clean:
	rm -f *.o *.clog *.clog2 *.slog2 *~
	rm -f $(PROGS)

install: clean
	rm -f $(HOME)/mnt/lab/PV/04/*
	cp $(SRC) $(HOME)/mnt/lab/PV/04
	rm -f /tmp/04Code.zip
	cd ..; zip /tmp/04Code.zip $(addprefix 04/, $(SRC))
	cp /tmp/04Code.zip ${HOME}/public_html/vl/gen/pv
