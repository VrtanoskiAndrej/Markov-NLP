CXX=mpic++
CCFLAGS=-Wall -g -std=c++11
# activate for compiler optimizations:
#CCFLAGS=-Wall -O3
OBJDIR="build"

all: markov

markov: main.o utils.o markov_matrix.o
	$(CXX) $(LDFLAGS) -o $@ $^

clean:
	rm -f *.o markov