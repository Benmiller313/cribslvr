#ifndef CSROUND_H
#define CSROUND_H 

#include "hand.h"
#include "playerHand.h"
#include "card.h"

#include <utility>


namespace cribslvr {

struct HandOutcome{
	int dealer_points;
	int pone_points;
	int crib_points;
	Card turn_card;
	HandOutcome(Card card):turn_card(card){ }
};

class Round { 
public:
	Round();

	PlayerHand& getDealersHand();
	PlayerHand& getPonesHand();
	HandOutcome runHand();

private:
	PlayerHand dealers_hand;
	PlayerHand pones_hand;
	Card turn_card;

};
}

#endif