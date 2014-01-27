#include <unittest++/UnitTest++.h>
#include "../card.h"
#include "../hand.h"
#include <stdexcept>

#include <set>

using namespace cribslvr;


SUITE(cardtests){

TEST(AllCardsSizeTest)
{
	CHECK_EQUAL(52, Card::all_cards.size());
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
	CHECK_THROW(Card card_S14("S15"), std::invalid_argument);
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

}


