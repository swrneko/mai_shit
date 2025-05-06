#include <iostream>
<<<<<<< HEAD
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

=======

using namespace std;


void print_matrix(int matrix_size, int** matrix) {
  for(int i=0; i < matrix_size; i++) {
      for(int j=0; j < matrix_size; j++) {
        cout << matrix[i][j] << " ";
      }
      cout << endl;
    }
}

void input_matrix() {
  int matrix_size = 0; 
  cout << "Введите размерность матрицы M(A;A): " << endl;
  cin >> matrix_size;

  int matrix[matrix_size][matrix_size];

  int** matrix = new int*[size];
    for (int i = 0; i < size; ++i) {
        matrix[i] = new int[size];
    }

  cout << "Введите матрицу: " << endl;
  for(int i=0; i < matrix_size; i++) {
    for(int j=0; j < matrix_size; j++) {
      cin >> matrix[i][j];
    }
  }
}

int main() {
  input_matrix();
  return 0;
}
>>>>>>> afb4634 (add laba 2 (programming))
