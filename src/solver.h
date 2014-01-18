#ifndef CSSOLVER_H
#define CSSOLVER_H

#include "hand.h"
#include "card.h"

#include <map>
#include <set>

namespace cribslvr{

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
	std::map<int, double> findScoringProbabilites() const ;

	static std::set<Card> allCards;

private:
	Hand hand;
	
	static std::set<Card> generateAllCards();


};

}

#endif