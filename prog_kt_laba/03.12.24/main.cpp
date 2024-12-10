/**************************************************************
* КАФЕДРА # 304 1 КУРС М3О-111Б-23
*
*-------------------------------------------------------------*
* Project Type : Win32 Console Application *
* Project Name : IKTLabProject#3
*
* File Name : IKTLabProject#3.CPP
*
* Language : C/C++ *
* Programmer(s) : Корепанов Д.А. Назаров М.В.
*
* Modified By : *
* Created : 19/11/23 *
* Last Revision : 19/11/23 *
* Comment(s) :
**************************************************************/

#include <iostream>
#include <fstream>
using namespace std;

int main()
{
  int N; //Величина N
  int M; // Величина M
  const int SIZE = 10; // Константа размеров массива
  float VEC[SIZE]; // Массив VEC из файла
  float NEWVEC[SIZE/2]; // Формируемый массив NEWVEC
  float Summ = 0; // Сумма первых M элементов массива
  float Min = 0; // Значение наибольшего отрицательного элемента

  ifstream fin;
  fin.open("LabFile.txt");

  // Проверка данных на вход.
  if (!fin.is_open()) {
    cout << "File opening error.";
    fin.close();
    return 5;
  }

  // Чтение данных из файла
  fin >> N;

  if (fin.eof()) { // Проверка файла на пустоту
    cout << "File is empty.";
    fin.close();
    return 9;
  }

  if (fin.fail()) { // Проверка типа данных при чтении
    cout << "File reading error.";
    fin.close();
    return 6;
  }

  fin >> M;

  if (fin.fail()) { // Проверка типа данных при чтении
    cout << "File reading error.";
    fin.close();
    return 7;
  }
  for (int i = 0; i < SIZE; i++) {
    fin >> VEC[i];

    if (fin.fail()) { // Проверка типа данных при чтении
      cout << "File reading error.";
      fin.close();
      return 8;
    }
  }

  // Входной контроль
  if (N <= 0) {
    cout << "Enter N incorrectly. N must be > 0." << endl;
    fin.close();
    return 1;
  }

  if (N > SIZE / 2) {
    cout << "Enter N incorrectly. N must be < SIZE/2." << endl;
    fin.close();
    return 2;
  }

  if (M <= 0) {
    cout << "Enter M incorrectly. M must be > 0." << endl;
    fin.close();
    return 3;
  }

  if (M > SIZE / 2) {
    cout << "Enter M incorrectly. M must be < SIZE/2." << endl;
    fin.close();
    return 4;
  }

  for (int i = 0; i < SIZE / 2; i++) {
    NEWVEC[i] = (VEC[2*i] + VEC[2*i + 1])/2;// Формирование нового массива
    if (i < M) Summ += NEWVEC[i];// Подсчет суммы первых M элементов нового
    if (NEWVEC[i] < 0) {// Определение значение Min в массиве NEWVEC
    if (Min == 0) Min = NEWVEC[i];// Задаем начальное значение Min
    if (NEWVEC[i] > Min) Min = NEWVEC[i];// Ищем наибольший отрицательный
  }

  if (i == 0) cout << "NEWVEC: ";// Печать сформированного массива
    cout << NEWVEC[i] << ", ";
  }

  cout << endl << "Summ = " << Summ << endl;

  if (Min == 0) cout << "No negative elements are found in the range from 1 to "<< N << endl;
  else cout << "Maximum negative element = " << Min << endl;

  // Выводим индексы элементов массива равных Min
  for (int i = 0; i < N; i++) {

    // Проверка на нахождение нужного элемента
    if (Min == 0) break;

    //Вывод Индексов при нахождении
    if (i == 0) cout << "Indexes of the searched elements: ";
    if (NEWVEC[i] == Min) cout << i << " ";
  }

  fin.close();
  return 0;
}
