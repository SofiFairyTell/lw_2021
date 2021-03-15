#include <iostream> 
#include <vector> 
#include <unordered_map> 
#include <iomanip> 
#include <fstream> 
#include <cmath> 
#include <bitset>
using namespace std; 

vector<vector<double>> p; 
unordered_map<char, vector<int>> bin_representation_for_letter; 

string ToBitString(char letter) 
{ 
    string res = ""; 
    for (int bit : bin_representation_for_letter[letter]) 
    { 
        res += to_string(bit); 
    } 
    return res; 
} 
double ConditionalProbability(char received_letter, char sent_letter) 
{ 
    double res = 1; 
    for (int i = 0; i < 4; ++i) 
    { 
        res *= p[(bin_representation_for_letter[received_letter])[i]] 
        [(bin_representation_for_letter[sent_letter])[i]]; 
    } 
    return res; 
} 
int main() 
{ 
    cout << setprecision(8) << fixed; 
    char letter = 'a'; 
    bool flag = false; 
    for (int b3 = 0; b3 < 2; ++b3) 
    { 
        for (int b2 = 0; b2 < 2; ++b2) 
        { 
            for (int b1 = 0; b1 < 2; ++b1) { 
                for (int b0 = 0; b0 < 2; ++b0) 
                { 
                    // skip "0000" for lab #3 
                    if (!flag) 
                    { 
                        flag = true; 
                        continue; 
                    } 
                    if (letter > 'k') 
                    { 
                        break; 
                    } 
                    bin_representation_for_letter[letter] = { b3, b2, b1, b0 }; 
                    ++letter; 
                } 
            } 
        } 
    } 
    string source_alphabet = {    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',  'i', 'j', 'k' }; 
    string receiver_alphabet = source_alphabet + '?'; 
    // conditional probability 
        p = vector<vector<double>> (2, vector<double> (2)); 
        p[0][0] = 0.58; 
        p[1][0] = 0.42; 
        p[1][1] = 0.67; 
        p[0][1] = 0.33; 
    unordered_map<char, unordered_map<char, double>> channel_matrix; 
    for (char sent_letter : source_alphabet)
    { 
        double sum = 0; 
        for (char received_letter : receiver_alphabet) 
        { 
            if (received_letter == '?') 
            { 
                continue; 
            } 
            channel_matrix[sent_letter][received_letter] = ConditionalProbability(received_letter, sent_letter); 
            sum += channel_matrix[sent_letter][received_letter]; 
        } 
        // probability of '????' 
        channel_matrix[sent_letter]['?'] = 1 - sum; 
    } 
    
    ofstream fout("C:\\Users\\Kurbatova\\source\\LW2020\\lw_2021\\TIPIS\\lw_2\\information-theory-lab-2-channel-matrix.txt"); 
    fout << setprecision(8) << fixed; 
    int size_of_cell = 15; 
    fout << "CHANNEL MATRIX:" << endl; 
    fout << setw(2 * size_of_cell) << ""; 
    for (char received_letter : receiver_alphabet) 
    { 
        fout << setw(size_of_cell) << received_letter; 
    } 
   
    fout << endl; 
    fout << setw(2 * size_of_cell) << ""; 
    for (char received_letter : receiver_alphabet) 
    { 
        if (received_letter == '?') 
        { 
            continue; 
        } 
        fout << setw(size_of_cell) << ToBitString(received_letter); 
    } 
    fout << setw(size_of_cell) << "????" << endl; 
    for (char sent_letter : source_alphabet) 
    { 
        fout << setw(size_of_cell) << sent_letter 
        << setw(size_of_cell) << ToBitString(sent_letter); 
        for (char received_letter : receiver_alphabet) 
        { 
            fout << setw(size_of_cell) << channel_matrix[sent_letter][received_letter]; 
        } 
        fout << endl; 
    } 
    fout << endl; 
    unordered_map<char, double> probability_to_send = 
    { 
        {'a', 0.124279}, 
        {'b', 0.039437}, 
        {'c', 0.059650},
        {'d', 0.095822}, 
        {'e', 0.319089}, 
        {'f', 0.029545}, 
        {'g', 0.056979}, 
        {'h', 0.093613}, 
        {'i', 0.144755}, 
        {'j', 0.005672}, 
        {'k', 0.031160} 
    }; 
    unordered_map<char, double> probability_to_receive; 
    for (char received_letter : receiver_alphabet) 
    { 
        // formula of total probability 
        double sum = 0; 
        for (char sent_letter : source_alphabet) 
        { 
            sum += channel_matrix[sent_letter][received_letter] * probability_to_send[sent_letter]; 
        } 
        probability_to_receive[received_letter] = sum; 
    } 
    
    fout << "PROBABILITY TO RECEIVE LETTER:" << endl; 
    for (char letter : receiver_alphabet) 
    { 
        fout << setw(size_of_cell) << letter << setw(size_of_cell) << probability_to_receive[letter] << endl; 
    } 
    fout << endl; 
     double receiver_entropy = 0; 
    for (char letter : receiver_alphabet) 
    { 
        receiver_entropy -= probability_to_receive[letter] * log2(probability_to_receive[letter]); 
     } 

    fout << "RECEIVERS ENTROPY: " << receiver_entropy << endl; 
    cout << "RECEIVERS ENTROPY: " << receiver_entropy << endl; 
    double noise_entropy = 0; 
    for (char sent_letter : source_alphabet) 
    { 
        double sum = 0; 
        for (char received_letter : receiver_alphabet) 
        { 
            sum += channel_matrix[sent_letter][received_letter] * log2(channel_matrix[sent_letter][received_letter]); 
        } 
        noise_entropy -= sum * probability_to_send[sent_letter]; 
    } 
 
    cout << "NOISE ENTROPY: " << noise_entropy << endl; 
    fout << "NOISE ENTROPY: " << noise_entropy << endl; 
    double leak_entropy = 0; 
    for (char received_letter : receiver_alphabet) 
    { 
        double sum = 0; 
        for (char sent_letter : source_alphabet) 
        { 
            double tmp = 
            channel_matrix[sent_letter][received_letter] * probability_to_send[sent_letter] / probability_to_receive[received_letter]; 
            sum += tmp * log2(tmp); 
        } 
        
        leak_entropy -= sum * probability_to_receive[received_letter]; 
    } 

    cout << "LEAK ENTROPY: " << leak_entropy << endl; 
    fout << "LEAK ENTROPY: " << leak_entropy << endl; 
    
    return 0; 
}