#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <stack>
#include <string>
#include <iostream>
#include <iomanip>
#include <iterator>
#define loop(x, s, e) for(int x = s; x < e; x++)

using namespace std;

vector<string> split_string(string input_string, char split_char);
fstream output_file;



void print_custom(vector<string> data, int from, int to, string first, string second){
	loop(i, from, to){
		if (data[i] != first && data[i] != second)
			output_file << data[i] << " ";
		else
			output_file << "[" << data[i] << "] ";
	}
	output_file << endl << "======================================================================================" << endl;
}

void print_freq_lookup(vector <pair<string, int>> freq_lookup){
	output_file << "Frequency for all keywords in text: " << endl;
	loop(i, 0, freq_lookup.size()){
		output_file << freq_lookup[i].first << " = " << freq_lookup[i].second << endl;
	}
	output_file << "======================================================================================" << endl;
}

void print_calculated_matrix(vector<pair<pair<string, string>, float>> calculated_words, vector<pair<string, int>> freq_lookup, int n){
	vector<vector<float>> matrix(n, vector<float>(n));
	for (pair<pair<string, string>, float> w : calculated_words){
		int i, j;
		for (int k = 0; k < n; k++){
			if (freq_lookup[k].first == w.first.first){
				i = k;
			}
			if (freq_lookup[k].first == w.first.second){
				j = k;
			}
		}
		matrix[i][j] = w.second;
		for (int k = 0; k < n; k++){
			if (freq_lookup[k].first == w.first.second){
				i = k;
			}
			if (freq_lookup[k].first == w.first.first){
				j = k;
			}
		}
		matrix[i][j] = w.second;
	}
	output_file << "==================================== MATRIX =======================================" << endl;
	output_file << "          ";
	for (pair<string, int> elem : freq_lookup){
		output_file << setw(10) << elem.first;
	}
	output_file << endl;
	loop(i, 0, n){
		output_file << setw(10) << freq_lookup[i].first;
		loop(j, 0, n){
			output_file << setw(10) << fixed << setprecision(2) << matrix[i][j];
		}
		output_file << endl;
	}
	output_file << "======================================================================================" << endl;

}

void is_pair_exist(vector<string> data, vector<pair<string, int>> freq_lookup, int window_size){
	print_freq_lookup(freq_lookup);
	vector<pair<pair<string, string>, float>> calculated_words;
	int n = data.size();
	loop(i, 0, freq_lookup.size()){
		loop(j, i, freq_lookup.size()){
			if (i != j){
				string first = freq_lookup[i].first;
				string second = freq_lookup[j].first;
				int res = 0;
				for (int k = 0; k < n; k += window_size){
					int fir = 0;
					int sec = 0;
					loop(l, k, k + window_size){
						if (l >= n) break;
						if (data[l] == first){
							fir++;
						}
						if (data[l] == second){
							sec++;
						}
					}
					if (fir > 0 && sec > 0){
						output_file << "The words: [" << first << "] , [" << second << "] shown in paragraph " << min(fir, sec) << " time(s)." << endl;
						print_custom(data, k, k + window_size, first, second);
						res += min(fir, sec);

					}
				}
				float calculated_value = ((float)(2 * res) / ((float)((freq_lookup[i].second) + (freq_lookup[j].second))));
				calculated_words.push_back(make_pair(make_pair(first, second), calculated_value));
			}
		}
	}
	print_calculated_matrix(calculated_words, freq_lookup, freq_lookup.size());

}

int main() {

	ifstream input_file1, input_file2;
	
	string data, words;
	input_file1.open("input.txt");
	input_file2.open("keywords.txt");
	output_file.open("output.txt", std::ofstream::out | std::ofstream::trunc);
	while (!input_file1.eof())
	{
		getline(input_file1, data);
	}
	while (!input_file2.eof())
	{
		getline(input_file2, words);
	}
	input_file1.close();
	input_file2.close();
	
	vector<string> text = split_string(data,' ');
	int n = text.size();
	int window_size = 50;
	int random_times = 40;
	srand((unsigned)time(0));

	vector<string> lookup_words = split_string(words,',');
	vector<pair<string, int>> freq_lookup(lookup_words.size());



	for (int i = 0; i < random_times; i++){
		int random_index = max(0, (rand() % n));
		int random_word = max(0, (int)(rand() % lookup_words.size()));
		text.insert(text.begin() + random_index, lookup_words[random_word]);
	}
	for (int i = 0; i < lookup_words.size(); i++)
	{
		freq_lookup[i].first = lookup_words[i];
		freq_lookup[i].second = count(text.begin(), text.end(), lookup_words[i]);
	}

	output_file << "======================= RESULT ==============================" << endl;
	is_pair_exist(text, freq_lookup, window_size);

	output_file.close();

	return 0;
}

vector<string> split_string(string input_string, char split_char) {
	string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char &x, const char &y) {
		return x == y && x == ' ';
	});

	input_string.erase(new_end, input_string.end());

	while (input_string[input_string.length() - 1] == ' ') {
		input_string.pop_back();
	}

	vector<string> splits;
	char delimiter = split_char;

	size_t i = 0;
	size_t pos = input_string.find(delimiter);

	while (pos != string::npos) {
		splits.push_back(input_string.substr(i, pos - i));

		i = pos + 1;
		pos = input_string.find(delimiter, i);
	}

	splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

	return splits;
}