#include <unittest++/UnitTest++.h>

#include "../solver.h"
#include "../hand.h"
#include "../card.h"
#include <stdexcept>
#include <iostream>


using namespace cribslvr;

SUITE(SolverTests)
{


	TEST(PossibilitiesTest)
	{
		Card cards[6] = {Card("S1"), Card("S2"), Card("S3"), Card("S10"), Card("C6"), Card("C13")};
		Hand hand(cards);
		hand.discard(Card("C6"), Card("C13"));
		Solver solver(hand); 
		PossibilityMap probabilites = solver.findScoringPossibilites();
		CHECK_EQUAL(probabilites[1].size(), 0);
		CHECK_EQUAL(probabilites[5].size(), 9);
		CHECK_EQUAL(probabilites[7].size(), 15);
		CHECK_EQUAL(probabilites[8].size(), 3);
		CHECK_EQUAL(probabilites[9].size(), 3);
		CHECK_EQUAL(probabilites[10].size(), 3);
		CHECK_EQUAL(probabilites[12].size(), 11);
		CHECK_EQUAL(probabilites[13].size(), 1);
		CHECK_EQUAL(probabilites[14].size(), 3);
		CHECK_EQUAL(probabilites[15].size(), 0);
	}

	TEST(DiscardForPointsTest)
	{
		Card cards[6] = {Card("S1"), Card("S2"), Card("S3"), Card("S4"), Card("S5"), Card("S6")};
		Hand hand(cards);
		Solver solver(hand);
		std::vector<DiscardOutcome> outcomes = solver.discardForMaxPoints();
		CHECK_EQUAL(15, outcomes.size());	//6-choose-2
	}




}