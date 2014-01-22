#ifndef CSSOLVER_H
#define CSSOLVER_H

#include "hand.h"
#include "card.h"

#include <map>
#include <set>
#include <vector>

namespace cribslvr{

typedef std::map<int, std::vector<Card> > PossibilityMap;

class Solver{
public:
	Solver(Hand hand):
		hand(hand){}

	/*
	 *	Given a crib hand, select the two cards to 
	 *	discard for the max expected hand value. 
	 * 	Does not factor in the crib. 
	 */	
	int discardForMaxPoints();

	/*
	 *	Takes the keepers from a hand and adds all possible 
	 *	turn cards and counts the points. Return a map of the
	 *	points earned and the turn_cards that make those points. 
	 */
	PossibilityMap findScoringPossibilites() const ;

	static const std::set<Card> all_cards;

private:
	Hand hand;
	static std::set<Card> generateAllCards();

};

}

#endif

