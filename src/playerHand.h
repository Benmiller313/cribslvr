#ifndef CSPLAYERHAND_H
#define CSPLAYERHAND_H

#include "hand.h"

#include <set>

namespace cribslvr {

class PlayerHand : public Hand {
public:	
	PlayerHand();
	PlayerHand(Card cards[6]);
	void dealCards(std::set<Card>&);
	void discard(Card first_card, Card second_card);
	int countPoints(Card turn_card) const;

	const std::set<Card>& getDiscarded() const;
	const std::set<Card>& getCards() const;
	bool hasDiscarded() const;

private:
	std::set<Card> discarded;
	std::set<Card> cards;
};



}

#endif