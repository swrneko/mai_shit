/****************************************************************
 *                     КАФЕДРА № 304 2 КУРС                      *
 *---------------------------------------------------------------*
 * Project Type  : GNU/Linux Console Application                 *
 * Project Name  : main                                          *
 * File Name     : main.cpp                                      *
 * Language      : C/C++                                         *
 * Programmer(s) : Егоров А.В (swrneko)                          *
 * Modifyed By   : Егоров А.В (swrneko)                          *
 * Edited by     : Neovim, Visual Studio                         *
 * OS            : Arch Linux                                    *
 * Github url    : https://github.com/swrneko/mai_shit.git       *
 * Created       : 5/11/25                                       *
 * Last Revision : 12/11/25                                      *
 * Comment(s)    : Алгоритм поиска                               *
 ****************************************************************/

// --- ПОДКЛЮЧЕНИЕ НЕОБХХОДИМЫХ БИБЛИОТЕК ---
#include <chrono> // Дает доступ к высокоточному "секундомеру" для замера времени выполнения кода.
#include <cstdlib> // Содержит функции для генерации случайных чисел (rand, srand).
#include <ctime> // Нужна для получения текущего времени, чтобы случайные числа были разными при каждом запуске.
#include <iomanip> // "Input/Output Manipulators" - инструменты для красивого форматирования вывода, например, для создания ровных колонок в таблице (setw).
#include <iostream> // Позволяет выводить текст в консоль (cout) и считывать ввод.
#include <string> // Позволяет использовать удобный тип "string" для работы с текстом.

// --- ИСПОЛЬЗОВАНИЕ ПРОСТРАНСТВ ИМЕН ---
using namespace std;
using namespace std::chrono;

// --- Структура для хранения результатов ---
struct SearchResult {
  int index; // Здесь будет индекс найденного элемента (или -1, если не нашли).
  long long time_microseconds; // Время, потраченное на поиск, в микросекундах.
  long long counter1;          // Счетчик сравнений ключа с элементом массива.
  long long counter2; // Счетчик сравнений индекса в циклах (например, i < n).
};

// --- БЫСТРАЯ СОРТИРОВКА СЛИЯНИЕМ (MERGE SORT) ---
// Этот алгоритм нужен, чтобы подготовить массив для бинарного поиска (BS) и OAS.

// Вспомогательная функция, которая мержит две отсортированные части массива в одну.
void merge(int *arr, int left, int mid, int right) {
  // Шаг 1: Узнаем размеры двух "половинок".
  int left_half_size = mid - left + 1;
  int right_half_size = right - mid;

  // Шаг 2: Создаем временные массивы, чтобы скопировать в них эти половинки.
  int *left_array = new int[left_half_size];
  int *right_array = new int[right_half_size];

  // Шаг 3: Копируем данные из основного массива во временные.
  for (int i = 0; i < left_half_size; i++)
    left_array[i] = arr[left + i];
  for (int j = 0; j < right_half_size; j++)
    right_array[j] = arr[mid + 1 + j];

  // Шаг 4: Сливаем временные массивы обратно в основной, расставляя элементы по
  // порядку.
  int i = 0;    // Индекс для левого временного массива
  int j = 0;    // Индекс для правого временного массива
  int k = left; // Индекс для основного массива

  while (i < left_half_size && j < right_half_size) {
    if (left_array[i] <= right_array[j]) {
      arr[k] = left_array[i];
      i++;
    } else {
      arr[k] = right_array[j];
      j++;
    }
    k++;
  }

  // Шаг 5: Если в одной из половинок остались элементы, просто дописываем их в
  // конец.
  while (i < left_half_size)
    arr[k++] = left_array[i++];
  while (j < right_half_size)
    arr[k++] = right_array[j++];

  // Шаг 6: Обязательно освобождаем память, занятую временными массивами.
  delete[] left_array;
  delete[] right_array;
}

// "Управляющая" функция сортировки. Она использует рекурсию (вызывает саму
// себя), чтобы разделить массив на мельчайшие части, а затем собирает их с
// помощью функции merge.
void mergeSort(int *arr, int left, int right) {
  if (left >= right) {
    return; // Если в куске 1 элемент или меньше, он уже отсортирован.
  }
  int mid = left + (right - left) / 2; // Находим середину
  mergeSort(arr, left, mid);           // Сортируем левую половину
  mergeSort(arr, mid + 1, right);      // Сортируем правую половину
  merge(arr, left, mid, right);        // Сливаем отсортированные половины
}

// --- РЕАЛИЗАЦИЯ АЛГОРИТМОВ ПОИСКА ---

// Алгоритм 1: BLS (Better Linear Search) - Простой линейный поиск
// Стратегия: Идти по массиву от начала до конца и сравнивать каждый элемент с
// ключом.
SearchResult BLS(const int *arr, int n, int key) {
  long long c1 = 0, c2 = 0;
  auto begin = steady_clock::now(); // Запускаем "секундомер"

  for (int i = 0; i < n; ++i) {
    c2++; // Считаем операцию сравнения индекса (i < n)
    c1++; // Считаем операцию сравнения ключа (arr[i] == key)
    if (arr[i] == key) {
      auto end = steady_clock::now(); // Останавливаем "секундомер"
      // Возвращаем структуру с результатами
      return {i, duration_cast<microseconds>(end - begin).count(), c1, c2};
    }
  }

  auto end = steady_clock::now(); // Останавливаем, если ничего не нашли
  return {-1, duration_cast<microseconds>(end - begin).count(), c1, c2};
}

// Алгоритм 2: SLS (Sentinel Linear Search) - Линейный поиск со "сторожем"
// Стратегия: Временно поставить искомый элемент в конец массива. Это позволяет
// убрать из цикла проверку `i < n`, что немного ускоряет его.
SearchResult SLS(int *arr, int n, int key) {
  long long c1 = 0, c2 = 0;
  if (n == 0)
    return {-1, 0, 0, 0};

  auto begin = steady_clock::now();
  int last = arr[n - 1]; // Сохраняем последний элемент

  c1++;
  if (last == key) { // Сразу проверяем, вдруг он и есть искомый
    auto end = steady_clock::now();
    return {n - 1, duration_cast<microseconds>(end - begin).count(), c1, c2};
  }

  arr[n - 1] = key; // Ставим "сторожа"

  int i = 0;
  while (arr[i] != key) { // В этом цикле теперь только одно сравнение!
    c1++;
    i++;
  }
  c1++; // Учитываем последнее, успешное сравнение

  arr[n - 1] = last; // Возвращаем исходный элемент на место
  auto end = steady_clock::now();

  c2++; // Делаем одну-единственную проверку, чтобы понять, что мы нашли.
  if (i < n - 1) { // Если `i` меньше, чем индекс последнего элемента...
    return {i, duration_cast<microseconds>(end - begin).count(), c1,
            c2}; // ...значит, мы нашли настоящий элемент.
  } else {
    return {-1, duration_cast<microseconds>(end - begin).count(), c1,
            c2}; // ...иначе мы нашли "сторожа".
  }
}

// Алгоритм 3: OAS (Ordered Array Search) - Поиск в отсортированном массиве
// Стратегия: Как и BLS, идти по порядку, но если мы наткнулись на элемент
// БОЛЬШЕ искомого, то можно сразу останавливаться - дальше его точно не будет.
SearchResult OAS(const int *arr, int n, int key) {
  long long c1 = 0, c2 = 0;
  auto begin = steady_clock::now();

  for (int i = 0; i < n; ++i) {
    c2++; // Сравнение индекса
    c1++; // Сравнение на равенство
    if (arr[i] == key) {
      auto end = steady_clock::now();
      return {i, duration_cast<microseconds>(end - begin).count(), c1, c2};
    }

    c1++; // Второе сравнение - на "больше"
    if (arr[i] > key) {
      break; // Выходим из цикла досрочно
    }
  }

  auto end = steady_clock::now();
  return {-1, duration_cast<microseconds>(end - begin).count(), c1, c2};
}

// Алгоритм 4: BS (Binary Search) - Бинарный поиск
// Стратегия: Смотреть на элемент в середине. Если он не подходит, отбрасывать
// половину массива и повторять поиск в оставшейся половине.
SearchResult BS(const int *arr, int n, int key) {
  long long c1 = 0, c2 = 0;
  auto begin = steady_clock::now();

  int left = 0, right = n - 1; // Границы области поиска

  while (left <= right) {
    c2++; // Считаем проверку условия цикла
    int mid =
        left + (right - left) / 2; // Вычисляем середину (безопасный способ)

    c1++;
    if (arr[mid] == key) { // Нашли!
      auto end = steady_clock::now();
      return {mid, duration_cast<microseconds>(end - begin).count(), c1, c2};
    }

    c1++;
    if (arr[mid] < key) { // Если середина меньше ключа...
      left = mid + 1;     // ...то ищем в правой половине.
    } else {              // Иначе...
      right = mid - 1;    // ...ищем в левой.
    }
  }
  c2++; // Последняя, неудачная проверка цикла

  auto end = steady_clock::now();
  return {-1, duration_cast<microseconds>(end - begin).count(), c1, c2};
}

// --- ФУНКЦИЯ ДЛЯ ПРОВЕДЕНИЯ ТЕСТОВ И ВЫВОДА РЕЗУЛЬТАТОВ ---

// Эта функция просто запускает все 4 алгоритма и печатает их результаты в
// красивой таблице.
void run_test_scenario(const string &scenario_name, int *unsorted_arr,
                       const int *sorted_arr, int n, int key) {
  cout << "  Сценарий: " << scenario_name << " (ключ = " << key << ")\n";
  cout << "  " << string(85, '-') << "\n";
  cout << "  | Алгоритм |   Индекс   | Время (мкс) | Сравнения ключа "
          "(counter1) | Сравнения индекса (counter2) |\n";
  cout << "  " << string(85, '-') << "\n";

  SearchResult res_bls = BLS(unsorted_arr, n, key);
  cout << "  | BLS      | " << setw(10) << res_bls.index << " | " << setw(11)
       << res_bls.time_microseconds << " | " << setw(26) << res_bls.counter1
       << " | " << setw(27) << res_bls.counter2 << " |\n";

  SearchResult res_sls = SLS(unsorted_arr, n, key);
  cout << "  | SLS      | " << setw(10) << res_sls.index << " | " << setw(11)
       << res_sls.time_microseconds << " | " << setw(26) << res_sls.counter1
       << " | " << setw(27) << res_sls.counter2 << " |\n";

  SearchResult res_oas = OAS(sorted_arr, n, key);
  cout << "  | OAS      | " << setw(10) << res_oas.index << " | " << setw(11)
       << res_oas.time_microseconds << " | " << setw(26) << res_oas.counter1
       << " | " << setw(27) << res_oas.counter2 << " |\n";

  SearchResult res_bs = BS(sorted_arr, n, key);
  cout << "  | BS       | " << setw(10) << res_bs.index << " | " << setw(11)
       << res_bs.time_microseconds << " | " << setw(26) << res_bs.counter1
       << " | " << setw(27) << res_bs.counter2 << " |\n";

  cout << "  " << string(85, '-') << "\n\n";
}

// --- ГЛАВНАЯ ФУНКЦИЯ ПРОГРАММЫ ---
// Выполнение программы всегда начинается с функции main.

int main() {
  // --- Фаза 1: Начальная настройка ---
  setlocale(LC_ALL, "Russian"); // Включаем поддержку русского языка в консоли
  srand(time(0)); // Инициализируем генератор случайных чисел текущим временем,
                  // чтобы они были разными при каждом запуске

  // Массив с размерами, которые мы будем тестировать
  const int num_sizes = 6;
  int sizes[num_sizes] = {50000, 100000, 150000, 200000, 250000, 300000};

  // --- Фаза 2: Основной цикл тестирования ---
  // Этот цикл будет повторять весь эксперимент для каждого размера из массива
  // `sizes`.
  for (int s = 0; s < num_sizes; ++s) {
    int n = sizes[s];

    cout << string(90, '=') << "\n";
    cout << "Тесты для массива размером " << n << " элементов\n";
    cout << string(90, '=') << "\n\n";

    // --- Фаза 3: Подготовка данных ---
    // Так как массивы очень большие, мы не можем создать их на стеке.
    // Мы запрашиваем память для них в "куче" (heap) с помощью `new[]`.
    int *unsorted_array = new int[n];
    int *sorted_array = new int[n];

    // Заполняем оба массива одинаковыми случайными числами
    for (int i = 0; i < n; ++i) {
      unsorted_array[i] = rand();
      sorted_array[i] = unsorted_array[i]; // Делаем точную копию
    }

    // --- Фаза 4: Сортировка ---
    // Сортируем ТОЛЬКО копию, чтобы оставить оригинальный массив
    // несортированным для BLS и SLS.
    auto sort_begin = steady_clock::now();
    mergeSort(sorted_array, 0, n - 1);
    auto sort_end = steady_clock::now();
    auto sort_time = duration_cast<milliseconds>(sort_end - sort_begin);
    cout << "  (Время на сортировку массива: " << sort_time.count()
         << " мс)\n\n";

    // --- Фаза 5: Определение ключей для тестов ---
    int key_at_start =
        sorted_array[0]; // Для лучшего случая берем первый элемент
    int key_in_middle = sorted_array[n / 2]; // Для среднего - центральный
    int key_not_found = 999999999; // Для худшего - число, которого точно нет

    // --- Фаза 6: Запуск сценариев ---
    run_test_scenario("Ключ в начале", unsorted_array, sorted_array, n,
                      key_at_start);
    run_test_scenario("Ключ в середине", unsorted_array, sorted_array, n,
                      key_in_middle);
    run_test_scenario("Ключ отсутствует", unsorted_array, sorted_array, n,
                      key_not_found);

    // --- Фаза 7: Очистка памяти ---
    // КРАЙНЕ ВАЖНО: Память, которую мы запросили с помощью `new[]`, нужно
    // вернуть операционной системе с помощью `delete[]`. Иначе произойдет
    // утечка памяти.
    delete[] unsorted_array;
    delete[] sorted_array;
  }

  return 0; // Сообщаем, что программа завершилась успешно
}
