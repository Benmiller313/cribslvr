#include <unittest++/UnitTest++.h>

#include "../playerHand.h"
#include "../card.h"

#include <stdexcept>

namespace cribslvr {

SUITE(PlayerHandTests)
{
	TEST(NormalConstructor)
	{
		Card cards[6] = {Card("S1"), Card("S2"), Card("S3"), Card("S4"), Card("S5"), Card("S6") };
		PlayerHand test_hand(cards);

		CHECK_EQUAL(6, test_hand.getCards().size());
		CHECK_EQUAL(0, test_hand.getDiscarded().size());
		CHECK_EQUAL(0, test_hand.getKeepers().size());
	}

	TEST(DiscardNormally)
	{
		Card cards[6] = {Card("S9"), Card("H10"), Card("D10"), Card("C8"), Card("S8"), Card("S6")};
		PlayerHand test_hand(cards);

		test_hand.discard(Card("S9"), Card("H10"));
		std::set<Card> const dis = test_hand.getDiscarded();
		CHECK(!(dis.find(Card("S9"))==dis.end()));
		CHECK(!(dis.find(Card("H10"))==dis.end()));
		CHECK_EQUAL(dis.size(), 2);

		std::set<Card> const keepers = test_hand.getKeepers();
		CHECK_EQUAL(keepers.size(), 4);
	}

	TEST(DiscardSameError)
	{
		Card cards[6] = {Card("S9"), Card("H10"), Card("D10"), Card("C8"), Card("S8"), Card("S6")};
		PlayerHand test_hand(cards);

		CHECK_THROW(test_hand.discard(Card("S9"), Card("S9")), std::invalid_argument);
	}

	TEST(DiscardNotFoundError)
	{
		Card cards[6] = {Card("S9"), Card("H10"), Card("D10"), Card("C8"), Card("S8"), Card("S6")};
		PlayerHand test_hand(cards);

		CHECK_THROW(test_hand.discard(Card("S1"), Card("S9")), std::invalid_argument);

	}

}


}