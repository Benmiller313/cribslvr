#ifndef CSHAND_H
#define CSHAND_H

#include "card.h"
#include <set>
#include <string>

namespace cribslvr{

class Hand{
public:
	Hand(Card cards[6]);
	int countPoints(Card turn_card) const;
	void discard(Card, Card);
	std::string print() const; 

	std::set<Card> const *getCards() const;
	std::set<Card> const *getKeepers() const;
	std::set<Card> const *getDiscarded() const;
private:

	int count15s(std::set<Card> combination, std::set<Card> remaining) const;
	int count15s(const Card& turn_card) const;
	int sumCards(const std::set<Card>& cards) const;

	std::set<Card> const *cards;
	std::set<Card> const *keepers;
	std::set<Card> const *discarded;

};

}

#endif