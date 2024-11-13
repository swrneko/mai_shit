/****************************************************************
*                     КАФЕДРА № 304 1 КУРС                      *
*---------------------------------------------------------------*
* Project Type  : GNU/Linux Console Application                 *
* Project Name  : proj_1                                        *
* File Name     : main.cpp                                      *
* Language      : C/C++                                         *
* Programmer(s) : Егоров А.В (swrneko), Федоров А.И.            *
* Modifyed By   : Егоров А.В (swrneko)                          *
* Edited by     : Neovim, Visual Studio                         *
* OS            : Arch Linux, Windows 11                        *
* Github url    : https://github.com/swrneko/mai_shit.git       *
* Lit source    :                                               *
* Created       : 05/11/24                                      *
* Last Revision : 13/11/24                                      *
* Comment(s)    : Сумма ряда.                                   *
****************************************************************/
#include <cmath>
#include <iostream>
using namespace std;

float tsum = 0.75; // точная сумма
int count = 1; // count - кол-во суммированных эл-тов
int n = 2; // n - порядковый номер элемента
float sum, eps, diff = 0; // sum - сумма, esp - ввод точности, diff - разность точного значенме и суммы

int main() { // основное тело
  setlocale(LC_ALL, "Russian");

  cout << "Введите точность: ";
  cin >> eps;
  diff = fabs(tsum - sum);

  if (eps <= 0) {
    cout << "Введённое число меньше или равно нулю.\n";
    exit(1);
  }

  while (diff >= eps) {
    sum = (sum + (1 / (pow(n, 2) - 1)));
    n += 1;
    count += 1;
    diff = fabs(tsum - sum);
  }
  cout << "Количество просуммированных элементов: " << count << "\nСумма: " << sum << "\nРазность суммы и точного значения: " << diff << endl;
}

