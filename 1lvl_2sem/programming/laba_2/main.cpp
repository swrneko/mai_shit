#include <iostream>
using namespace std;

const int ROWS = 3;
const int COLS = 3;

int main() {
    int matrix[ROWS][COLS];

    // Ввод матрицы
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cin >> matrix[i][j];
        }
    }

    // Вывод матрицы
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

