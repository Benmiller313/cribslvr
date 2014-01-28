#include "playerHand.h"
#include "card.h"

#include <cstdlib>
#include <time.h>
#include <stdexcept>

namespace cribslvr {

PlayerHand::PlayerHand(Card cards[6])
	:Hand(), cards(cards, cards+6)
{

}

PlayerHand::PlayerHand(){
	dealCards();
}


void PlayerHand::dealCards()
{

}

const std::set<Card>& PlayerHand::getCards() const
{
	return cards;
}

const std::set<Card>& PlayerHand::getDiscarded() const
{
	return discarded;
}

void PlayerHand::discard(Card first_card, Card second_card)
{
	if(first_card == second_card){
		throw std::invalid_argument("Error: Cards to discard must be different. (" + first_card.print() + ":" + second_card.print() + ")");
	}
	if(cards.find(first_card) == cards.end()){
		throw std::invalid_argument("Error: Card " + first_card.print() + " is not a part of the hand.");
	}
	if(cards.find(second_card) == cards.end()){
		throw std::invalid_argument("Error: Card " + second_card.print() + " is not a part of the hand.");
	}
	keepers.clear();
	discarded.clear();
	for(std::set<Card>::iterator i = cards.begin(); i != cards.end(); i++){
		if((*i)==first_card || (*i)==second_card){
			discarded.insert(*i);
		}
		else{
			keepers.insert(*i);
		}
	}
}

int PlayerHand::countPoints(Card turn_card) const
{
	if(keepers.size() != 4){
		throw std::logic_error("Must discard before counting points!");
	}
	return Hand::countPoints(turn_card);
}

}