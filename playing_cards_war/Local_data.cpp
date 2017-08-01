#include "Local_data.h"
#include <math.h>

void save_data(unsigned long long int aot, int avg_battles, int avg_wars, int mx, int mn, int wmx, int wmn) {
	// saves data to txt file, combining new data with already saved data.
	unsigned long long int *data = new unsigned long long int[7];
	data = load_data();
	float percent = float(aot) / (aot + data[0]);
	ofstream stats_file;
	stats_file.open("war_statistics.txt");
	stats_file << "Statistics_for_all_games_played: \n";
	stats_file << "\nAmount_of_games_played: " << aot + data[0];
	stats_file << "\nAverage_amount_of_battles: " << round(avg_battles*percent + data[1] * (1 - percent));
	stats_file << "\nAverage_amount_of_wars: " << round(avg_wars*percent + data[2] * (1 - percent));
	
	if (data[3] > mx)
		stats_file << "\nMax_battles: " << data[3];
	else
		stats_file << "\nMax_battles: " << mx;
	if (data[4] < mn && data[0] != 0)
		stats_file << "\nMin_battles: " << data[4];
	else
		stats_file << "\nMin_battles: " << mn;
	if (data[5] > wmx)
		stats_file << "\nMax_wars: " << data[5];
	else
		stats_file << "\nMax_wars: " << wmx;
	if(data[6] < wmn && data[0] != 0)
		stats_file << "\nMin_wars: " << data[6];
	else
		stats_file << "\nMin_wars: " << wmn;
	stats_file.close();
	delete data;
}

unsigned long long int* load_data() {
	// loads data from file to an array and returns it
	fstream stats;
	stats.open("war_statistics.txt", ios::in);
	unsigned long long int *data = new unsigned long long int[7];
	if (stats.good() == false) { // if file could not be opened
		for (int i = 0; i < 7; i++)
			data[i] = 0;
		return data;
	}
	string temp;
	stats >> temp;
	for (int i = 0; i < 7; i++) { // filling array with data from file
		stats >> temp;
		stats >> data[i];
	}
	stats.close();
	return data;
}