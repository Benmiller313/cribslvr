#ifndef CSSOLVER_H
#define CSSOLVER_H

#include "playerHand.h"
#include "card.h"
#include "DiscardOutcome.h"

#include <map>
#include <set>
#include <vector>
#include <string>

namespace cribslvr{


class Solver{
public:
	Solver(PlayerHand hand):
		hand(hand){}

	/*
	 *	Given a crib hand, select the two cards to 
	 *	discard for the max expected hand value. 
	 * 	Does not factor in the crib. 
	 */	
	std::vector<DiscardOutcome> discardForMaxPoints();

	/*
	 *	Takes the keepers from a hand and adds all possible 
	 *	turn cards and counts the points. Return a map of the
	 *	points earned and the turn_cards that make those points. 
	 */
	PossibilityMap findScoringPossibilites() const ;

	

private:
	PlayerHand hand;
	
	void deriveProbabilites(const PossibilityMap&, ProbabilityMap&) const;

};

}

#endif

