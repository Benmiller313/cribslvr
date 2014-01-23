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
int Solver::discardForMaxPoints()
{


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