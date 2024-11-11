#include <cmath>
#include <iostream>
using namespace std;

float tsum = 0.75;
int count, n, slag = 0;
float sum, eps, diff = 0;

/*
esp - ввод точности
n - порядковый номер элемента
count - кол-во суммированных эл-тов
sum - сумма
diff - разность точного значенме и суммы
*/

void init_var() { // иницавлизвция переменных
  n = 2;
  diff = fabs(tsum - sum);
}

void main_computing() {
  while (sum != eps) {
    sum = (1 / ((n - 1) * (n + 1)));
    n += 1;
    cout << sum << endl;
    cout << n << endl;
  }
}

int main() { // основное тело
  cout << "Введите точность: ";
  cin >> eps;
  init_var();
  main_computing();
}
