#ifndef CSDISCARDOUTCOME_H
#define CSDISCARDOUTCOME_H

#include "card.h"

#include <string>
#include <map>
#include <set>
#include <vector>



namespace cribslvr{

typedef std::map<int, std::vector<Card> > PossibilityMap;
typedef std::map<int, double> ProbabilityMap;

struct DiscardOutcome{
	std::pair<Card, Card> discarded_cards;
	std::set<Card> keepers;
	PossibilityMap possibilities;
	ProbabilityMap probabilities;
	double expected_score;

	DiscardOutcome(Card first, Card second) : discarded_cards(first, second){};
	std::string print();
	
	bool operator> (const DiscardOutcome&) const;

};


}

#endif