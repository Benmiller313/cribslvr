#include "hand.h"
#include <vector>
#include <sstream>

#include <map>

#include <iostream>
#include <vector>
#include <stdexcept>

namespace cribslvr{


Hand::Hand(std::vector<Card>::iterator begin, std::vector<Card>::iterator end)
{
	while(begin != end){
		keepers.insert(*begin);
		begin++;
	}
}


Hand::Hand(Card input_cards[4]) : keepers(input_cards, input_cards+4)
{
	
}


std::string Hand::print() const
{
	std::stringstream ret;
	for(std::set<Card>::iterator i = keepers.begin(); i != keepers.end(); ++i){
		ret << (*i).print() << std::endl;

	}
	return ret.str();
}


const std::set<Card>& Hand::getKeepers() const 
{
	return keepers;
}


int Hand::countPoints(Card turn_card) const
{
	std::set<Card> full_hand(keepers);
	full_hand.insert(turn_card);

	int points = 0;

	int prev_num = 0;
	bool running = true;
	std::set<Card> run;

	Suit flush_suit = turn_card.getSuit();
	bool flush = true;

	std::set<Card>::iterator i = full_hand.end();
	std::map<int, int> of_a_kinds;
	for(std::set<Card>::iterator i = full_hand.begin(); i != full_hand.end(); i++){
		of_a_kinds[i->getNumber()]++;
		if(flush && i->getSuit() != flush_suit){
			flush = false;
		}
		if (!(*i == turn_card) && i->getNumber()==11 && i->getSuit()==turn_card.getSuit()){
			points++;	//"The right jack"
		}
		if(running){
			if(run.size() == 0 || i->getNumber() == prev_num+1){ 
				run.insert(*i);
				prev_num = i->getNumber();
			}
			else if (i->getNumber() != prev_num){
				if(run.size() < 3){
					run.clear();
					run.insert(*i);
					prev_num = i->getNumber();
				} 
				else{
					running = false;
				}
			}
		}
	}

	for(std::map<int, int>::iterator i = of_a_kinds.begin(); i != of_a_kinds.end(); i++){
		if(i->second == 2){
			//std::cout << "dubs" << std::endl;
			points+=2;
		}
		if(i->second == 3){
			//std::cout << "trips" << std::endl;
			points+=6;
		}
		if(i->second == 4){
			//std::cout << "Quads" << std::endl;
			points+= 12;
		}
	}

	//tabulate the run. 
	if(run.size() > 2){
		int run_score = run.size();
		for(std::set<Card>::iterator i = run.begin(); i!=run.end(); i++){
			run_score *= of_a_kinds[i->getNumber()];
		}
		//std::cout << "runs: " << run_score <<std::endl;
		points += run_score;
	}
	//std::cout << "15 points: " << count15s(turn_card) << std::endl;
	points += count15s(turn_card)*2;
	if(flush){
		points+=5;
	}
	return points;
}

/*
 *	Look at all 2, 3, 4 and 5 combinations of a hand
 *	and see if they add up to 15. 
 *	Combination is where we currently are in the search.
 *	It is a set of cards less than 15. If the next card
 *	in the hand is too large, we no longer need to test
 *	the current combination further. 
 */
int Hand::count15s(std::set<Card> combination, std::set<Card> remaining) const
{
	/*std::cout << "Current combo: " << std::endl;
	printCardSet( combination );
	std:: cout << "Current remaining" << std::endl;
	printCardSet( remaining);
	std::cout << std::endl;*/
	if(remaining.size() == 0){
		return 0;	//No more 15s
	}
	int fifteens = 0;
	int current_sum = sumCards(combination);
	for(std::set<Card>::iterator i = remaining.begin(); i != remaining.end(); i++){
		if (current_sum + i->getValue() > 15){
			return fifteens;
		}
		if (current_sum + i->getValue() == 15){
			fifteens++;
		}
		else{
			//so we can add a card to make less than 15. 
			std::set<Card> new_combination(combination);
			new_combination.insert(*i);
			std::set<Card>::iterator rest = i;
			std::set<Card> new_remaining(++rest, remaining.end());
			fifteens += count15s(new_combination, new_remaining);
		}

	}

	return fifteens;
}

int Hand::count15s(const Card& turn_card) const
{
	std::set<Card> empty;
	std::set<Card> full_hand(keepers);
	full_hand.insert(turn_card);
	return count15s(empty, full_hand);
}

int Hand::sumCards(const std::set<Card>& cards) const
{
	int sum = 0;
	for(std::set<Card>::const_iterator i = cards.begin(); i != cards.end(); i++){
		sum += i->getValue();
	}
	return sum;
}

void Hand::addCards(std::set<Card> newCards)
{
	std::set<Card>::iterator i;
	for(i=newCards.begin(); i!= newCards.end(); i++){
		keepers.insert(*i);
	}
	return;
}

}
