#include <unittest++/UnitTest++.h>
#include "card.h"
#include "hand.h"
#include <stdexcept>

#include <set>

using namespace cribslvr;

Hand* setupTestHand(std::string cards[6])
{
	Card card_array[6] = {Card(cards[0]),
							Card(cards[1]), 
							Card(cards[2]), 
							Card(cards[3]), 
							Card(cards[4]), 
							Card(cards[5]),
						}; 
	return new Hand(card_array);
}


TEST(CardConstruction)
{
	Card test_card(cribslvr::SPADE, 3);
	CHECK_EQUAL(3, test_card.getNumber());
	CHECK_EQUAL(cribslvr::SPADE, test_card.getSuit());
}

TEST(CardConstructionWithCode)
{
	Card card_S1("S1");
	CHECK(Card(SPADE, 1) == card_S1);
	Card card_H1("H1");
	CHECK(Card(HEART, 1)==card_H1);
	Card card_C1("C1");
	CHECK(Card(CLUB, 1) == card_C1);
	Card card_D1("D1");
	CHECK(Card(DIAMOND, 1) == card_D1);
}

TEST(CardConstructionWithCodeErrors)
{
	CHECK_THROW(Card card_(""), std::invalid_argument);
	CHECK_THROW(Card card_S0("S0"), std::invalid_argument);
	CHECK_THROW(Card card_S14("S14"), std::invalid_argument);
	CHECK_THROW(Card card_X3("X3"), std::invalid_argument);
}

TEST(CardComparison)
{
	Card low_card(cribslvr::SPADE, 3);
	Card high_card(cribslvr::SPADE, 4);
	CHECK(low_card < high_card);
	CHECK(!(high_card < low_card));
	CHECK(!(high_card < high_card));
}

TEST(CardComparisonSameNumber)
{
	Card low_card(cribslvr::CLUB, 4);
	Card high_card(cribslvr::SPADE, 4);
	CHECK(low_card < high_card);
}

TEST(CardPrint)
{
	Card test_card(cribslvr::SPADE, 9);
	CHECK_EQUAL("S9", test_card.print());

	Card card1(cribslvr::SPADE, 10);
	CHECK_EQUAL("S10", card1.print());
}


TEST(HandPrint)
{
	std::string cards[6] = {"S9", "H10", "D10", "C8", "S8", "S6"};
	Hand* test_hand = setupTestHand(cards);

	CHECK_EQUAL("S6\nC8\nS8\nS9\nH10\nD10\n", test_hand->print());

	delete test_hand;
}

TEST(HandDiscard)
{
	std::string cards[6] = {"S9", "H10", "D10", "C8", "S8", "S6"};
	Hand* test_hand = setupTestHand(cards);

	test_hand->discard(Card("S9"), Card("H10"));
	std::set<Card> *dis = test_hand->getDiscarded();
	CHECK(!(dis->find(Card("S9"))==dis->end()));
	CHECK(!(dis->find(Card("H10"))==dis->end()));
	CHECK_EQUAL(dis->size(), 2);

	std::set<Card> *keepers = test_hand->getKeepers();
	CHECK_EQUAL(keepers->size(), 4);

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

	Card cards[6] = {card1, card2, card3, card4, card5, card6};

	Hand test_hand(cards);
	test_hand.discard(card1, card6);	//leaves 2 pair in the hand
	//CHECK_EQUAL(4, test_hand.countPoints(card7));

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

	Card cards[6] = {card1, card2, card3, card4, card5, card6};

	Hand test_hand(cards);
	test_hand.discard(card5, card6);
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

	Card cards[6] = {card1, card2, card3, card4, card5, card6};

	Hand test_hand(cards);
	test_hand.discard(card5, card6);
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

	Card cards[6] = {card1, card2, card3, card4, card5, card6};

	Hand test_hand(cards);
	test_hand.discard(card5, card6);
	//CHECK_EQUAL(3, test_hand.countPoints(card7));
}

TEST(HandCountPointsQuadRun)
{
	std::string cards[6] = {"S10", "S11", "C12", "C13", "C1", "C2"};
	Hand* test_hand = setupTestHand(cards);

	test_hand->discard(Card("C2"), Card("C1"));
	CHECK_EQUAL(4, test_hand->countPoints(Card("C1")));
}

TEST(HandCountDoubleRun)
{

	std::string cards[6] = {"S10", "S11", "S12", "C6", "C1", "C2"};
	Hand* test_hand = setupTestHand(cards);

	test_hand->discard(Card("C2"), Card("C1"));
	CHECK_EQUAL(8, test_hand->countPoints(Card("C10")));

	delete test_hand;
}

TEST(HandCount15s)
{
	std::string cards[6] = {"S5", "S10", "S11", "S13", "C1", "C2"};
	Hand* test_hand = setupTestHand(cards);

	test_hand->discard(Card("C2"), Card("C1"));
	CHECK_EQUAL(6, test_hand->countPoints(Card("C1")));
	CHECK_EQUAL(14, test_hand->countPoints(Card("C5")));
	delete test_hand;

}

TEST(HandCountFlush)
{
	std::string cards[6] = {"S10", "S12", "S13", "S8", "C1", "C2"};
	Hand* test_hand = setupTestHand(cards);

	test_hand->discard(Card("C1"), Card("C2"));
	CHECK_EQUAL(5, test_hand->countPoints(Card("S1")));

	delete test_hand;
}

TEST(HandCountRightJack)
{
	std::string cards[6] = {"S1", "S2", "S6", "C11", "H10", "H12"};
	Hand* test_hand = setupTestHand(cards);

	test_hand->discard(Card("H10"), Card("H12"));
	CHECK_EQUAL(1, test_hand->countPoints(Card("C10")));

	delete test_hand;
}

TEST(HandCountNeatHands)
{
	std::string cards[6] = {"S5", "C5", "H2", "D1", "S1", "S2"};
	Hand* test_hand = setupTestHand(cards);

	test_hand->discard(Card("S1"), Card("S2"));
	CHECK_EQUAL(8, test_hand->countPoints(Card("D5")));

	delete test_hand;

	std::string cards2[6] = {"S5", "C5", "H5", "D11", "C1", "C2"};
	test_hand = setupTestHand(cards2);

	test_hand->discard(Card("C1"), Card("C2"));
	CHECK_EQUAL(29, test_hand->countPoints(Card("D5")));
	delete test_hand;
}



int main()
{
	return UnitTest::RunAllTests();
}