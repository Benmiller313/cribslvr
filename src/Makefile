objects = card.o hand.o playerHand.o solver.o DiscardOutcome.o round.o
test_objects = card_tests.o hand_tests.o solver_tests.o playerHand_tests.o
flags = -stdlib=libstdc++ -std=c++11

cribslvr : $(objects) utest
	./utest
round.o : round.cpp round.h hand.o card.o playerHand.o
	clang++ $(flags) round.cpp -c

solver.o : solver.cpp solver.h card.o hand.o DiscardOutcome.o
	clang++ $(flags) solver.cpp -c 

DiscardOutcome.o : DiscardOutcome.cpp DiscardOutcome.h
	clang++ $(flags) DiscardOutcome.cpp -c

playerHand.o : playerHand.cpp playerHand.h hand.o
	clang++ $(flags) playerHand.cpp -c

hand.o : hand.cpp hand.h card.o
	clang++ $(flags) hand.cpp -c

card.o : card.cpp card.h
	clang++ $(flags) card.cpp -c



utest : $(test_objects) $(objects)
	clang++ $(flags) tests/main.cpp -lUnitTest++  -o utest $(objects) $(test_objects)

card_tests.o : tests/card_tests.cpp card.o
	clang++ $(flags) tests/card_tests.cpp -c

hand_tests.o : tests/hand_tests.cpp hand.o card.o
	clang++ $(flags) tests/hand_tests.cpp -c

playerHand_tests.o : tests/playerHand_tests.cpp playerHand.o hand.o card.o
	clang++ $(flags) tests/playerHand_tests.cpp -c

solver_tests.o : tests/solver_tests.cpp solver.o
	clang++ $(flags) tests/solver_tests.cpp -c

 
.PHONY : clean
clean:
	-rm $(objects) $(test_objects) utest