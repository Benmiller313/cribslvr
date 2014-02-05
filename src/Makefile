objects = card.o hand.o playerHand.o solver.o DiscardOutcome.o round.o discardTables.o
executables = solve_hand simulate_hands utest
test_objects = card_tests.o hand_tests.o solver_tests.o playerHand_tests.o discardTables_tests.o
flags = -stdlib=libstdc++ -std=c++11

all : $(executables)

solve_hand : $(objects) solve_hand.cpp 
	clang++ $(flags) $(objects) solve_hand.cpp -o solve_hand

simulate_hands : $(objects) simulate_hands.cpp
	clang++ $(flags) $(objects) simulate_hands.cpp -o simulate_hands


discardTables.o : discardTables.cpp discardTables.h
	clang++ $(flags) discardTables.cpp -c

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
	./utest

card_tests.o : tests/card_tests.cpp card.o
	clang++ $(flags) tests/card_tests.cpp -c

hand_tests.o : tests/hand_tests.cpp hand.o card.o
	clang++ $(flags) tests/hand_tests.cpp -c

playerHand_tests.o : tests/playerHand_tests.cpp playerHand.o hand.o card.o
	clang++ $(flags) tests/playerHand_tests.cpp -c

solver_tests.o : tests/solver_tests.cpp solver.o
	clang++ $(flags) tests/solver_tests.cpp -c

discardTables_tests.o : tests/discardTables_tests.cpp discardTables.o round.o
	clang++ $(flags) tests/discardTables_tests.cpp -c

 
.PHONY : clean
clean:
	-rm $(objects) $(test_objects) $(executables)