#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <math.h>

using namespace std;

void reset_variables(unsigned int& war_count, unsigned int& battle_count, unsigned int& p1w, unsigned int& p2w, unsigned long long int& all_battles, unsigned int& all_wars, unsigned int& mx, unsigned int& mn, unsigned int& wmx, unsigned int& wmn);
void card_names(unsigned int a);
void print_decks(vector < unsigned int> deck1, vector < unsigned int> deck2);
void prepare_decks(vector < unsigned int>& p1, vector < unsigned int>& p2);
void transfer_cards(vector < unsigned int>& p1, vector < unsigned int>& p2, unsigned int p1size, unsigned int p2size, unsigned int k);
void encounter(vector < unsigned int>& p1, vector < unsigned int>& p2, unsigned int& war_count);
void game(vector < unsigned int>& p1, vector < unsigned int>& p2, unsigned int& war_count, unsigned int& all_battles, bool isPrint, unsigned int& p1w, unsigned int& p2w);
void print_result(int start, int p1w, int p2w, unsigned long long int all_battles, int aot, int all_wars, int mx, int mn, int wmx, int wmn);
void percent_print(int i, int aot);
void collect_stats(vector < unsigned int>& p1, vector < unsigned int>& p2, unsigned int& war_count, unsigned int& battle_count, unsigned int& p1w, unsigned int& p2w, unsigned long long int& all_battles, unsigned int& all_wars, unsigned int& mx, unsigned int& mn, unsigned int& wmx, unsigned int& wmn);
void menu(vector < unsigned int>& p1, vector < unsigned int>& p2, unsigned int& war_count, unsigned int& battle_count, unsigned int& p1w, unsigned int& p2w, unsigned long long int& all_battles, unsigned int& all_wars, unsigned int& mx, unsigned int& mn, unsigned int& wmx, unsigned int& wmn);