#ifndef CSSOLVER_H
#define CSSOLVER_H

#include "hand.h"

namespace cribslvr{

class Solver{
public:
	Solver(Hand hand):
		hand(hand);
	int discardForMaxPoints();
private:
	Hand hand;
};

}

#endif