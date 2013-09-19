CXX=		/usr/local/bin/g++-4.9

CPPFLAGS=	-I/Users/alberto/Applications/boost \
			-I/Users/alberto/Applications/cplex/include \
			-I/Users/alberto/Applications/concert/include \
			-I/Users/alberto/Applications/maersk \
			-std=c++11 -O3 -DIL_STD

LDFLAGS=	-L/Users/alberto/Applications/cplex/lib/x86-64_darwin/static_pic \
			-L/Users/alberto/Applications/concert/lib/x86-64_darwin/static_pic
					
LDLIBS=		-lcplex -lilocplex -lconcert -lm

OBJS=		base/graph.o \
			base/node.o \
			base/problem.o \
			preprocessing/graph_generator.o \
			preprocessing/problem_data.o \
			preprocessing/program_params.o \
			util/knapsack.o

main: $(OBJS) base/base.h main.cpp
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) $(OBJS) main.cpp -o main

all: main

clean:
	rm $(OBJS)