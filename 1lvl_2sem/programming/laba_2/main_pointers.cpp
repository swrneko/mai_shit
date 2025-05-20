#include <iostream>
#include <fstream>

using namespace std;

// Прототипы функций
int getMatrixSize(const char* filename);
void readMatrixFromFile(const char* filename, int* matrix, int size);
int processMatrix(int* matrix, int size, int* sums, int& minSum);

// Получение размера квадратной матрицы из файла (размер — первая строка файла)
int getMatrixSize(const char* filename) {
    ifstream fin(filename); // Открываем файл для чтения
    int size;
    fin >> size;            // Считываем размер матрицы
    fin.close();            // Закрываем файл
    return size;
}

// Чтение квадратной матрицы из файла и заполнение одномерного массива
void readMatrixFromFile(const char* filename, int* matrix, int size) {
    ifstream fin(filename); // Открываем файл для чтения
    int tmp;
    fin >> tmp;             // Пропускаем размер матрицы (он уже считан ранее)
    // Заполняем одномерный массив, используя арифметику указателей
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            fin >> *(matrix + i*size + j);
    fin.close();            // Закрываем файл
}

// Обработка матрицы: поиск сумм в строках под главной диагональю без отрицательных элементов
// sums — массив для сохранения найденных сумм, minSum — минимальная из сумм
// Функция возвращает количество найденных сумм
int processMatrix(int* matrix, int size, int* sums, int& minSum) {
    minSum = 1000000000; // Задаем заведомо большое значение для поиска минимума
    int count = 0;       // Количество подходящих строк
    // Проходим по всем строкам под главной диагональю (i > 0)
    for (int i = 1; i < size; ++i) {
        bool hasNegative = false; // Флаг наличия отрицательного элемента в строке
        // Проверяем только элементы под главной диагональю (j < i)
        for (int j = 0; j < i; ++j) {
            if (*(matrix + i*size + j) < 0) {
                hasNegative = true; // Если встретился отрицательный элемент — строка не подходит
                break;
            }
        }
        // Если в строке нет отрицательных элементов — считаем сумму элементов под диагональю
        if (!hasNegative) {
            int sum = 0;
            for (int j = 0; j < i; ++j)
                sum += *(matrix + i*size + j);
            sums[count++] = sum;      // Сохраняем сумму в массив
            if (sum < minSum)         // Обновляем минимум, если нужно
                minSum = sum;
        }
    }
    if (count == 0)
        minSum = 0; // Если подходящих строк не найдено — минимум 0
    return count;   // Возвращаем количество найденных сумм
}

int main() {
    // Определяем размерность матрицы, считав первую строку файла
    int size = getMatrixSize("input.txt");

    // Динамически выделяем память под матрицу (одномерный массив)
    int* matrix = new int[size * size];

    // Динамически выделяем память под массив для найденных сумм (максимум size-1)
    int* sums = new int[size];
    int minSum; // Для хранения минимальной суммы

    // Читаем матрицу из файла
    readMatrixFromFile("input.txt", matrix, size);

    // Обрабатываем матрицу, ищем суммы и минимум
    int count = processMatrix(matrix, size, sums, minSum);

    // Вывод всех найденных сумм по условию
    cout << "Суммы элементов по условию: ";
    if (count == 0) {
        cout << "Нет подходящих строк"; // Если не найдено ни одной подходящей строки
    } else {
        for (int i = 0; i < count; ++i) {
            cout << sums[i];
            if (i + 1 != count) cout << ", "; // Разделяем суммы запятыми
        }
    }
    cout << endl;

    // Вывод минимальной из найденных сумм
    cout << "Минимальная из этих сумм: " << minSum << endl;

    // Освобождаем память под массивы
    delete[] matrix;
    delete[] sums;

    return 0;
}
