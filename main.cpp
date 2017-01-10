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

int main()
{
    unsigned int cards[56]; // array with all cards, array with number of wins by player, counter of number of counters.
    unsigned int temp, k, aot, mx=0, mn=0, avg=0, counter, p1w=0, p2w=0;
    vector < unsigned int> p1, p2; // player 1 cards, player 2 cards
    srand(time(NULL));
    cout << "How many times would you like to play?  ";
    cin >> aot;

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
           /* Printing decks of players * /
            cout << "Player 1 cards: " << p1.size() << endl;
            for(int i = 0; i < p1.size(); i++)
                card_names(p1[i]);
            cout << endl << endl << "Player 2 cards: " << p2.size() << endl;
            for(int i = 0; i < p2.size(); i++)
                card_names(p2[i]);
            cout << endl << "--------------------------------------------------------" << endl;
            /* */

            while(true){
                if ( p1[p1.size()-k] > p2[p2.size()-k] ){ // player 1 have stronger card
                    for(int i = 1; i <= k; i++)
                        p1.insert(p1.begin(), p1[p1.size()-i]);
                    for(int i = 1; i <= k; i++)
                        p1.insert(p1.begin(), p2[p2.size()-i]);
                    for(int i = 1; i <= k; i++){
                        p1.pop_back();
                        p2.pop_back();
                    }
                    break;
                }
                if ( p1[p1.size()-k] < p2[p2.size()-k] ){ // player 2 have stronger card
                    for(int i = 1; i <= k; i++)
                        p2.insert(p2.begin(), p2[p2.size()-i]);
                    for(int i = 1; i <= k; i++)
                        p2.insert(p2.begin(), p1[p1.size()-i]);
                    for(int i = 1; i <= k; i++){
                        p1.pop_back();
                        p2.pop_back();
                    }
                    break;
                }
                k += 2; // for wars
            }
        }
        // Game ends!
        if (p2.empty()) p1w++; // adding points for players after game, based on who won
        if (p1.empty()) p2w++;
        p1.clear(); // clearing vectors for next game
        p2.clear();

        //cout << "Amount of trials in game: " << counter << endl;

        if (mn > counter || mn == 0) mn = counter; // checking mimimal value
        if (mx < counter) mx = counter; // checking maximal value
        avg += counter; // caluclating avg

    }

    cout << "Player 1 won: " << p1w << " times" << endl;
    cout << "Player 2 won: " << p2w << " times" << endl;
    cout << "Average amount of trials in game: " << avg/aot << endl;
    cout << "Max of trials: " << mx << endl;
    cout << "Min of trials: " << mn << endl;
    return 0;
}
