#include "solver.h"

#include <sstream>

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
			outcome_list.push_back(outcome);
		}
	}
	return outcome_list;
}

PossibilityMap Solver::findScoringPossibilites() const
{
	PossibilityMap probabilities;
	int total_hands = 0;

	for(std::set<Card>::iterator i = all_cards.begin(); i!=all_cards.end(); i++){
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

std::string DiscardOutcome::print()
{
	std::stringstream ret;
	ret.precision(3);
	ret.setf(std::ios::fixed, std::ios::floatfield);
	ret << "Discarded: " << discarded_cards.first.print() << " " << discarded_cards.second.print() << " " << std::endl;
	ret << "Kept: ";
	for(std::set<Card>::iterator i=keepers.begin(); i!=keepers.end(); i++){
		ret << i->print() << " ";
	}
	ret << std::endl;
	for(PossibilityMap::iterator i=possibilities.begin(); i!=possibilities.end(); i++){
		if(i->first != NULL){
			ret << i->first << ": ";
			if(i->first < 10){
				ret << " ";
			}
			ret << "%" << probabilities[i->first]*100 << "\t";
			for(std::vector<Card>::iterator card=i->second.begin(); card!=i->second.end(); card++){
				ret << card->print() << " ";
			}
			ret << std::endl;
		}
	}
	ret << "Expected Score: " << expected_score << std::endl;
	return ret.str();
}

}