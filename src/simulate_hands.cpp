#include "discardTables.h"
#include "round.h"
#include "solver.h"

#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace cribslvr;

int main()
{	
	srand(time(NULL));
		for(int i = 0; i < 100000; i++){
			if(i %10==0){
				std::cout << DiscardTables::getTables()->print();
				std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
			}
			Round sim;
			Solver dealer_solver(sim.getDealersHand(), true);
			Solver pone_solver(sim.getPonesHand(), false);
			std::vector<DiscardOutcome> out = dealer_solver.discardForMaxPoints();
			sim.getDealersHand().discard(out[0].discarded_cards.first, out[0].discarded_cards.second);
			out = pone_solver.discardForMaxPoints();
			sim.getPonesHand().discard(out[0].discarded_cards.first, out[0].discarded_cards.second);
			HandOutcome doneHand = sim.runHand();	
			DiscardTables::getTables()->saveTables();
		}
		std::cout << DiscardTables::getTables()->print();
}
