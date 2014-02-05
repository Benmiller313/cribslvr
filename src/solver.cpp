#include "solver.h"
#include "discardTables.h"

#include <sstream>
#include <algorithm>
#include <functional>

namespace cribslvr {

Solver::Solver(PlayerHand hand, bool is_dealer)
	:hand(hand), is_dealer(is_dealer)
{
	discard_tables = DiscardTables::getTables();
}

/*
 *	Iterate over all possible discards. 
 * 	For each discard, check each possible
 * 	cut or turn card. Calculate what points 
 *	you would score. 
 */
std::vector<DiscardOutcome> Solver::discardForMaxPoints()
{
	std::vector<DiscardOutcome> outcome_list;
	for(std::set<Card>::iterator i=hand.getCards().begin(); i!=hand.getCards().end(); i++){
		std::set<Card>::iterator next = i;
		next++;
		for(std::set<Card>::iterator j=next; j!=hand.getCards().end(); j++){
			hand.discard(*i, *j);
			//prepare the elements for the DiscardOutcome:
			struct DiscardOutcome outcome(*i, *j);
			outcome.keepers = hand.getKeepers();
			outcome.possibilities = findScoringPossibilites();
			//probabilities is derivative of poss.
			deriveProbabilites(outcome.possibilities, outcome.probabilities);
			outcome.expected_score = 0;
			//Expected value equals the sum of all X*Probability(X) for possible scores X
			for(ProbabilityMap::iterator i=outcome.probabilities.begin(); i!=outcome.probabilities.end(); i++){
				outcome.expected_score += i->first*i->second;	
			}
			if(is_dealer){
				outcome.expected_score += DiscardTables::getTables()->getExpectedValue(is_dealer, i->getNumber(), j->getNumber());
			}
			else{
				outcome.expected_score -= DiscardTables::getTables()->getExpectedValue(is_dealer, i->getNumber(), j->getNumber());
			}
			outcome_list.push_back(outcome);
		}
	}
	sort(outcome_list.begin(), outcome_list.end(), std::greater<DiscardOutcome>());
	return outcome_list;
}

PossibilityMap Solver::findScoringPossibilites() const
{
	PossibilityMap probabilities;
	int total_hands = 0;

	for(std::set<Card>::iterator i = Card::all_cards.begin(); i!=Card::all_cards.end(); i++){
		if(hand.getKeepers().find(*i) == hand.getKeepers().end()){	//Card isnt already in the hand
			total_hands++;
			int score = hand.countPoints(*i);
			probabilities[score].push_back(*i);
		}
	}

	return probabilities;
}


void Solver::deriveProbabilites(const PossibilityMap& possibilities, ProbabilityMap& probabilites) const
{
	for(PossibilityMap::const_iterator i=possibilities.begin(); i!= possibilities.end(); i++){
		probabilites[i->first] = i->second.size()/48.0;

	}
}


}