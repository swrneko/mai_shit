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
* Last Revision : 12/11/24                                      *
* Comment(s)    : Сумма ряда.                                   *
****************************************************************/
#include <cmath>
#include <iostream>
using namespace std;

float tsum = 0.75;
int count = 1;
int n = 2;
float sum, eps, diff = 0;

/*
esp - ввод точности
n - порядковый номер элемента
count - кол-во суммированных эл-тов
sum - сумма
diff - разность точного значенме и суммы
*/

void inpt_varibles() {
  cout << "Введите точность: ";
  cin >> eps;
  diff = fabs(tsum - sum);

  if (eps <= 0) {
    cout << "Введённое число меньше или равно нулю.\n";
    exit(1);
  }
}

void main_computing() { // основные вычисления
  while (diff >= eps) {
    sum = (sum + (1 / (pow(n, 2) - 1)));
    n += 1;
    count += 1;
    diff = fabs(tsum - sum);
  }
  cout << "Количество просуммированных элементов: " << count << "\nСумма: " << sum << "\nРазность суммы и точного значения: " << diff << endl;
}



int main() { // основное тело
  inpt_varibles();
  main_computing();
}
