#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <algorithm>

using namespace std;

typedef vector<vector<int>> Matrix;

Matrix MultiplicationMatrices(const Matrix& a, const Matrix& b)
{
	int m = a.size();
	int n = a[0].size();
	int p = b[0].size();

	if (b.size() != n) {
		throw exception();
	}

	Matrix c = vector<vector<int>>(m, vector<int>(p));
	int sum = 0;

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < p; ++j) {
			sum = 0;
			for (int idx = 0; idx < n; ++idx) {
				sum = (sum + a[i][idx] * b[idx][j]) % 2;
			}
			c[i][j] = sum;
		}
	}

	return c;
}

void PrintMatrix(const Matrix& a) {
	int m = a.size();
	int n = a[0].size();
	for (int r = 0; r < m; ++r) {
		for (int c = 0; c < n; ++c) {
			cout << a[r][c] << " ";
		}
		//cout << endl;
	}
}

Matrix TransposedMatrix(const Matrix& a)
{
	int m = a.size();
	int n = a[0].size();

	Matrix b = vector<vector<int>>(n, vector<int>(m));
	for (int r = 0; r < m; ++r) {
		for (int c = 0; c < n; ++c) {
			b[c][r] = a[r][c];
		}
	}

	return b;
}

Matrix SumOfMatrices(const Matrix& a, const Matrix& b)
{
	if (a.size() != b.size() || a[0].size() != b[0].size()) {
		throw exception();
	}

	int m = a.size();
	int n = a[0].size();

	Matrix res = vector<vector<int>>(m, vector<int>(n));
	for (int r = 0; r < m; ++r) {
		for (int c = 0; c < n; ++c) {
			res[r][c] = (a[r][c] + b[r][c]) % 2;
		}
	}

	return res;

}

Matrix CheckMatrix(const Matrix& generator_matrix)
{
	Matrix res = vector<vector<int>>(4, vector<int>(16));
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 16; ++j) {
			res[i][j] = generator_matrix[i][j + 4];
		}
	}

	for (int i = 0; i < 16; ++i) {
		vector<int> new_row(16, 0);
		new_row[i] = 1;
		res.push_back(new_row);
	}

	return TransposedMatrix(res);
}

int main()
{
	Matrix input = {
			{0, 0, 1, 1}
	};

	cout << "Input:" << endl;
	PrintMatrix(input);
	cout << endl;

	Matrix generator_matrix = {
			{1, 0, 0, 0,    1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 1, 0, 0,    0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 1, 0,    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
			{0, 0, 0, 1,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}
	};
	//PrintMatrix(generator_matrix);

	Matrix output = MultiplicationMatrices(input, generator_matrix);
	Matrix transposed_output = vector<vector<int>>(10, vector<int>(1));
	for (int i = 0; i < 10; ++i) {
		transposed_output[i][0] = output[0][i];
	}

	cout << "Output:" << endl;
	PrintMatrix(output);
	cout << endl << endl;

	Matrix check_matrix = CheckMatrix(generator_matrix);
	int m = check_matrix.size();
	int n = check_matrix[0].size();
	/*
	for (int r = 0; r < m; ++r) {
		for (int c = 0; c < n; ++c) {
			cout << check_matrix[r][c] << " ";
		}
		cout << endl;
	}
	*/

	vector<Matrix> errors = {
		// one-time errors
		{{1, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
		{{0, 1, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
		{{0, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
		{{0, 0, 0, 1,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},

		// double errors
		{{1, 1, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
		{{0, 1, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
		{{0, 0, 1, 1,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
		{{1, 0, 0, 1,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
		{{1, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
		{{0, 1, 0, 1,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}
	};

	cout << "Error                                   : Syndrome" << endl;
	for (const auto& error : errors) {

		auto spoiled_output = SumOfMatrices(output, error);
		auto transposed_spoiled_output = TransposedMatrix(spoiled_output);
		auto syndrome = MultiplicationMatrices(check_matrix, trans - posed_spoiled_output);

		PrintMatrix(error);
		cout << ": ";
		PrintMatrix(syndrome);
		cout << endl;
	}
	cout << endl;

	string source_alphabet = {
			'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
			'i', 'j', 'k',

			// delete
			'l', 'm', 'n', 'o'

	};

	unordered_map<char, Matrix> input_for_letter{
			{'a', {{0, 0, 0, 1}}},
			{'b', {{0, 0, 1, 0}}},
			{'c', {{0, 0, 1, 1}}},
			{'d', {{0, 1, 0, 0}}},
			{'e', {{0, 1, 0, 1}}},
			{'f', {{0, 1, 1, 0}}},
			{'g', {{0, 1, 1, 1}}},
			{'h', {{1, 0, 0, 0}}},
			{'i', {{1, 0, 0, 1}}},
			{'j', {{1, 0, 1, 0}}},
			{'k', {{1, 0, 1, 1}}},
			{'l', {{1, 1, 0, 0}}},
			{'m', {{1, 1, 0, 1}}},
			{'n', {{1, 1, 1, 0}}},
			{'o', {{1, 1, 1, 1}}}
	};

	unordered_map<char, Matrix> output_for_letter;

	cout << "    letter :   code1 :                                   code2" << endl;
	for (auto letter : source_alphabet)
	{
		output_for_letter[letter] = MultiplicationMatri - ces(input_for_letter[letter], generator_matrix);
		cout << setw(10) << letter << " : ";
		PrintMatrix(input_for_letter[letter]);
		cout << ": ";
		PrintMatrix(output_for_letter[letter]);
		cout << endl;
	}

	for (auto l1 : source_alphabet) {
		for (auto l2 : source_alphabet) {
			auto delta = SumOfMatrices(output_for_letter[l1], out - put_for_letter[l2]);
			int dist = 0;
			for (int r = 0; r < delta.size(); ++r) {
				for (int c = 0; c < delta[0].size(); ++c) {
					dist += delta[r][c];
				}
			}
			cout << setw(5) << dist;
		}
		cout << endl;
	}

	return 0;
}
