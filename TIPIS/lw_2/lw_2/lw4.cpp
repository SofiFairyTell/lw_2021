#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>
#include <set>
#include <map>

#include <unordered_set>
#include <unordered_map>

#include <cmath>

using namespace std;

vector<vector<double>> p;

unordered_map<char, vector<int>> first_code;
unordered_map<char, vector<int>> second_code;

string source_alphabet;
string receiver_alphabet;

map<char, set<vector<int>>> sphere;

unordered_map<char, unordered_map<char, double>> channel_matrix;

unordered_map<char, double> probability_to_send;
unordered_map<char, double> probability_to_receive;

ofstream fout("C:\\Users\\Kurbatova\\source\\LW2021\\TIPIS\\lw_2\\information-theory-lab-4-channel-matrix.txt");
int size_of_cell = 15;
    // вывод в файл
	string source_alphabet_fout = { 'g', 'k', 'o', 'p', 'r','s','t','u', 'v', 'z','w' }; //алфавит источника
	string receiver_alph_fout = source_alphabet_fout + '?';

double ConditionalProbability(char received_letter, char sent_letter)
{
	//Условные вероятности
	double sum = 0;
	for (const auto& elem : sphere[received_letter]) {
		double part = 1;
		for (int i = 0; i < 7; ++i) {
			part *= p[elem[i]][(second_code[sent_letter])[i]];
		}
		sum += part;
	}
	return sum;
}

int Distance(const vector<int>& a, const vector<int>& b)
{
	int res = 0;
	for (int i = 0; i < 7; ++i) {
		if (a[i] != b[i]) {
			++res;
		}
	}
	return res;
}

void FillInChannelMatrix()
{
	for (char sent_letter : source_alphabet) {
		double sum = 0;
		for (char received_letter : receiver_alphabet) {
			if (received_letter == '?') {
				continue;
			}

			// edit
			channel_matrix[sent_letter][received_letter] = ConditionalProbability(received_letter, sent_letter);
			sum += channel_matrix[sent_letter][received_letter];
		}
		// probability of '????'
		channel_matrix[sent_letter]['?'] = 1 - sum;
	}
}

void PrintChannelMatrix()
{
	fout << setprecision(8) << fixed;

	fout << "КАНАЛЬНАЯ МАТРИЦА" << endl;
	fout << setw(2 * size_of_cell) << "";
	for (char received_letter : receiver_alph_fout)
	{ 
		fout << setw(size_of_cell) << received_letter; 
	} 
	fout << endl;
	int i = 0;
	for (char sent_letter : source_alphabet) {
		fout << setw(size_of_cell) << receiver_alph_fout[i] << setw(size_of_cell);
		for (char received_letter : receiver_alphabet) {
			fout << setw(size_of_cell) << channel_matrix[sent_letter][received_letter];
		}
		fout << endl; 
		i++;
	}
	fout << endl;
}

void FindAndPrintReceiversAlphabetDistribution()
{
	for (char received_letter : receiver_alphabet) {
		// formula of total probability
		double sum = 0; 
		for (char sent_letter : source_alphabet) {
			sum += channel_matrix[sent_letter][received_letter] * probability_to_send[sent_letter];
		}
		probability_to_receive[received_letter] = sum;
	}

	int j = 0;
	fout << "ВЕРОЯТНОСТЬ ПОЛУЧЕНИЯ СИМВОЛА:" << endl;
	for (char letter : receiver_alphabet) {
		fout << setw(size_of_cell) << receiver_alph_fout[j] << setw(size_of_cell) << probability_to_receive[letter] << endl;
		j++;
	}
	fout << endl;

}


int main()
{
	source_alphabet = {
			'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
			'i', 'j', 'k'
	};

	receiver_alphabet = source_alphabet + '?';

	probability_to_send = {
				{'a', 0.252340},
				{'b', 0.097010},
				{'c', 0.058950},
				{'d', 0.014970},
				{'e', 0.083590},
				{'f', 0.074860},
				{'g', 0.079230},
				{'h', 0.006240},
				{'i', 0.095450},
				{'j', 0.117900},
				{'k', 0.119460}
	};

	first_code = {
			{'a', {0, 0, 0, 1}},
			{'b', {0, 0, 1, 0}},
			{'c', {0, 0, 1, 1}},
			{'d', {0, 1, 0, 0}},
			{'e', {0, 1, 0, 1}},
			{'f', {0, 1, 1, 0}},
			{'g', {0, 1, 1, 1}},
			{'h', {1, 0, 0, 0}},
			{'i', {1, 0, 0, 1}},
			{'j', {1, 0, 1, 0}},
			{'k', {1, 0, 1, 1}},
	};

	/*second_code = {
			{'a', {1, 1, 0, 1, 0, 0, 1}},
			{'b', {0, 1, 0, 1, 0, 1, 0}},
			{'c', {1, 0, 0, 0, 0, 1, 1}},
			{'d', {1, 0, 0, 1, 1, 0, 0}},
			{'e', {0, 1, 0, 0, 1, 0, 1}},
			{'f', {1, 1, 0, 0, 1, 1, 0}},
			{'g', {0, 0, 0, 1, 1, 1, 1}},
			{'h', {1, 1, 1, 0, 0, 0, 0}},
			{'i', {0, 0, 1, 1, 0, 0, 1}},
			{'j', {1, 0, 1, 1, 0, 1, 0}},
			{'k', {0, 1, 1, 0, 0, 1, 1}},
	};*/
	second_code = {
		{'a', {0, 0, 0, 1, 1, 1, 1}},//o
		{'b', {0, 0, 1, 0, 0, 1, 0}},//s
		{'c', {0, 0, 1, 1, 1, 0, 1}},//g
		{'d', {0, 1, 0, 0, 1, 0, 0}},//z
		{'e', {0, 1, 0, 1, 0, 1, 1}},//p
		{'f', {0, 1, 1, 0, 1, 1, 0}},//v
		{'g', {0, 1, 1, 1, 0, 0, 1}},//u
		{'h', {1, 0, 0, 0, 1, 1, 0}},//w
		{'i', {1, 0, 0, 1, 0, 0, 1}},//r
		{'j', {1, 0, 1, 0, 1, 0, 0}},//t
		{'k', {1, 0, 1, 1, 0, 1, 1}},//k
	};

	for (int bit0 = 0; bit0 < 2; ++bit0) {
		for (int bit1 = 0; bit1 < 2; ++bit1) {
			for (int bit2 = 0; bit2 < 2; ++bit2) {
				for (int bit3 = 0; bit3 < 2; ++bit3) {
					for (int bit4 = 0; bit4 < 2; ++bit4) {
						for (int bit5 = 0; bit5 < 2; ++bit5) {
							for (int bit6 = 0; bit6 < 2; ++bit6) {
								{
									vector<int> cur_second_code = {
											bit0,
											bit1,
											bit2,
											bit3,
											bit4,
											bit5,
											bit6
									};

									for (auto letter : source_alphabet) {
										if (Distance(cur_second_code, second_code[letter]) <= 1) {
											sphere[letter].insert(cur_second_code);
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}


	// вероятности искажений 
	p = vector<vector<double>> (2, vector<double> (2)); 
	p[0][0] = 0.58; 
	p[1][0] = 0.42; 
	p[1][1] = 0.90; 
	p[0][1] = 0.10; 

	double transmission_time_of_one_bit = 0.0002;

	FillInChannelMatrix();
	PrintChannelMatrix();

	FindAndPrintReceiversAlphabetDistribution();

	cout << setprecision(8) << fixed;

	double source_entropy = 0;
	for (char letter : source_alphabet) {
		source_entropy -= probability_to_send[letter] * log2(probability_to_send[letter]);
	}
	fout << "Source entropy: " << endl
		<< "H(u) = " << source_entropy << endl;
	cout << "Source entropy: " << endl
		<< "H(u) = " << source_entropy << endl;

	double receiver_entropy = 0;
	for (char letter : receiver_alphabet) {
		receiver_entropy -= probability_to_receive[letter] * log2(probability_to_receive[letter]);
	}
	fout << "Receivers entropy: " << endl
		<< "H(v) = " << receiver_entropy << endl;
	cout << "Receivers entropy: " << endl
		<< "H(v) = " << receiver_entropy << endl;

	double leak_entropy = 0;
	for (char received_letter : receiver_alphabet) {
		double sum = 0;
		for (char sent_letter : source_alphabet) {
			double tmp =
				channel_matrix[sent_letter][received_letter] *
				probability_to_send[sent_letter] /
				probability_to_receive[received_letter];
			sum += tmp * log2(tmp);
		}
		leak_entropy -= sum * probability_to_receive[received_letter];
	}
	fout << "Leak entropy: " << endl
		<< "H(u|v) = " << leak_entropy << endl;
	cout << "Leak entropy: " << endl
		<< "H(u|v) = " << leak_entropy << endl;

	double noise_entropy = 0;
	for (char sent_letter : source_alphabet) {
		double sum = 0;
		for (char received_letter : receiver_alphabet) {
			sum += channel_matrix[sent_letter][received_letter] *
				log2(channel_matrix[sent_letter][received_letter]);
		}
		noise_entropy -= sum * probability_to_send[sent_letter];
	}
	fout << "Noise entropy: " << endl
		<< "H(v|u) = " << noise_entropy << endl;
	cout << "Noise entropy: " << endl
		<< "H(v|u) = " << noise_entropy << endl;

	double useful_information_by_source = source_entropy - leak_entropy;
	fout << "Useful information (by source): " << endl
		<< "I(u,v) = H(u) - H(u|v) = " << useful_information_by_source << endl;
	cout << "Useful information (by source): " << endl
		<< "I(u,v) = H(u) - H(u|v) = " << useful_information_by_source << endl;

	double useful_information_by_receiver = receiver_entropy - noise_entropy;
	fout << "Useful information (by receiver): " << endl
		<< "I(u,v) = H(v) - H(v|u) = " << useful_information_by_receiver << endl;
	cout << "Useful information (by receiver): " << endl
		<< "I(u,v) = H(v) - H(v|u) = " << useful_information_by_receiver << endl;

	// every letter contains four bits
	double information_transfer_rate = ((useful_information_by_source + useful_information_by_receiver) / 2) / (7 * transmission_time_of_one_bit);
	fout << "Information transfer rate:" << endl
		<< "J = " << information_transfer_rate << endl;
	cout << "Information transfer rate: " << endl
		<< "J = " << information_transfer_rate << endl;


	return 0;
}
