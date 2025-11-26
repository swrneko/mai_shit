#include <iostream>
#include <cstdlib>  // Для функций генерации случайных чисел (rand, srand)
#include <ctime>    // Для инициализации таймера (time)
#include <iomanip>  // Для красивого форматирования таблицы (setw)
#include <chrono>   // Для точного замера времени выполнения

// Используем стандартное пространство имен
using namespace std;
using namespace std::chrono; // Для удобства работы со временем

// --- ГЛОБАЛЬНЫЕ НАСТРОЙКИ ---
// Флаг, который включает вывод массива на каждом шаге.
// Включаем его только для N=15, чтобы не засорять консоль на больших массивах.
bool SHOW_STEPS = false;

// --- ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ---

// Функция для вывода массива в консоль
// Принимает указатель на массив и его размер
void printArray(int* arr, int n) {
    // Если вывод отключен, сразу выходим
    if (!SHOW_STEPS) return;
    
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Функция для обмена двух элементов местами (аналог std::swap)
// Увеличивает счетчик пересылок (moves) на 3, так как обмен — это 3 операции присваивания:
// 1. temp = a
// 2. a = b
// 3. b = temp
void mySwap(int& a, int& b, long long& moves) {
    int temp = a;
    a = b;
    b = temp;
    moves += 3;
}

// Функция для создания копии массива
// Нужна, чтобы каждый алгоритм работал с одинаковыми исходными данными, но не портил их для других
void copyArray(const int* src, int* dest, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// =========================================================
// АЛГОРИТМ 1: СОРТИРОВКА СЛИЯНИЕМ (MERGE SORT)
// =========================================================

// Вспомогательная функция, которая сливает два отсортированных подмассива в один
void merge(int* arr, int left, int mid, int right, long long& cmp, long long& moves) {
    // Вычисляем размеры временных подмассивов
    int n1 = mid - left + 1; // Размер левой части
    int n2 = right - mid;    // Размер правой части

    // Выделяем динамическую память под временные массивы
    // (так как vector использовать нельзя)
    int* L = new int[n1];
    int* R = new int[n2];

    // Копируем данные во временные массивы
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
        moves++; // Учитываем пересылку данных
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
        moves++; // Учитываем пересылку данных
    }

    // Индексы для обхода массивов:
    int i = 0;    // Индекс для левого подмассива (L)
    int j = 0;    // Индекс для правого подмассива (R)
    int k = left; // Индекс для основного массива (arr)

    // Основной цикл слияния: сравниваем элементы и вставляем меньший в основной массив
    while (i < n1 && j < n2) {
        cmp++; // Считаем сравнение L[i] <= R[j]
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            moves++; // Пересылка из L в arr
            i++;
        } else {
            arr[k] = R[j];
            moves++; // Пересылка из R в arr
            j++;
        }
        k++;
    }

    // Если в левом массиве остались элементы, дописываем их
    while (i < n1) {
        arr[k] = L[i];
        moves++;
        i++;
        k++;
    }

    // Если в правом массиве остались элементы, дописываем их
    while (j < n2) {
        arr[k] = R[j];
        moves++;
        j++;
        k++;
    }

    // ОЧЕНЬ ВАЖНО: Освобождаем память временных массивов, чтобы не было утечек
    delete[] L;
    delete[] R;
}

// Рекурсивная функция сортировки слиянием
void mergeSortRecursive(int* arr, int left, int right, long long& cmp, long long& moves) {
    if (left >= right) {
        return; // Базовый случай: массив из 1 элемента уже отсортирован
    }
    
    // Находим середину массива
    int mid = left + (right - left) / 2;
    
    // Рекурсивно сортируем левую половину
    mergeSortRecursive(arr, left, mid, cmp, moves);
    
    // Рекурсивно сортируем правую половину
    mergeSortRecursive(arr, mid + 1, right, cmp, moves);
    
    // Сливаем две отсортированные половины
    merge(arr, left, mid, right, cmp, moves);
}

// Обертка для удобного вызова из main (скрывает параметры left и right)
void runMergeSort(int* arr, int n, long long& cmp, long long& moves) {
    mergeSortRecursive(arr, 0, n - 1, cmp, moves);
    
    if (SHOW_STEPS) {
        cout << "Merge Sort result: ";
        printArray(arr, n);
    }
}

// =========================================================
// АЛГОРИТМ 2: БЫСТРАЯ СОРТИРОВКА (QUICK SORT)
// =========================================================

// --- ВАРИАНТ А: Опорный элемент - ПОСЛЕДНИЙ (Схема Ломуто) ---
// Этот вариант работает плохо на уже отсортированных массивах (O(N^2))

int partitionLast(int* arr, int low, int high, long long& cmp, long long& moves) {
    int pivot = arr[high]; // Опорный элемент - последний
    moves++; // Условное чтение pivot
    
    int i = (low - 1); // Индекс меньшего элемента

    for (int j = low; j <= high - 1; j++) {
        cmp++; // Сравнение текущего элемента с опорным
        if (arr[j] < pivot) {
            i++;
            // Если элемент меньше опорного, меняем его с элементом под индексом i
            mySwap(arr[i], arr[j], moves);
        }
    }
    // Ставим опорный элемент на его правильное место (после всех меньших)
    mySwap(arr[i + 1], arr[high], moves);
    return (i + 1); // Возвращаем индекс опорного элемента
}

void quickSortLastRecursive(int* arr, int low, int high, long long& cmp, long long& moves) {
    if (low < high) {
        // Получаем индекс разделения
        int pi = partitionLast(arr, low, high, cmp, moves);

        if (SHOW_STEPS) {
             cout << "Pivot Index " << pi << ": ";
             printArray(arr, high + 1); // Печатаем массив (упрощенно)
        }

        // Рекурсивно сортируем элементы до и после разделения
        quickSortLastRecursive(arr, low, pi - 1, cmp, moves);
        quickSortLastRecursive(arr, pi + 1, high, cmp, moves);
    }
}

void runQuickSortLast(int* arr, int n, long long& cmp, long long& moves) {
    quickSortLastRecursive(arr, 0, n - 1, cmp, moves);
}


// --- ВАРИАНТ Б: Схема ХОАРА (Опорный элемент - СЕРЕДИНА) ---
// Этот вариант намного эффективнее на уже отсортированных данных.

int partitionHoare(int* arr, int low, int high, long long& cmp, long long& moves) {
    int pivot = arr[(low + high) / 2]; // Опорный - центральный элемент
    moves++; // Чтение pivot
    
    int i = low - 1;
    int j = high + 1;

    while (true) {
        // Ищем элемент слева, который больше или равен опорному
        do {
            i++;
            cmp++; 
        } while (arr[i] < pivot);

        // Ищем элемент справа, который меньше или равен опорному
        do {
            j--;
            cmp++;
        } while (arr[j] > pivot);

        // Если указатели сошлись, разделение закончено
        if (i >= j)
            return j;

        // Иначе меняем местами элементы, стоящие не на своих сторонах
        mySwap(arr[i], arr[j], moves);
    }
}

void quickSortHoareRecursive(int* arr, int low, int high, long long& cmp, long long& moves) {
    if (low < high) {
        int pi = partitionHoare(arr, low, high, cmp, moves);
        
        if (SHOW_STEPS) {
             cout << "Hoare Partition: ";
             // Вывод упрощен для демонстрации
             printArray(arr, high + 1); 
        }

        // В схеме Хоара рекурсивные вызовы немного отличаются границами (pi и pi+1)
        quickSortHoareRecursive(arr, low, pi, cmp, moves);
        quickSortHoareRecursive(arr, pi + 1, high, cmp, moves);
    }
}

void runQuickSortHoare(int* arr, int n, long long& cmp, long long& moves) {
    quickSortHoareRecursive(arr, 0, n - 1, cmp, moves);
    if (SHOW_STEPS) {
        cout << "Quick Sort (Hoare) result: ";
        printArray(arr, n);
    }
}

// =========================================================
// ЛОГИКА ТЕСТИРОВАНИЯ
// =========================================================

// Тип сортировки для генерации данных
enum SortType { RANDOM, SORTED_ASC, SORTED_DESC };

// Определение типа функции для удобства передачи в testRunner
typedef void (*SortFunction)(int*, int, long long&, long long&);

// Функция, которая запускает один тест и выводит строку таблицы
void runSingleTest(const char* algoName, SortFunction sortFunc, int* originalData, int n, const char* dataTypeDesc) {
    // 1. Создаем копию массива, чтобы сортировка не испортила данные для других алгоритмов
    int* arr = new int[n];
    copyArray(originalData, arr, n);

    long long cmp = 0;   // Сброс счетчика сравнений
    long long moves = 0; // Сброс счетчика пересылок

    if (SHOW_STEPS) {
        cout << "\n--- Запуск: " << algoName << " ---\n";
        cout << "До сортировки: ";
        printArray(arr, n);
    }

    // 2. Замеряем время
    auto start = high_resolution_clock::now();
    sortFunc(arr, n, cmp, moves);
    auto end = high_resolution_clock::now();

    // Переводим время в наносекунды
    long long time_ns = duration_cast<nanoseconds>(end - start).count();

    // 3. Вывод результатов
    if (SHOW_STEPS) {
        // Подробный вывод для N=15
        cout << "После сортировки: ";
        printArray(arr, n);
        cout << "Время: " << time_ns << " нс, Сравнений: " << cmp << ", Пересылок: " << moves << endl;
    } else {
        // Табличный вывод для больших N
        cout << left << setw(8) << n << " | " 
             << setw(13) << dataTypeDesc << " | "
             << setw(20) << algoName << " | " 
             << setw(12) << time_ns << " | " 
             << setw(15) << cmp << " | " 
             << setw(15) << moves << endl;
    }

    // 4. Очистка памяти копии
    delete[] arr;
}

// Функция сценария, которая создает данные и прогоняет по ним все выбранные алгоритмы
void runTestScenario(int n, SortType type) {
    // Выделяем память под исходный массив
    int* original = new int[n];
    
    // Генерация данных в зависимости от типа
    if (type == RANDOM) {
        for (int i = 0; i < n; i++) original[i] = rand() % 10000;
    } else if (type == SORTED_ASC) {
        // Возрастающая последовательность (0, 1, 2...)
        for (int i = 0; i < n; i++) original[i] = i;
    } else { 
        // Убывающая последовательность (n, n-1, ...)
        for (int i = 0; i < n; i++) original[i] = n - i;
    }

    // Строковое описание типа данных
    const char* typeStr = (type == RANDOM) ? "Random" : (type == SORTED_ASC ? "Sorted Asc" : "Sorted Desc");

    // === ВАРИАНТ 4: СЛИЯНИЕМ + БЫСТРАЯ ===
    
    // 1. Сортировка слиянием (Merge Sort)
    runSingleTest("Merge Sort", runMergeSort, original, n, typeStr);

    // 2. Быстрая сортировка (Quick Sort) - Опорный = Последний
    // ВНИМАНИЕ: На больших отсортированных массивах (>40000) это может вызвать переполнение стека!
    if (n <= 40000 || type == RANDOM) {
        runSingleTest("Quick (Last Pivot)", runQuickSortLast, original, n, typeStr);
    } else {
        // Пропускаем опасный тест для больших N и выводим заглушку
        if (!SHOW_STEPS)
            cout << left << setw(8) << n << " | " << setw(13) << typeStr << " | "
                 << setw(20) << "Quick (Last Pivot)" << " | " 
                 << "SKIPPED (Stack Overflow Risk)" << endl;
    }

    // 3. Быстрая сортировка (Quick Sort) - Схема Хоара
    runSingleTest("Quick (Hoare)", runQuickSortHoare, original, n, typeStr);

    // Освобождаем память исходного массива
    delete[] original; 
}

// =========================================================
// ГЛАВНАЯ ФУНКЦИЯ (MAIN)
// =========================================================
int main() {
    setlocale(LC_ALL, ""); // Включаем русский язык
    srand(time(0));        // Инициализация генератора случайных чисел

    // --- ЧАСТЬ 1: Демонстрация работы на малом массиве (N=15) ---
    cout << "=========================================================\n";
    cout << " ЧАСТЬ 1: Промежуточные результаты (N = 15)\n";
    cout << "=========================================================\n";
    SHOW_STEPS = true; // Включаем режим подробного вывода
    runTestScenario(15, RANDOM);
    SHOW_STEPS = false; // Выключаем для второй части
    cout << "\n\n";

    // --- ЧАСТЬ 2: Анализ производительности на больших массивах ---
    cout << "=========================================================\n";
    cout << " ЧАСТЬ 2: Сравнительный анализ (N = 500..100000)\n";
    cout << "=========================================================\n";
    
    // Заголовок таблицы
    cout << string(95, '-') << endl;
    cout << left << setw(8) << "N" << " | " 
                 << setw(13) << "Тип данных" << " | "
                 << setw(20) << "Алгоритм" << " | " 
                 << setw(12) << "Время (нс)" << " | " 
                 << setw(15) << "Сравнения" << " | " 
                 << setw(15) << "Пересылки" << endl;
    cout << string(95, '-') << endl;

    // Массив размеров, которые нужно протестировать
    int sizes[] = {500, 1000, 10000, 50000, 100000};
    const int num_sizes = 5;

    for (int i = 0; i < num_sizes; ++i) {
        int n = sizes[i];
        
        // Тест 1: Случайные данные
        runTestScenario(n, RANDOM);
        
        // Тест 2: Уже отсортированные данные (Возрастание)
        // Лучший случай для Хоара, худший для Last Pivot
        runTestScenario(n, SORTED_ASC);

        // Тест 3: Обратно отсортированные данные (Убывание)
        runTestScenario(n, SORTED_DESC);
        
        cout << string(95, '-') << endl; // Разделитель таблицы
    }

    return 0;
}
