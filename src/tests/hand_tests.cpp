#include <unittest++/UnitTest++.h>
#include "../card.h"
#include "../hand.h"

#include <stdexcept>
#include <set>

using namespace cribslvr;



Hand* setupTestHand(std::string cards[4])
{
	Card card_array[4] = {Card(cards[0]),
							Card(cards[1]), 
							Card(cards[2]), 
							Card(cards[3]), 
						}; 
	return new Hand(card_array);
}

SUITE(HandTests){

TEST(HandConstructor)
{
	Card cards[4] = {Card("S9"), Card("S1"), Card("C1"), Card("C2")};
	Hand test_hand(cards);
	CHECK_EQUAL(4, test_hand.getKeepers().size());
}


TEST(HandPrint)
{
	std::string cards[4] = {"S9", "H10", "D10", "C8"};
	Hand* test_hand = setupTestHand(cards);

	CHECK_EQUAL("C8\nS9\nH10\nD10\n", test_hand->print());

	delete test_hand;
}

TEST(HandCountPointsPairs)
{
	Card card1(cribslvr::SPADE, 9);
	Card card2(cribslvr::HEART, 10);
	Card card3(cribslvr::DIAMOND, 10);
	Card card4(cribslvr::CLUB, 8);
	Card card5(cribslvr::SPADE, 8);
	Card card6(cribslvr::SPADE, 6);
	Card card7(cribslvr::HEART, 13);

	Card cards[4] = {card2, card3, card4, card5};

	Hand test_hand(cards);
		//leaves 2 pair in the hand
	CHECK_EQUAL(4, test_hand.countPoints(card7));

}

TEST(HandCountPointsTrips)
{
	Card card1(cribslvr::SPADE, 10);
	Card card2(cribslvr::HEART, 10);
	Card card3(cribslvr::DIAMOND, 10);
	Card card4(cribslvr::CLUB, 7);
	Card card5(cribslvr::SPADE, 8);
	Card card6(cribslvr::SPADE, 6);
	Card card7(cribslvr::HEART, 13);

	Card cards[4] = {card1, card2, card3, card4};

	Hand test_hand(cards);
	//CHECK_EQUAL(6, test_hand.countPoints(card7));
}

TEST(HandCountPointsQuads)
{
	Card card1(cribslvr::SPADE, 10);
	Card card2(cribslvr::HEART, 10);
	Card card3(cribslvr::DIAMOND, 10);
	Card card4(cribslvr::CLUB, 10);
	Card card5(cribslvr::SPADE, 8);
	Card card6(cribslvr::SPADE, 6);
	Card card7(cribslvr::HEART, 13);

	Card cards[4] = {card1, card2, card3, card4};

	Hand test_hand(cards);
	//CHECK_EQUAL(12, test_hand.countPoints(card7));
}

TEST(HandCountPointsRun)
{
	Card card1(cribslvr::SPADE, 1);
	Card card2(cribslvr::HEART, 2);
	Card card3(cribslvr::DIAMOND, 3);
	Card card4(cribslvr::CLUB, 6);
	Card card5(cribslvr::SPADE, 8);
	Card card6(cribslvr::SPADE, 6);
	Card card7(cribslvr::HEART, 13);

	Card cards[4] = {card1, card2, card3, card4};

	Hand test_hand(cards);
	//CHECK_EQUAL(3, test_hand.countPoints(card7));
}

TEST(HandCountPointsQuadRun)
{
	std::string cards[4] = {"S10", "S11", "C12", "C13"};
	Hand* test_hand = setupTestHand(cards);

	CHECK_EQUAL(4, test_hand->countPoints(Card("C1")));
}

TEST(HandCountDoubleRun)
{

	std::string cards[4] = {"S10", "S11", "S12", "C6"};
	Hand* test_hand = setupTestHand(cards);

	CHECK_EQUAL(8, test_hand->countPoints(Card("C10")));

	delete test_hand;
}

TEST(HandCount15s)
{
	std::string cards[4] = {"S5", "S10", "S11", "S13"};
	Hand* test_hand = setupTestHand(cards);

	CHECK_EQUAL(6, test_hand->countPoints(Card("C1")));
	CHECK_EQUAL(14, test_hand->countPoints(Card("C5")));
	delete test_hand;

}

TEST(HandCountFlush)
{
	std::string cards[4] = {"S10", "S12", "S13", "S8"};
	Hand* test_hand = setupTestHand(cards);

	CHECK_EQUAL(5, test_hand->countPoints(Card("S1")));

	delete test_hand;
}

TEST(HandCountRightJack)
{
	std::string cards[6] = {"S1", "S2", "S6", "C11"};
	Hand* test_hand = setupTestHand(cards);

	CHECK_EQUAL(1, test_hand->countPoints(Card("C10")));

	delete test_hand;
}

TEST(HandCountNeatHands)
{
	std::string cards[4] = {"S5", "C5", "H2", "D1"};
	Hand* test_hand = setupTestHand(cards);

	CHECK_EQUAL(8, test_hand->countPoints(Card("D5")));

	delete test_hand;

	std::string cards2[4] = {"S5", "C5", "H5", "D11"};
	test_hand = setupTestHand(cards2);

	CHECK_EQUAL(29, test_hand->countPoints(Card("D5")));
	delete test_hand;

	std::string cards3[4] = {"S7", "C7", "D7", "H7"};
	test_hand = setupTestHand(cards3);
	CHECK_EQUAL(24, test_hand->countPoints(Card("S1")));
}


}