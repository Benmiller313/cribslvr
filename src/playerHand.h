#ifndef CSPLAYERHAND_H
#define CSPLAYERHAND_H

#include "hand.h"

namespace cribslvr {

class PlayerHand : public Hand {
public:	
	PlayerHand();
	PlayerHand(Card cards[6]);
	void dealCards();
	void discard(Card first_card, Card second_card);
	int countPoints(Card turn_card) const;

	const std::set<Card>& getDiscarded() const;
	const std::set<Card>& getCards() const;

private:
	std::set<Card> discarded;
	std::set<Card> cards;
};



}

#endif