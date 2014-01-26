#include "solver.h"
#include "hand.h"
#include "card.h"
#include "DiscardOutcome.h"

#include <iostream>
#include <vector>

using namespace cribslvr;

int main(){
	std::cout << "Enter the cards in your hand: ('S1=Ace of Spades, S13=King of Spades')" <<std::endl;
	std::string card_input;
	std::vector<Card> cards;
	for(int i = 0; i < 6; i++){
		std::cin >> card_input;
		cards.push_back(Card(card_input)); 
	}
	Hand hand(cards.begin(), cards.end());
	Solver hand_solver( hand );	//Im not sure if I'm happy with the interface I've made...
	std::vector<DiscardOutcome> outcomes = hand_solver.discardForMaxPoints();
	for(std::vector<DiscardOutcome>::iterator i=outcomes.begin(); i!=outcomes.end(); i++){
		std::cout << i->print() << std::endl;
	}
}