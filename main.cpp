// Program created by Szymon Pucher

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>

using namespace std;

void card_names(unsigned int a){
    if (a == 11) cout << "J";
    else if (a == 12) cout << "Q";
    else if (a == 13) cout << "K";
    else if (a == 14) cout << "AS";
    else if (a == 15) cout << "JOKER";
    else cout << a;
    cout << ", ";
}
int menu(){
    int x;
    cout << "\n1. What is that game?\n2. Play war many times and see statistics.\n3. Play war one game and display status of decks after each battle.\n4. Exit.\n\nInput: ";
    cin >> x;
    return x;
}
int main()
{
    unsigned int cards[56]; // array with all cards, array with number of wins by player, counter of number of counters.
    unsigned int g;
    vector < unsigned int> p1, p2; // player 1 cards, player 2 cards

    srand(time(NULL));
    cout << "This program plays war, the card game.\n";
    while(g != 4){
            unsigned int temp, k, aot, mx=0, mn=0, avg=0, counter, p1w=0, p2w=0,p1size,p2size;
            g = menu();
            system("cls");
            if(g == 1){
                cout << "Standard war game, bigger card wins, and winner gets both cards. Game ends when one of the players doesn't have cards.\nWhen cards drawn from the decks are equal, war starts, players put one card up side down and second one fights.\n";

            }
            if(g == 2 || g == 3){
                if(g==2){
                    cout << "How many times would you like to play?: ";
                    cin >> aot;
                }
                else aot = 1;
                clock_t start = clock();

                for(int i = 0; i < aot; i++){

                    for(int i = 0; i < 56; i++)
                        cards[i] = i/4 + 2; // filling the deck of cards

                    k = 56;
                    for(int i = 0; i < 28; i++){ // picking cards for 1st deck
                        temp = rand() % k--;
                        p1.push_back(cards[temp]);
                        for(int i = temp; i < k; i++)
                            cards[i] = cards[i+1];
                    }
                    for(int i = 0; i < 28; i++){ // picking cards for 2nd deck
                        temp = rand() % k--;
                        p2.push_back(cards[temp]);
                        for(int i = temp; i < k; i++)
                            cards[i] = cards[i+1];
                    }

                    counter = 0; // default value of counter before war starts
                    // Game starts!
                    while(!p1.empty() && !p2.empty()){ // game will continue until both players have cards in their decks
                        counter++; // counts number of encounters in single game
                        k=1; // used for wars

                        // Printing decks of players only if picked one game to play
                        if(g == 3){
                            cout << "Player 1 cards: " << p1.size() << endl;
                            for(int i = 0; i < p1.size(); i++)
                                card_names(p1[i]);
                            cout << endl << endl << "Player 2 cards: " << p2.size() << endl;
                            for(int i = 0; i < p2.size(); i++)
                                card_names(p2[i]);
                            cout << endl << "--------------------------------------------------------" << endl;
                        }

                        p1size = p1.size();
                        p2size = 56 - p1size;
                        while(true){
                            if(p1size < k){
                                p1.clear();
                                break;
                            }
                            if(p2size < k){
                                p2.clear();
                                break;
                            }
                            if ( p1[p1size-k] > p2[p2size-k] ){ // player 1 have stronger card
                                for(int i = 1; i <= k; i++)
                                    p1.insert(p1.begin(), p1[p1size-1]);
                                for(int i = 1; i <= k; i++)
                                    p1.insert(p1.begin(), p2[p2size-i]);
                                for(int i = 1; i <= k; i++){
                                    p1.pop_back();
                                    p2.pop_back();
                                }
                                break;
                            }
                            if ( p1[p1size-k] < p2[p2size-k] ){ // player 2 have stronger card
                                for(int i = 1; i <= k; i++)
                                    p2.insert(p2.begin(), p2[p2size-1]);
                                for(int i = 1; i <= k; i++)
                                    p2.insert(p2.begin(), p1[p1size-i]);
                                for(int i = 1; i <= k; i++){
                                    p1.pop_back();
                                    p2.pop_back();
                                }
                                break;
                            }
                            k += 2; // increments in case when both players have the same cards
                        }
                    }
                    // Game ends! ---------------------------
                    if (p2.empty()) p1w++; // adding points for players after game, based on who won
                    if (p1.empty()) p2w++;
                    p1.clear(); // clearing vectors for next game
                    p2.clear();

                    //cout << "Amount of trials in game: " << counter << endl;

                    if (mn > counter || mn == 0) mn = counter; // checking mimimal value
                    if (mx < counter) mx = counter; // checking maximal value
                    avg += counter; // caluclating avg

                }

                cout << endl << "Time of execution: " << clock() - start << " ms" << endl;

                cout << "Player 1 won: " << p1w << " wars" << endl;
                cout << "Player 2 won: " << p2w << " wars" << endl;
                cout << "Average amount of battles in war: " << avg/aot << endl;
                cout << "Max of battles: " << mx << endl;
                cout << "Min of battles: " << mn << endl;
        }
    }
    return 0;
}
