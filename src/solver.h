#ifndef CSSOLVER_H
#define CSSOLVER_H

#include "hand.h"
#include "card.h"

#include <map>
#include <set>
#include <vector>
#include <string>

namespace cribslvr{

typedef std::map<int, std::vector<Card> > PossibilityMap;
typedef std::map<int, double> ProbabilityMap;

struct DiscardOutcome{
	std::pair<Card, Card> discarded_cards;
	PossibilityMap possibilities;
	ProbabilityMap probabilities;
	double expected_score;

	DiscardOutcome(Card first, Card second) : discarded_cards(first, second){};
	std::string print();
};

class Solver{
public:
	Solver(Hand hand):
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

	static const std::set<Card> all_cards;

private:
	Hand hand;
	static std::set<Card> generateAllCards();

	void deriveProbabilites(const PossibilityMap&, ProbabilityMap&) const;

};

}

#endif

