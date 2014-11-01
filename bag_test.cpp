#include "diablo_bag.hpp"

uint64_t item_uid = 1LL;

static void construct_item(struct bag_unit *item, uint32_t s_loc, uint16_t i_length, uint16_t i_width)
{
	item->item_uid = item_uid;
	item->s_loc    = s_loc;
	item->i_length = i_length;
	item->i_width  = i_width;
	item_uid ++;
}

static void test_auto_pick(DiabloBag *TestBagOne)
{
	struct bag_unit itemone = {0};
	construct_item(&itemone, 0, 3, 3);
	if (TestBagOne->auto_pick_up_items(&itemone)) {
		TestBagOne->print_bag_cond();
	} else {
		printf("bag full\n");
	}

	for (int i = 0; i < 15; i++) {
		construct_item(&itemone, 0, 1, 3);
		if (TestBagOne->auto_pick_up_items(&itemone)) {
			TestBagOne->print_bag_cond();
		} else {
			printf("bag full\n");
		}
	}

	construct_item(&itemone, 0, 1, 1);
	if (TestBagOne->auto_pick_up_items(&itemone)) {
		TestBagOne->print_bag_cond();
	} else {
		printf("bag full\n");
	}

	construct_item(&itemone, 0, 1, 2);
	if (TestBagOne->auto_pick_up_items(&itemone)) {
		TestBagOne->print_bag_cond();
	} else {
		printf("bag full\n");
	}

	construct_item(&itemone, 0, 1, 3);
	if (TestBagOne->auto_pick_up_items(&itemone)) {
		TestBagOne->print_bag_cond();
	} else {
		printf("bag full\n");
	}
}

static void test_place_item(DiabloBag *TestBagOne)
{
	struct bag_unit *on_hand = new bag_unit;
	on_hand = TestBagOne->get_item(on_hand, 0);
	if (on_hand) {
		printf("item [%"PRIu64" %"PRIu32"] [%"PRIu16" %"PRIu16"] on hand\n", 
				on_hand->item_uid, on_hand->s_loc, on_hand->i_length, on_hand->i_width);
	}

	on_hand = TestBagOne->place_items(on_hand, 1);
	if (on_hand) {
		printf("item [%"PRIu64" %"PRIu32"] [%"PRIu16" %"PRIu16"] on hand\n", 
				on_hand->item_uid, on_hand->s_loc, on_hand->i_length, on_hand->i_width);
		TestBagOne->print_bag_cond();
	}

	on_hand = TestBagOne->place_items(on_hand, 4);
	if (on_hand) {
		printf("item [%"PRIu64" %"PRIu32"] [%"PRIu16" %"PRIu16"] on hand\n", 
				on_hand->item_uid, on_hand->s_loc, on_hand->i_length, on_hand->i_width);
		TestBagOne->print_bag_cond();
	}

	on_hand = TestBagOne->place_items(on_hand, 0);
	if (on_hand) {
		printf("item [%"PRIu64" %"PRIu32"] [%"PRIu16" %"PRIu16"] on hand\n", 
				on_hand->item_uid, on_hand->s_loc, on_hand->i_length, on_hand->i_width);
		TestBagOne->print_bag_cond();
	}

	on_hand = TestBagOne->get_item(on_hand, 40);
	if (on_hand) {
		printf("item [%"PRIu64" %"PRIu32"] [%"PRIu16" %"PRIu16"] on hand\n", 
				on_hand->item_uid, on_hand->s_loc, on_hand->i_length, on_hand->i_width);
	}

	on_hand = TestBagOne->place_items(on_hand, 10);
	if (on_hand) {
		printf("item [%"PRIu64" %"PRIu32"] [%"PRIu16" %"PRIu16"] on hand\n", 
				on_hand->item_uid, on_hand->s_loc, on_hand->i_length, on_hand->i_width);
		TestBagOne->print_bag_cond();
	}

	on_hand = TestBagOne->place_items(on_hand, 39);
	if (on_hand) {
		printf("item [%"PRIu64" %"PRIu32"] [%"PRIu16" %"PRIu16"] on hand\n", 
				on_hand->item_uid, on_hand->s_loc, on_hand->i_length, on_hand->i_width);
		TestBagOne->print_bag_cond();
	}

	on_hand = TestBagOne->place_items(on_hand, 40);
	if (on_hand) {
		printf("item [%"PRIu64" %"PRIu32"] [%"PRIu16" %"PRIu16"] on hand\n", 
				on_hand->item_uid, on_hand->s_loc, on_hand->i_length, on_hand->i_width);
		TestBagOne->print_bag_cond();
	}

	on_hand = TestBagOne->get_item(on_hand, 39);
	if (on_hand) {
		printf("item [%"PRIu64" %"PRIu32"] [%"PRIu16" %"PRIu16"] on hand\n", 
				on_hand->item_uid, on_hand->s_loc, on_hand->i_length, on_hand->i_width);
		TestBagOne->print_bag_cond();
	}

	on_hand = TestBagOne->place_items(on_hand, 30);
	if (on_hand) {
		printf("item [%"PRIu64" %"PRIu32"] [%"PRIu16" %"PRIu16"] on hand\n", 
				on_hand->item_uid, on_hand->s_loc, on_hand->i_length, on_hand->i_width);
		TestBagOne->print_bag_cond();
	}

	on_hand = TestBagOne->place_items(on_hand, 15);
	if (on_hand) {
		printf("item [%"PRIu64" %"PRIu32"] [%"PRIu16" %"PRIu16"] on hand\n", 
				on_hand->item_uid, on_hand->s_loc, on_hand->i_length, on_hand->i_width);
		TestBagOne->print_bag_cond();
	}

	on_hand = TestBagOne->place_items(on_hand, 38);
	if (on_hand) {
		printf("item [%"PRIu64" %"PRIu32"] [%"PRIu16" %"PRIu16"] on hand\n", 
				on_hand->item_uid, on_hand->s_loc, on_hand->i_length, on_hand->i_width);
		TestBagOne->print_bag_cond();
	}

	on_hand = TestBagOne->place_items(on_hand, 0);
	if (on_hand) {
		printf("item [%"PRIu64" %"PRIu32"] [%"PRIu16" %"PRIu16"] on hand\n", 
				on_hand->item_uid, on_hand->s_loc, on_hand->i_length, on_hand->i_width);
		TestBagOne->print_bag_cond();
	}
	delete on_hand;
}

int main()
{
	DiabloBag *TestBagOne = new DiabloBag;
	DiabloBag *TestBagTwo = new DiabloBag(10,10);

	/* at the beginning */
	TestBagOne->print_bag_cond();

	test_auto_pick(TestBagOne);
	test_place_item(TestBagOne);
	delete TestBagOne;
	delete TestBagTwo;
	return 0;
}
