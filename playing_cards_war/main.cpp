// Program created by Szymon Pucher

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <math.h>

using namespace std;

void card_names(unsigned int a) {
	if (a == 11) cout << "J";
	else if (a == 12) cout << "Q";
	else if (a == 13) cout << "K";
	else if (a == 14) cout << "AS";
	else if (a == 15) cout << "JOKER";
	else cout << a;
	cout << ", ";
}
void print_decks(vector < unsigned int> deck1, vector < unsigned int> deck2) {
	cout << "Player 1 cards: " << deck1.size() << endl;
	for (int i = 0; i < deck1.size(); i++)
		card_names(deck1[i]);
	cout << endl << endl << "Player 2 cards: " << deck2.size() << endl;
	for (int i = 0; i < deck2.size(); i++)
		card_names(deck2[i]);
	cout << endl << "--------------------------------------------------------" << endl;
}
int menu() {
	int x;
	cout << "\n1. What is that game?\n2. Play war many times and see statistics.\n3. Play war one game and display status of decks after each battle.\n4. Exit.\n\nInput: ";
	cin >> x;
	return x;
}
void prepare_decks(vector < unsigned int>& p1, vector < unsigned int>& p2) {
	unsigned int cards[56], temp;
	for (int i = 0; i < 56; i++)
		cards[i] = i / 4 + 2; // filling the deck of cards

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
	unsigned int p1size = p1.size();
	unsigned int p2size = 56 - p1size;
	unsigned int k = 1;
	while (true) {
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

void game(vector < unsigned int>& p1, vector < unsigned int>& p2, unsigned int& war_count, unsigned int& counter, int g, unsigned int& p1w, unsigned int& p2w) {
	prepare_decks(p1, p2);

	counter = 0; // default value of counter before war starts
	war_count = 0;
	while (!p1.empty() && !p2.empty()) { // game will continue until both players have cards in their decks
		counter++; // counts number of encounters in single game

				   // Printing decks of players only if picked one game to play, only if option 3 from menu is choosen
		if (g == 3) {
			print_decks(p1, p2);
		}

		encounter(p1, p2, war_count);
	}
	if (p2.empty()) p1w++; // adding points for players after game, based on who won
	if (p1.empty()) p2w++;
	p1.clear(); // clearing vectors for next game
	p2.clear();
}

void print_result(int start, int p1w, int p2w, int all_battles, int aot, int all_wars, int mx, int mn, int wmx, int wmn) {
	system("cls");
	cout << endl << "Time of execution: " << float(clock() - start) / 1000 << " s" << endl;
	cout << "Player 1 won " << p1w << " games" << endl;
	cout << "Player 2 won " << p2w << " games" << endl;
	cout << "Average amount of battles in game: " << all_battles / aot << endl;
	cout << "Average amount of wars in game: " << all_wars / aot << endl;
	cout << "Maximal amount of battles: " << mx << endl;
	cout << "Minimal amount of battles: " << mn << endl;
	cout << "Maximal amount of wars: " << wmx << endl;
	cout << "Minimal amount of wars: " << wmn << endl;
}

void percent_print(int i, int aot) {
	system("cls");
	cout << "Percent of games played: " << roundf(float(i) / float(aot) * 100) << " %" << endl;
}


int main()
{
	unsigned int g;
	vector < unsigned int> p1, p2; // player 1 cards, player 2 cards

	srand(time(NULL));
	cout << "This program plays war, the card game.\n";
	do {
		unsigned int temp, k, aot, mx = 0, mn = 0, wmn = 0, wmx = 0, all_battles = 0, counter, p1w = 0, p2w = 0, p1size, p2size, all_wars = 0, war_count;
		g = menu();
		system("cls");
		if (g == 1) {
			cout << "Standard war game, bigger card wins, and winner gets both cards. Game ends when one of the players doesn't have cards.\nWhen cards drawn from the decks are equal, war starts, players put one card up side down and second one fights.\n";
		}
		if (g == 2 || g == 3) {
			if (g == 2) {
				cout << "How many times would you like to play?: ";
				cin >> aot;
			}
			else aot = 1;
			clock_t start = clock();

			for (int i = 0; i < aot; i++) {
				
				game(p1, p2, war_count, counter, g, p1w, p2w); // plays one full game
				
				if (!(i % 1000)) 
					percent_print(i,aot);

				if (mn > counter || mn == 0) mn = counter; // checking mimimal value
				if (mx < counter) mx = counter; // checking maximal value
				if (wmn > war_count || wmn == 0) wmn = war_count;
				if (wmx < war_count) wmx = war_count;
				all_battles += counter; // adding amount of battles in last game to counter of all battles
				all_wars += war_count;
			}

			print_result(start, p1w, p2w, all_battles, aot, all_wars, mx, mn, wmx, wmn);
		}
	} while (g != 4);
	
	
	return 0;
}
