#include "diablo_bag.hpp"

bool DiabloBag::auto_pick_up_items(struct bag_unit *item)
{
	if (!item) {
		return false;
	}

	for (int i = 0; i < b_length * b_width; i++) {
		if (find_vacancy(item, i)) {
			set_item(item, i);
			return true;
		}
	}
	return false;
}

struct bag_unit *DiabloBag::place_items(struct bag_unit *item, uint32_t target_loc)
{
	if (!item) {
		return NULL;
	}
	
	if (target_loc >= b_length * b_width) {
		return NULL;
	}

	/* We put the item on the hand first, 
	 * and must clear its record in bag when exchanging. */
	if (item->s_loc != no_pos) {
		free_item_vacancy(item);
	}

	if (!swap_item(item, target_loc)) {
		clear_swap();
		return item;
	}

	/* place item in the bag safely */
	set_item(item, target_loc);

	/* copy swap to item(on hand), notice clear s_loc */
	cp_unit(item, swap_unit);
	item->s_loc = no_pos;

	/* clear swap infomation in the original bag */
	free_item_vacancy(swap_unit);
	clear_swap();
	return item;
}

struct bag_unit *DiabloBag::get_item(struct bag_unit *item, uint32_t target_loc)
{
	if (target_loc >= (uint32_t)b_length * (uint32_t)b_width) {
		return NULL;
	}

	if (!item) {
		return NULL;
	}

	if (bag[target_loc].item_uid == 0) {
		return NULL;
	}
	
	cp_unit(item, &(bag[target_loc]));
	return item;
}

void DiabloBag::print_bag_cond()
{
	for (int i = 0; i < b_width; i++) {
		for (int j = 0; j < b_length; j++) {
			struct bag_unit *cur_unit = &(bag[i * b_length + j]);
			printf("%"PRIu64" ",cur_unit->item_uid);
		}
		printf("\n");
	}
	printf("\n");
}
