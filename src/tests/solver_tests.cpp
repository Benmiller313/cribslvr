#include <unittest++/UnitTest++.h>

#include "../solver.h"
#include "../hand.h"
#include "../card.h"

using namespace cribslvr;

SUITE(SolverTests)
{
	TEST(AllCardsSizeTest)
	{
		CHECK_EQUAL(52, Solver::all_cards.size());
	}

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


}