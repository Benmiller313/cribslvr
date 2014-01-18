#ifndef CSHAND_H
#define CSHAND_H

#include "card.h"
#include <set>
#include <string>

namespace cribslvr{

class Hand{
public:
	Hand(Card cards[6]);
	int countPoints(Card turn_card);
	void discard(Card, Card);
	std::string print() const; 

	std::set<Card>* getCards();
	std::set<Card>* getKeepers();
	std::set<Card>* getDiscarded();
private:

	int count15s(std::set<Card> combination, std::set<Card> remaining);
	int count15s(const Card& turn_card);
	int sumCards(const std::set<Card>& cards);

	std::set<Card> *cards;
	std::set<Card> *keepers;
	std::set<Card> *discarded;

};

}

#endif