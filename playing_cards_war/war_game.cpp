#include "war_game.h"

void reset_variables(unsigned int& war_count, unsigned int& battle_count, unsigned int& p1w, unsigned int& p2w, unsigned long long int& all_battles, unsigned int& all_wars, unsigned int& mx, unsigned int& mn, unsigned int& wmx, unsigned int& wmn) {
	// resets vairables between sets of games
	war_count = battle_count = p1w = p2w = all_battles = all_wars = mx = mn = wmx = wmn = 0;
}

void card_names(unsigned int a) {
	// Prints correct card names based on the card strength
	if (a == 11) cout << "J";
	else if (a == 12) cout << "Q";
	else if (a == 13) cout << "K";
	else if (a == 14) cout << "AS";
	else if (a == 15) cout << "JOKER";
	else cout << a;
	cout << ", ";
}

void print_decks(vector < unsigned int> deck1, vector < unsigned int> deck2) {
	// Prints current state of both players
	cout << "Player 1 cards: " << deck1.size() << endl;
	for (int i = 0; i < deck1.size(); i++)
		card_names(deck1[i]);
	cout << endl << endl << "Player 2 cards: " << deck2.size() << endl;
	for (int i = 0; i < deck2.size(); i++)
		card_names(deck2[i]);
	cout << endl << "--------------------------------------------------------" << endl;
}

void prepare_decks(vector < unsigned int>& p1, vector < unsigned int>& p2) {
	// Prepares decks for both players for new game of war.
	unsigned int cards[56], temp;
	for (int i = 0; i < 56; i++)
		cards[i] = i / 4 + 2; // creating initial 56 card deck

	unsigned int k = 56;
	for (int i = 0; i < 28; i++) {
		// picking cards for 1st deck
		temp = rand() % k--;
		p1.push_back(cards[temp]);
		for (int i = temp; i < k; i++)
			cards[i] = cards[i + 1];
		// picking cards for 2nd deck
		temp = rand() % k--;
		p2.push_back(cards[temp]);
		for (int i = temp; i < k; i++)
			cards[i] = cards[i + 1];
	}
}

void transfer_cards(vector < unsigned int>& p1, vector < unsigned int>& p2, unsigned int p1size, unsigned int p2size, unsigned int k) {
	// Transfers cards won by one player from the deck of second player
	for (int i = 1; i <= k; i++)
		p1.insert(p1.begin(), p1[p1size - 1]);
	for (int i = 1; i <= k; i++)
		p1.insert(p1.begin(), p2[p2size - i]);
	for (int i = 1; i <= k; i++) {
		p1.pop_back();
		p2.pop_back();
	}
}

void encounter(vector < unsigned int>& p1, vector < unsigned int>& p2, unsigned int& war_count) {
	// Calculates outcome of a single encounter within a game 
	unsigned int p1size = p1.size(); // deck size, player 1
	unsigned int p2size = 56 - p1size; // deck size, player 2
	unsigned int k = 1; // amount of cards to transfer
	while (true) {
		// if you don't have enough cards to play war, you loose
		if (p1size < k) {
			p1.clear();
			break;
		}
		if (p2size < k) {
			p2.clear();
			break;
		}
		if (p1[p1size - k] > p2[p2size - k]) { // player 1 have stronger card
			transfer_cards(p1, p2, p1size, p2size, k);
			break;
		}
		if (p1[p1size - k] < p2[p2size - k]) { // player 2 have stronger card
			transfer_cards(p2, p1, p2size, p1size, k);
			break;
		}
		k += 2; // increments in case when both players have the same cards
		war_count++;
	}
}

void game(vector < unsigned int>& p1, vector < unsigned int>& p2, unsigned int& war_count, unsigned int& all_battles, bool isPrint, unsigned int& p1w, unsigned int& p2w) {
	// playes one full game
	prepare_decks(p1, p2);

	all_battles = 0; // amount of battles played in a game
	war_count = 0; // amount of wars played in a game
	while (!p1.empty() && !p2.empty()) { // game will continue until both players have cards in their decks
		all_battles++; // counts number of encounters in single game
		if (isPrint) {
			print_decks(p1, p2); // Printing decks of players only if picked one game to play, only if option 3 from menu is choosen
		}
		encounter(p1, p2, war_count); // calculating outcome of one encounter
	}
	// game ends
	if (p2.empty()) p1w++; // adding points for players after game, based on who won
	if (p1.empty()) p2w++;
	p1.clear(); // clearing decks for next game
	p2.clear();
}

void print_result(int start, int p1w, int p2w, unsigned long long int all_battles, int aot, int all_wars, int mx, int mn, int wmx, int wmn) {
	// Printing statistics based on many games played
	system("cls");
	cout << "Statistics from " << aot << " games: " << endl;
	cout << endl << "Time of execution: " << float(clock() - start) / 1000 << " s" << endl;
	cout << "Player 1 won " << p1w << " games" << endl;
	cout << "Player 2 won " << p2w << " games" << endl;
	cout << "Average amount of battles in game: " << all_battles / aot << endl;
	cout << "Average amount of wars in game: " << all_wars / aot << endl;
	cout << "Maximal amount of battles: " << mx << endl;
	cout << "Minimal amount of battles: " << mn << endl;
	cout << "Maximal amount of wars: " << wmx << endl;
	cout << "Minimal amount of wars: " << wmn << endl << endl;
}

void percent_print(int i, int aot) {
	// Prints percent of games already played.
	system("cls");
	cout << "Percent of games played: " << roundf(float(i) / float(aot) * 100) << " %" << endl;
}

void collect_stats(vector < unsigned int>& p1, vector < unsigned int>& p2, unsigned int& war_count, unsigned int& battle_count, unsigned int& p1w, unsigned int& p2w, unsigned long long int& all_battles, unsigned int& all_wars, unsigned int& mx, unsigned int& mn, unsigned int& wmx, unsigned int& wmn) {
	// adds statistics of new game to stats of previous games
	if (mn > battle_count || mn == 0) mn = battle_count;
	if (mx < battle_count) mx = battle_count;
	if (wmn > war_count || wmn == 0) wmn = war_count;
	if (wmx < war_count) wmx = war_count;
	all_battles += battle_count; // adding amount of battles in last game to counter of all battles
	all_wars += war_count;
}

void menu(vector < unsigned int>& p1, vector < unsigned int>& p2, unsigned int& war_count, unsigned int& battle_count, unsigned int& p1w, unsigned int& p2w, unsigned long long int& all_battles, unsigned int& all_wars, unsigned int& mx, unsigned int& mn, unsigned int& wmx, unsigned int& wmn) {
	// command line interface
	char x;
	cout << "This program plays war, the card game.\n\n";
	cout << "Menu:\n1. What is that game?\n2. Play war many times and see statistics.\n3. Play war once and display status of decks after each battle.\n4. Exit.\n\nInput: ";
	cin >> x;
	switch (x) {
	case '1':
		system("cls");
		cout << "Standard war game, bigger card wins, and winner gets both cards. Game ends when one of the players doesn't have cards.\nWhen cards drawn from the decks are equal, war starts, players put one card up side down and second one fights.\n\n";
		break;
	case '2': {
		int aog; // amount of games
		cout << "How many times would you like to play?: ";
		cin >> aog;
		clock_t start = clock(); // for measurement of time in which a set of games was played
		for (int i = 0; i < aog; i++) {
			game(p1, p2, war_count, battle_count, false, p1w, p2w); // plays one full game
			if (!(i % 1000))
				percent_print(i, aog);
			collect_stats(p1, p2, war_count, battle_count, p1w, p2w, all_battles, all_wars, mx, mn, wmx, wmn);
		}
		print_result(start, p1w, p2w, all_battles, aog, all_wars, mx, mn, wmx, wmn);
		break;
	}
	case '3':
		game(p1, p2, war_count, battle_count, true, p1w, p2w); // plays one full game
		break;
	case '4':
		exit(0);
		break;
	}
	system("pause");
	system("cls");
	reset_variables(war_count, battle_count, p1w, p2w, all_battles, all_wars, mx, mn, wmx, wmn);
	menu(p1, p2, war_count, battle_count, p1w, p2w, all_battles, all_wars, mx, mn, wmx, wmn);
}