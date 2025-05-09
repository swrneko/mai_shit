#include <iostream>
using namespace std;

void print_matrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void input_matrix() {
    int size;
    cout << "Введите размерность матрицы M(A;A): ";
    cin >> size;

    // Выделение памяти
    int** matrix = new int*[size];
    for (int i = 0; i < size; ++i) {
        matrix[i] = new int[size];
    }

    cout << "Введите матрицу:" << endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cin >> matrix[i][j];
        }
    }

    cout << "Матрица:" << endl;
    print_matrix(matrix, size);

    // Очистка памяти
    for (int i = 0; i < size; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    input_matrix();
    return 0;
}

