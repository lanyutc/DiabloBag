#ifndef __DIABLOBAG_HPP__
#define __DIABLOBAG_HPP__

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define __STDC_FORMAT_MACROS 
#include <inttypes.h>
#undef __STDC_FORMAT_MACROS

/* s_loc and i_length/width are unnecessary for real diablo3 probablely.
 * I guess that there is other position for keeping detailed infomation of target item. */
struct bag_unit {
	uint64_t item_uid;   /* item unique id. */

	uint32_t s_loc;      /* when this unit carrys item, 
						  * record the item starting location in the bag. from 1...*/

	uint16_t i_length;   /* item length */
	uint16_t i_width;    /* item width */
};

class DiabloBag
{
	public:
		DiabloBag(void):b_length(default_l), b_width(default_w) {
			bag = new bag_unit[b_length * b_width];
			swap_unit = new bag_unit;
			if (!bag || !swap_unit) {
				printf("DiabloBag construct failed l:%"PRIu16" w:%"PRIu16"\n", b_length, b_width);
			}
			printf("DiabloBag construct sucessfully l:%"PRIu16" w:%"PRIu16"\n", b_length, b_width);
		}

		DiabloBag(uint16_t length, uint16_t width):b_length(length), b_width(width) {
			bag = new bag_unit[b_length * b_width];
			swap_unit = new bag_unit;
			if (!bag || !swap_unit) {
				printf("DiabloBag construct failed l:%"PRIu16" w:%"PRIu16"\n", b_length, b_width);
			}
			printf("DiabloBag construct sucessfully l:%"PRIu16" w:%"PRIu16"\n", b_length, b_width);
		}

		~DiabloBag(void) {
			delete [] bag;
			delete swap_unit;
		}


	public:
		/* 
		 * Usage: when bag is cloesed and nothing is on hand, 
		          system will pick item automaticly.
	     * Return: 1. flase means that bag has not enough vacancy for 'new' item.
				   2. true means that automatic place item sucessfully.
		 */
		bool auto_pick_up_items(struct bag_unit *item);

		/* 
		 * Usage: place the item on hand in the target location(target_loc).
	     * Return: 1. NULL means that some parameter are illegal.
				   2. what return value equal item means that place failed, item is still on hand.
				   3. what return value is zero(not NULL) means that place in empty vacancy without exchange,
				      so nothing on hand.
				   4. what return value is not equal item means that place in one item vacancy with exchange,
				      so the item in the bag originally is on hand now.
		 */
		struct bag_unit *place_items(struct bag_unit *item, uint32_t target_loc);

		/* Put the item in the bag on hand */
		struct bag_unit *get_item(struct bag_unit *item, uint32_t target_loc);

		/* for test */
		void print_bag_cond();


	private:
		/* return : pos % b_length */
		inline uint16_t l_pos(uint32_t pos) {
			while (pos > b_length) 
				pos -= b_length;
			return pos;
		}

		/* return : pos / b_length */
		inline uint16_t w_pos(uint32_t pos) {
			uint16_t w = 0;
			while (pos > b_length) {
				pos -= b_length;
				w++;
			}
			return w;
		}

		inline uint32_t calc_s_loc(uint16_t l_pos , uint16_t w_pos) {
			return ((uint32_t)w_pos * (uint32_t)b_length + (uint32_t)l_pos);
		}

		inline void cp_unit(struct bag_unit *des, const struct bag_unit *src) {
			memcpy(des, src, sizeof(struct bag_unit));
		}
		
		inline void clear_swap() {
			memset(swap_unit, 0, sizeof(struct bag_unit));
		}

		inline void set_item(struct bag_unit *item, uint32_t target_loc) {
			item->s_loc = target_loc + 1;
			for (int i = 0; i < item->i_width; i++) {
				for (int j = 0; j < item->i_length; j++) {
					struct bag_unit *cur_unit = &(bag[target_loc + calc_s_loc(j, i)]);
					cp_unit(cur_unit, item);
				}
			}
		}

		/* Target location only one item allowed. */
		inline bool swap_item(struct bag_unit *item, uint32_t target_loc) {
			for (int i = 0; i < item->i_width; i++) {
				for (int j = 0; j < item->i_length; j++) {
					uint32_t pos = target_loc + calc_s_loc(j, i);
					if (pos >= (uint32_t)b_length * (uint32_t)b_width) {
						return false;
					}
					struct bag_unit *cur_unit = &(bag[pos]);
					if (cur_unit->item_uid != no_item && swap_unit->item_uid == no_item) {
						cp_unit(swap_unit, cur_unit);
						continue;
					}
					if (cur_unit->item_uid != no_item && swap_unit->item_uid != cur_unit->item_uid) {
						return false;
					}
				}
			}
			return true;
		}

		inline bool find_vacancy(struct bag_unit *item, uint32_t target_loc) {
			for (int i = 0; i < item->i_width; i++) {
				for (int j = 0; j < item->i_length; j++) {
					uint32_t pos = target_loc + calc_s_loc(j, i);
					if (pos >= (uint32_t)b_length * (uint32_t)b_width) {
						return false;
					}
					struct bag_unit *cur_unit = &(bag[pos]);
					if (cur_unit->item_uid != no_item) {
						return false;
					}
				}
			}
			return true;
		}

		inline void free_item_vacancy(struct bag_unit *item) {
			struct bag_unit empty = {0};
			for (int i = 0; i < item->i_width; i++) {
				for (int j = 0; j < item->i_length; j++) {
					struct bag_unit *cur_unit = &(bag[item->s_loc + calc_s_loc(j, i) - 1]);
					if (cur_unit->item_uid == item->item_uid) {
						cp_unit(cur_unit, &empty);
					}
				}
			}
		}



	private:
		enum {
			/* This is Diablo3 bag size(10x8) */
			default_l = 10,
			default_w = 6,

			no_item = 0,
			no_pos	= 0,
		};


	private:
		uint16_t b_length;     /* bag length */
		uint16_t b_width;      /* bag width  */
		struct bag_unit *bag;  /* bag space, capacity is b_length X b_width */
		struct bag_unit *swap_unit; /* swap space, for temporary storage of information exchange of item */
};

#endif
