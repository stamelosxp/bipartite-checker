LEDALIB = '/usr/local/LEDA'
LEDAINCL = '/usr/local/LEDA/incl'
INCL = '../incl'

bipartite_checker: main.o BFS.o
	g++ -O3 -o bipartite_checker main.o BFS.o -lleda -L$(LEDALIB)

BFS.o: ../src/BFS.cpp
	g++ -O3 -c ../src/BFS.cpp -I $(INCL) -I $(LEDAINCL)

main.o: ../src/main.cpp
	g++ -O3 -c ../src/main.cpp -I $(INCL) -I $(LEDAINCL) 

run:
	./bipartite_checker
	
clean: 
	rm -f biparite_checker *.o
