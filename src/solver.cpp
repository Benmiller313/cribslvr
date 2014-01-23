#include "solver.h"

#include <iostream>

namespace cribslvr {


 
const std::set<Card> Solver::all_cards = Solver::generateAllCards();

/*
 *	Iterate over all possible discards. 
 * 	For each discard, check each possible
 * 	cut or turn card. Calculate what points 
 *	you would score. 
 */
std::vector<DiscardOutcome> Solver::discardForMaxPoints()
{
	std::vector<DiscardOutcome> outcome_list;
	for(std::set<Card>::iterator i=hand.getKeepers().begin(); i!=hand.getKeepers().end(); i++){
		std::set<Card>::iterator next = i;
		next++;
		for(std::set<Card>::iterator j=next; i!=hand.getKeepers().end(); i++){
			hand.discard(*i, *j);
			//prepare the elements for the DiscardOutcome:
			struct DiscardOutcome outcome(*i, *j);
			outcome.possibilities = findScoringPossibilites();
			//probabilites is derivative of poss.
			deriveProbabilites(outcome.possibilities, outcome.probabilities);
			outcome.expected_score = 0;
			//Expected value equals the sum of all X*Probability(X) for possible scores X
			for(ProbabilityMap::iterator i=outcome.probabilities.begin(); i!=outcome.probabilities.end(); i++){
				outcome.expected_score += i->first*i->second;	
			}
			outcome_list.push_back(outcome);
		}
	}
	return outcome_list;
}

PossibilityMap Solver::findScoringPossibilites() const
{
	PossibilityMap probabilites;
	int total_hands = 0;

	for(std::set<Card>::iterator i = all_cards.begin(); i!=all_cards.end(); i++){
		if(hand.getKeepers().find(*i) == hand.getKeepers().end()){	//Card isnt already in the hand
			total_hands++;
			int score = hand.countPoints(*i);
			probabilites[score].push_back(*i);
		}
	}

	return probabilites;
}

void Solver::deriveProbabilites(const PossibilityMap& possibilities, ProbabilityMap& probabilites) const
{

}

std::set<Card> Solver::generateAllCards()
{
	std::set<Card> all_cards;
	for(int suitIterator = HEART; suitIterator <= SPADE; suitIterator++){
		for(int card_num = 1; card_num < 14; card_num++){
			all_cards.insert(Card(static_cast<Suit>(suitIterator), card_num));
		}
	}
	return all_cards;
}

}