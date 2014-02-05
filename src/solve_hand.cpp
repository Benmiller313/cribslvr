#include "solver.h"
#include "hand.h"
#include "playerHand.h"
#include "card.h"
#include "DiscardOutcome.h"

#include <string>
#include <iostream>


using namespace cribslvr;

int main(){
	std::string in;
	Card cards[6];
	std::cout << "Enter Your Cards:" << std::endl;
	for(int i=0; i<6; i++){
		std::cin >> in;
		cards[i]=Card(in);
	}
	PlayerHand hand(cards);
	std::cout << "Are you dealing? (y/n)" << std::endl;
	std::cin >> in;
	bool deal = false;
	if(in=="y" || in=="Y"){
		deal = true;
	}

	Solver solver(hand, deal);
	std::vector<DiscardOutcome> out = solver.discardForMaxPoints();
	for(std::vector<DiscardOutcome>::iterator i=out.begin(); i!=out.end(); i++){
		std::cout << i->print() << std::endl;
	}
}