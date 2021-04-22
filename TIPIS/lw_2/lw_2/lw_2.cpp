//#include <iostream> 
//#include <vector> 
//#include <unordered_map> 
//#include <iomanip> 
//#include <fstream> 
//#include <cmath> 
//#include <bitset>
//using namespace std; 
//
//vector<vector<double>> p; 
//unordered_map<char, vector<int>> bin_represent_letter; 
//
//string ToBitString(char letter) 
//{ 
//    string res = ""; 
//    for (int bit : bin_represent_letter[letter]) 
//    { 
//        res += to_string(bit); // изменение в строковое представление
//    } 
//    return res; 
//} 
//// Вычисление условной вероятности
//double ConditionalProbability(char received_letter, char sent_letter) 
//{ 
//    // P(A|B) = P(A)
//    double res = 1; 
//    for (int i = 0; i < 4; ++i) 
//    { 
//        res *= p[(bin_represent_letter[received_letter])[i]][(bin_represent_letter[sent_letter])[i]]; 
//    } 
//    return res; 
//} 
//int main() 
//{ 
//	setlocale(LC_ALL, "");
//    cout << setprecision(8) << fixed; //устновить точност
//    char letter = 'a'; 
//    bool flag = false; 
//    for (int b3 = 0; b3 < 2; ++b3) 
//    { 
//        for (int b2 = 0; b2 < 2; ++b2) 
//        { 
//            for (int b1 = 0; b1 < 2; ++b1) { 
//                for (int b0 = 0; b0 < 2; ++b0) 
//                { 
//                    // skip "0000" for lab #3 
//                    if (!flag) 
//                    { 
//                        flag = true; 
//                        continue; 
//                    } 
//                    if (letter > 'k') 
//                    { 
//                        break; 
//                    } 
//                    bin_represent_letter[letter] = { b3, b2, b1, b0 }; 
//                    ++letter; 
//                } 
//            } 
//        } 
//    } 
//	
//
//	//string source_alphabet = { 'o', 's', 'g', 'z', 'p', 'v', 'u','w', 'r', 't', 'k' };
//
//	string source_alphabet = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k' }; //алфавит источника
//    string receiver_alphabet = source_alphabet + '?'; //алфавит передачи
//	
//
//// вероятности искажений 
//        p = vector<vector<double>> (2, vector<double> (2)); 
//        p[0][0] = 0.58; 
//        p[1][0] = 0.42; 
//        p[1][1] = 0.90; 
//        p[0][1] = 0.10; 
//
//    unordered_map<char, unordered_map<char, double>> channel_matrix; 
//    for (char sent_letter : source_alphabet)
//    { 
//        double sum = 0; 
//        for (char received_letter : receiver_alphabet) 
//        { 
//            if (received_letter == '?') 
//            { 
//                continue; 
//            } 
//            channel_matrix[sent_letter][received_letter] = ConditionalProbability(received_letter, sent_letter); 
//            sum += channel_matrix[sent_letter][received_letter]; 
//        } 
//        // вероятность of '????' 
//        channel_matrix[sent_letter]['?'] = 1 - sum; 
//    } 
//    
//    ofstream fout("C:\\Users\\Kurbatova\\source\\LW2020\\lw_2021\\TIPIS\\lw_2\\information-theory-lab-2-channel-matrix-my.txt"); 
//    fout << setprecision(8) << fixed; 
//    int size_of_cell = 15; 
//    // вывод в файл
//	string source_alphabet_fout = { 'g', 'k', 'o', 'p', 'r','s','t','u', 'v', 'z','w' }; //алфавит источника
//	string receiver_alph_fout = source_alphabet_fout + '?';
//
//    fout << "КАНАЛЬНАЯ МАТРИЦА:" << endl; 
//    fout << setw(2 * size_of_cell) << ""; 
//
//    for (char received_letter : receiver_alph_fout)
//    { 
//        fout << setw(size_of_cell) << received_letter; 
//    } 
//   
//    fout << endl; 
//    fout << setw(2 * size_of_cell) << ""; 
//    for (char received_letter : receiver_alphabet) 
//    { 
//        if (received_letter == '?') 
//        { 
//            continue; 
//        } 
//        fout << setw(size_of_cell) << ToBitString(received_letter); 
//    } 
//    fout << setw(size_of_cell) << "????" << endl; 
//	int i = 0;
//    for (char sent_letter : source_alphabet) 
//    { 
//		
///*		fout << setw(size_of_cell) << sent_letter
//			<< setw(size_of_cell) << ToBitString(sent_letter);	*/	
//		fout << setw(size_of_cell) << receiver_alph_fout[i]
//			<< setw(size_of_cell) << ToBitString(sent_letter);
//
//        for (char received_letter : receiver_alphabet) 
//        { 
//            fout << setw(size_of_cell) << channel_matrix[sent_letter][received_letter]; 
//        } 
//        fout << endl; 
//		i++;
//    } 
//    fout << endl; 
//    //unordered_map<char, double> probability_to_send = 
//    //{ 
//    //    {'a', 0.252340}, 
//    //    {'s', 0.097010}, 
//    //    {'g', 0.058950},
//    //    {'z', 0.014970}, 
//    //    {'p', 0.083590}, 
//    //    {'v', 0.074860}, 
//    //    {'u', 0.079230}, 
//    //    {'w', 0.006240}, 
//    //    {'r', 0.095450}, 
//    //    {'t', 0.117900}, 
//    //    {'k', 0.119460} 
//    //}; 
//	unordered_map<char, double> probability_to_send =
//	{
//		{'a', 0.252340},
//		{'b', 0.097010},
//		{'c', 0.058950},
//		{'d', 0.014970},
//		{'e', 0.083590},
//		{'f', 0.074860},
//		{'g', 0.079230},
//		{'h', 0.006240},
//		{'i', 0.095450},
//		{'j', 0.117900},
//		{'k', 0.119460}
//	};
//    unordered_map<char, double> probability_to_receive; 
//    for (char received_letter : receiver_alphabet) 
//    { 
//        // формула общей вероятности
//        double sum = 0; 
//        for (char sent_letter : source_alphabet) 
//        { 
//            sum += channel_matrix[sent_letter][received_letter] * probability_to_send[sent_letter]; 
//        } 
//        probability_to_receive[received_letter] = sum; 
//    } 
//	int j = 0;
//    fout << "ВЕРОЯТНОСТЬ ПОЛУЧЕНИЯ СИМВОЛА:" << endl; 
//    for (char letter : receiver_alphabet)
//    { 
//
//	     /*fout << setw(size_of_cell) << letter << setw(size_of_cell) << probability_to_receive[letter] << endl; */
//		 fout << setw(size_of_cell) << receiver_alph_fout[j] << setw(size_of_cell) << probability_to_receive[letter] << endl;
//		 j++;
//
//    } 
//    fout << endl; 
//    
//	double receiver_entropy = 0; 
//    for (char letter : receiver_alphabet) 
//    { 
//        receiver_entropy -= probability_to_receive[letter] * log2(probability_to_receive[letter]); 
//     } 
//
//    fout << "ЭНТРОПИЯ ПРИЕМНИКА: " << receiver_entropy << endl; 
//    cout << "RECEIVER ENTROPY: " << receiver_entropy << endl; 
//
//	double noise_entropy = 0; 
//    for (char sent_letter : source_alphabet) 
//    { 
//        double sum = 0; 
//        for (char received_letter : receiver_alphabet) 
//        { 
//            sum += channel_matrix[sent_letter][received_letter] * log2(channel_matrix[sent_letter][received_letter]); 
//        } 
//        noise_entropy -= sum * probability_to_send[sent_letter]; 
//    } 
// 
//    cout << "NOISE ENTROPY: " << noise_entropy << endl; 
//    fout << "ЭНТРОПИЯ ШУМА: " << noise_entropy << endl; 
//    double leak_entropy = 0; 
//
//    for (char received_letter : receiver_alphabet) 
//    { 
//        double sum = 0; 
//        for (char sent_letter : source_alphabet) 
//        { 
//            double tmp = 
//            channel_matrix[sent_letter][received_letter] * probability_to_send[sent_letter] / probability_to_receive[received_letter]; 
//            sum += tmp * log2(tmp); 
//        } 
//        
//        leak_entropy -= sum * probability_to_receive[received_letter]; 
//    } 
//
//    cout << "LEAK ENTROPY: " << leak_entropy << endl; 
//    fout << "ЭНТРОПИЯ УТЕЧКИ: " << leak_entropy << endl; 
//    
//    return 0; 
//}