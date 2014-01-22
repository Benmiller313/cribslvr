objects = card.o hand.o solver.o
test_objects = card_tests.o hand_tests.o solver_tests.o

cribslvr : $(objects) utest
	./utest

solver.o : solver.cpp solver.h card.o hand.o
	g++ solver.cpp -c 

hand.o : hand.cpp hand.h card.o
	g++ hand.cpp -c

card.o : card.cpp card.h
	g++ card.cpp -c

utest : $(test_objects) $(objects)
	g++ tests/main.cpp -lUnitTest++  -o utest $(objects) $(test_objects)

card_tests.o : tests/card_tests.cpp card.o
	g++ tests/card_tests.cpp -c

hand_tests.o : tests/hand_tests.cpp hand.o card.o
	g++ tests/hand_tests.cpp -c

solver_tests.o : tests/solver_tests.cpp solver.o
	g++ tests/solver_tests.cpp -c

 
.PHONY : clean
clean:
	-rm $(objects) $(test_objects) utest