#ifndef CSHAND_H
#define CSHAND_H

#include "card.h"

#include <set>
#include <string>
#include <vector>


namespace cribslvr{

class Hand{
public:
	Hand(){};
	Hand(Card input_cards[4]);
	Hand(std::vector<Card>::iterator, std::vector<Card>::iterator);
	virtual int countPoints(Card turn_card) const;
	std::string print() const; 
	void addCards(std::set<Card> newCards);

	const std::set<Card>& getKeepers() const;
protected:
	std::set<Card> keepers;

private:

	int count15s(std::set<Card> combination, std::set<Card> remaining) const;
	int count15s(const Card& turn_card) const;
	int sumCards(const std::set<Card>& cards) const;

	
	

};

}

#endif