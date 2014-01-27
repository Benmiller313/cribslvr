#ifndef CSCARD_H
#define CSCARD_H

#include <string>
#include <set>

namespace cribslvr{

enum Suit {HEART, DIAMOND, CLUB, SPADE};

class Card {

public:
	Card(Suit suit, int number):
		suit(suit),
		number(number){}

	/*
	 *	Constructor that accepts the standard card code, 
	 *	Ex: ace of spades = S1
	 */
	Card(std::string);

	int getValue() const;

	bool operator< (const Card&) const;
	bool operator== (const Card&) const;

	std::string print() const;

	//Setters and Getters
	int getNumber() const;
	Suit getSuit() const;

	static const std::set<Card> all_cards;

private:

	 int number;		//Number is the actual number sequence of the card. Ace is 1, King is 13
	 Suit suit;

	 static std::set<Card> generateAllCards();

};
}

#endif