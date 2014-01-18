objects = card.o hand.o solver.o

cribslvr : $(objects) tests
	./tests

tests : $(objects)
	g++ test.cpp -lUnitTest++  -o tests $(objects)

solver.o : solver.cpp solver.h card.o hand.o
	g++ solver.cpp -c 

hand.o : hand.cpp hand.h card.o
	g++ hand.cpp -c

card.o : card.cpp card.h
	g++ card.cpp -c
 
.PHONY : clean
clean:
	-rm $(objects) tests