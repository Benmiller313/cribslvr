#include "DiscardOutcome.h"

#include <sstream>
#include <iostream>

namespace cribslvr {

std::string DiscardOutcome::print()
{
	std::stringstream ret;
	ret.precision(3);
	ret.setf(std::ios::fixed, std::ios::floatfield);
	ret << "Discarded: " << discarded_cards.first.print() << " " << discarded_cards.second.print() << " " << std::endl;
	ret << "Kept: ";
	for(std::set<Card>::iterator i=keepers.begin(); i!=keepers.end(); i++){
		ret << i->print() << " ";
	}
	ret << std::endl;
	for(PossibilityMap::iterator i=possibilities.begin(); i!=possibilities.end(); i++){
		if(i->first != NULL){
			ret << i->first << ": ";
			if(i->first < 10){
				ret << " ";
			}
			ret << "%" << probabilities[i->first]*100 << "\t";
			for(std::vector<Card>::iterator card=i->second.begin(); card!=i->second.end(); card++){
				ret << card->print() << " ";
			}
			ret << std::endl;
		}
	}
	ret << "Expected Score: " << expected_score << std::endl;
	return ret.str();
}

bool DiscardOutcome::operator>(const DiscardOutcome& smaller) const
{
	return expected_score > smaller.expected_score; 
}

}