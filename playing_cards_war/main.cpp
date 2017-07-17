/*
	This program plays war, the card game.
	Program created by Szymon Pucher
*/

#include "war_game.h"

int main() {
	/* */
	vector < unsigned int> p1, p2; // player 1 cards, player 2 cards
	unsigned int temp, k, aot, mx = 0, mn = 0, wmn = 0, wmx = 0, battle_count, p1w = 0, p2w = 0, p1size, p2size, all_wars = 0, war_count;
	unsigned long long all_battles = 0;

	srand(time(NULL));

	menu(p1, p2, war_count, battle_count, p1w, p2w, all_battles, all_wars, mx, mn, wmx, wmn);
	return 0;
	/* */


}
