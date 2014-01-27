#include "card.h"

#include <sstream>
#include <stdexcept>
#include <set>

namespace cribslvr
{

const std::set<Card> Card::all_cards = Card::generateAllCards();

Card::Card(std::string code)
{
	if (code.size() != 2 && code.size()!= 3){
		throw std::invalid_argument("Need a proper card code.");
	}

	switch (code.at(0)){
	case 'S':
		suit = SPADE;
		break;
	case 'C':
		suit = CLUB;
		break;
	case 'H':
		suit = HEART;
		break;
	case 'D':
		suit = DIAMOND;
		break;
	default:
		throw std::invalid_argument("Card code must start with a proper suit code.");
	}
	std::stringstream ss(code.substr(1));
	ss >> number;
	if(number < 1 || number > 13){
		throw std::invalid_argument("Card number must be between 1 and 13.");
	}
}

int Card::getValue() const
{
	return number<10 ? number : 10;
}

bool Card::operator< (const Card& other_card) const
{
	if(number==other_card.number){
		return suit < other_card.suit;
	}
	return number<other_card.number; 
}

bool Card::operator== (const Card& other_card) const
{
	return (number == other_card.number && suit == other_card.suit);
}

int Card::getNumber() const
{
	return number;
}

Suit Card::getSuit() const
{
	getNumber();
	return suit;
}

std::string Card::print() const
{
	std::stringstream ret;
	switch(suit){
	case SPADE:
		ret << "S";
		break;
	case CLUB:
		ret << "C";
		break;
	case HEART:
		ret << "H";
		break;
	case DIAMOND:
		ret << "D";
		break;
	}
	ret << number;
	return ret.str();
}

std::set<Card> Card::generateAllCards()
{
	std::set<Card> all_cards;
	for(int suitIterator = HEART; suitIterator <= SPADE; suitIterator++){
		for(int card_num = 1; card_num < 14; card_num++){
			all_cards.insert(Card(static_cast<Suit>(suitIterator), card_num));
		}
	}
	return all_cards;
}


}