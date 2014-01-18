#include "solver.h"

namespace cribslvr {



std::set<Card> Solver::allCards = Solver::generateAllCards();

/*
 *	Iterate over all possible discards. 
 * 	For each discard, check each possible
 * 	cut or turn card. Calculate what points 
 *	you would score. 
 */
int Solver::discardForMaxPoints()
{


}

std::map<int, double> Solver::findScoringProbabilites() const
{

}

std::set<Card> Solver::generateAllCards()
{
	std::set<Card> all_cards;
	for(int suitIterator = HEART; suitIterator != SPADE; suitIterator++){
		for(int card_num = 1; card_num < 15; card_num++){
			all_cards.insert(Card(static_cast<Suit>(suitIterator), card_num));
		}
	}

}

}