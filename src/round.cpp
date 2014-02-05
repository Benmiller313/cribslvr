#include "round.h"
#include "card.h"
#include "discardTables.h"

#include <stdexcept>
#include <time.h>
#include <cstdlib>
#include <iterator>
#include <algorithm>
#include <set>

namespace cribslvr {

Round::Round()
{
	//deal random cards to the dealer and pone and select a turn card

	std::set<Card> available_cards(Card::all_cards);
	dealers_hand.dealCards(available_cards);
	pones_hand.dealCards(available_cards);


	int forward = rand() % available_cards.size();
	std::set<Card>::iterator i = available_cards.begin();
	std::advance(i, forward);
	turn_card = *i;

}

PlayerHand& Round::getDealersHand() 
{
	return dealers_hand;
}

PlayerHand& Round::getPonesHand() 
{
	return pones_hand;
}

HandOutcome Round::runHand(){
	if(!dealers_hand.hasDiscarded() || !pones_hand.hasDiscarded()){
		throw std::logic_error("Both hands must discard before counting points.");
	}
	HandOutcome outcome(turn_card);
	outcome.dealer_points = dealers_hand.countPoints(turn_card);
	outcome.pone_points = pones_hand.countPoints(turn_card);
	Hand crib;
	crib.addCards(dealers_hand.getDiscarded());
	crib.addCards(pones_hand.getDiscarded());
	outcome.crib_points = crib.countPoints(turn_card);

	//Record the result of the hand in the discard tables. 
	std::set<Card>::iterator i = dealers_hand.getDiscarded().begin();
	DiscardTables::getTables()->publishResult(true, i->getNumber(), (++i)->getNumber(), outcome.crib_points);
	i = pones_hand.getDiscarded().begin();
	DiscardTables::getTables()->publishResult(false, i->getNumber(), (++i)->getNumber(), outcome.crib_points);


	return outcome;
}

}