#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void save_data(unsigned long long int all_battles, int aot, int all_wars, int mx, int mn, int wmx, int wmn);
unsigned long long int* load_data();