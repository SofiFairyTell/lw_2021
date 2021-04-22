#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <algorithm>

using namespace std;

typedef vector<vector<int>> Matrix;

Matrix MultiplicationMatrices(const Matrix& a, const Matrix& b)
{
	//Умножение матриц
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

	}
}

Matrix TransposedMatrix(const Matrix& a)
{
	//Транспонирование матрицы
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
	//Сложение матриц
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
	//Проверочная матрицы
	Matrix res = vector<vector<int>>(3, vector<int>(4));
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 4; ++j) {
			res[i][j] = generator_matrix[i][j + 3];
		}
	}

	for (int i = 0; i < 4; ++i) {
		vector<int> new_row(4, 0);
		new_row[i] = 1;
		res.push_back(new_row);
	}
	//Транспонирование матрицы чтобы потом  написать проверочную
	return TransposedMatrix(res);
}

int main()
{
	Matrix input = {
			{0, 0, 1, 1}
			//0 1 0 1 0 0 0 0 1 1 1 1 0 0 0 0 1 1 1 1
	};

	cout << "Input:" << endl;
	PrintMatrix(input);
	cout << endl;

	//Порождающая матрица
	//Matrix generator_matrix = {
	//		{1, 0, 0, 0,    1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	//		{0, 1, 0, 0,    0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
	//		{0, 0, 1, 0,    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
	//		{0, 0, 0, 1,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}
	//};
	//Порождающая матрица д.б. построена по 4-м правилам...поэтому переделать до 10, 4
	//Matrix generator_matrix = {
	//	{1, 1, 1, 0,    0, 0, 0},
	//	{1, 0, 0, 0,    1, 0, 0},
	//	{0, 1, 0, 1,    0, 1, 0},
	//	{1, 1, 0, 1,    0, 0, 1}
	//};

	Matrix generator_matrix = {
	{1, 0, 0, 0,    1, 1, 0},
	{0, 1, 0, 0,    1, 0, 0},
	{0, 0, 1, 0,    0, 1, 0},
	{0, 0, 0, 1,    1, 1, 1}
	};
	//PrintMatrix(generator_matrix);
	//Формирование новой кодовой последовательности

	Matrix output = MultiplicationMatrices(input, generator_matrix);
	Matrix transposed_output = vector<vector<int>>(7, vector<int>(1));

	for (int i = 0; i < 7; ++i) {
		transposed_output[i][0] = output[0][i];
	}

	cout << "Output:" << endl;
	PrintMatrix(output); //вывод на экран
	cout << endl << endl;

	Matrix check_matrix = CheckMatrix(generator_matrix);
	int m = check_matrix.size();
	int n = check_matrix[0].size();
	PrintMatrix(check_matrix); //вывод на экран
	//Матрицы для ошибок
	//vector<Matrix> errors = {
	//	// one-time errors
	//	{{1, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
	//	{{0, 1, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
	//	{{0, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
	//	{{0, 0, 0, 1,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},

	//	// double errors
	//	{{1, 1, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
	//	{{0, 1, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
	//	{{0, 0, 1, 1,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
	//	{{1, 0, 0, 1,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
	//	{{1, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
	//	{{0, 1, 0, 1,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}
	//};
	vector<Matrix> errors = {
		// one-time errors
		{{1, 0, 0, 0,   0, 0, 0}},
		{{0, 1, 0, 0,   0, 0, 0}},
		{{0, 0, 1, 0,   0, 0, 0}},
		{{0, 0, 0, 1,   0, 0, 0}},

		// double errors
		{{1, 1, 0, 0,   0, 0, 0}},
		{{0, 1, 1, 0,   0, 0, 0}},
		{{0, 0, 1, 1,   0, 0, 0}},
		{{1, 0, 0, 1,   0, 0, 0}},
		{{1, 0, 1, 0,   0, 0, 0}},
		{{0, 1, 0, 1,   0, 0, 0}}
	};
	
	Matrix input_2 = {
			{1, 1, 0, 0,0,0,0}
			//0 1 0 1 0 0 0 0 1 1 1 1 0 0 0 0 1 1 1 1
	};
	
	cout << "Error                                   : Syndrome" << endl;
	for (const auto& error : errors) {

		auto spoiled_output = SumOfMatrices(output, error);
		auto transposed_spoiled_output = TransposedMatrix(spoiled_output);
		auto syndrome = MultiplicationMatrices(check_matrix, transposed_spoiled_output);

		PrintMatrix(error);
		cout << ": ";
		PrintMatrix(syndrome);
		cout << endl;
	}

	cout << endl;

	string source_alphabet = {
			'o', 's', 'g', 'z', 'p', 'v', 'u', 'w',
			'r', 't', 'k',

			// delete
			'l', 'm', 'n', 'f'

	};

	unordered_map<char, Matrix> input_for_letter{
			{'o', {{0, 0, 0, 1}}},
			{'s', {{0, 0, 1, 0}}},
			{'g', {{0, 0, 1, 1}}},
			{'z', {{0, 1, 0, 0}}},
			{'p', {{0, 1, 0, 1}}},
			{'v', {{0, 1, 1, 0}}},
			{'u', {{0, 1, 1, 1}}},
			{'w', {{1, 0, 0, 0}}},
			{'r', {{1, 0, 0, 1}}},
			{'t', {{1, 0, 1, 0}}},
			{'k', {{1, 0, 1, 1}}},
			{'l', {{1, 1, 0, 0}}},
			{'m', {{1, 1, 0, 1}}},
			{'n', {{1, 1, 1, 0}}},
			{'f', {{1, 1, 1, 1}}}
	};

	unordered_map<char, Matrix> output_for_letter;

	cout << "    letter :   code1 :                                   code2" << endl;
	for (auto letter : source_alphabet)
	{
		output_for_letter[letter] = MultiplicationMatrices(input_for_letter[letter], generator_matrix);
		cout << setw(10) << letter << " : ";
		PrintMatrix(input_for_letter[letter]);
		cout << ": ";
		PrintMatrix(output_for_letter[letter]);
		cout << endl;
	}

	for (auto l1 : source_alphabet) {
		for (auto l2 : source_alphabet) {
			auto delta = SumOfMatrices(output_for_letter[l1], output_for_letter[l2]);
			int dist = 0;
			for (int r = 0; r < delta.size(); ++r) {
				for (int c = 0; c < delta[0].size(); ++c) {
					//вычисление кодовых расстояний между разрешенными комбинациями
					dist += delta[r][c];
				}
			}
			cout << setw(5) << dist;
		}
		cout << endl;
	}

	return 0;
	system("pause");
}
