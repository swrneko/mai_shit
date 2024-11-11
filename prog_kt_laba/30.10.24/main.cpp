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

void main_computing() { // основные вычисления
  while (n != eps) {
    sum = (sum + (1 / (pow(n, 2) - 1)));
    n += 1;
    count += 1;
  }
  diff = fabs(sum - tsum);
  cout << "Количество просуммированных элементов: " << count << "\nСумма: " << sum << "\nРазность суммы и точного значения: " << diff << endl;
}

void inpt_varibles() {
  cout << "Введите точность: ";
  cin >> eps;

  if (eps <= 0 or floor(eps) != eps or eps == 1) {
    cout << "Введённое число меньше или равно нулю, не является целочисленны или равняется 1.\n";
    exit(1);
  }
}

int main() { // основное тело
  inpt_varibles();
  main_computing();
}
