#include "round.h"

#include <stdexcept>

namespace cribslvr {

Round::Round()
{
	//deal random cards to the dealer and pone and select a turn card
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

	return outcome;
}

}