/*************************************************************************************
*                              КАФЕДРА № 304 1 КУРС                                  *
*------------------------------------------------------------------------------------*
* Project Type  : GNU/Linux Console Application                                      *
* Project Name  : laba_0                                                             *
* File Name     : main.cpp                                                           *
* Language      : C/C++                                                              *
* Programmer(s) : Егоров А.В (swrneko), Федоров А.И, Трифанов А.Л, Мурзамуратов И.Н. *
* Modifyed By   : Егоров А.В (swrneko)                                               *
* Edited by     : Neovim, Visual Studio, Sublime Text                                *
* OS            : Arch Linux, Windows 11/10                                          *
* Github url    : https://github.com/swrneko/mai_shit.git                            *
* Created       : 24.12/24                                                           *
* Last Revision : 24/12/24                                                           *
* Comment(s)    : Метод хорд поиска корней уравнения.                                *
*************************************************************************************/


#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    cout << fixed << setprecision(6);

    // Определяем границы поиска и шаги
    double start = -3.0, end = 3.0;
    int steps = 1000;

    // Поиск интервалов изменения знака функции
    vector<pair<double, double>> intervals;
    double step = (end - start) / steps;
    double x_prev = start;
    double y_prev = pow(x_prev, 3) - 2 * pow(x_prev, 2) - 4 * x_prev + 7;

    for (int i = 1; i <= steps; ++i) {
        double x_curr = start + i * step;
        double y_curr = pow(x_curr, 3) - 2 * pow(x_curr, 2) - 4 * x_curr + 7;
        if (y_prev * y_curr < 0) {
            intervals.emplace_back(x_prev, x_curr);
        }
        x_prev = x_curr;
        y_prev = y_curr;
    }

    cout << "Интервалы, где функция меняет знак:" << endl;
    for (auto &[a, b] : intervals) {
        cout << "[" << a << ", " << b << "]" << endl;
    }

    for (auto &[a, b] : intervals) {
        cout << "Интервал: " << "[" << a << ", " << b << "]" << endl;

        // Метод хорд (секущих)
        double x0 = a, x1 = b;
        double tol = 1e-6;
        int max_iter = 100;
        int iter_secant = 0;
        double root_secant = NAN;

        for (int i = 0; i < max_iter; ++i) {
            double fx0 = pow(x0, 3) - 2 * pow(x0, 2) - 4 * x0 + 7;
            double fx1 = pow(x1, 3) - 2 * pow(x1, 2) - 4 * x1 + 7;
            if (fabs(fx1 - fx0) < 1e-12) break; // предотвращение деления на ноль
            double x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);
            if (fabs(pow(x2, 3) - 2 * pow(x2, 2) - 4 * x2 + 7) < tol) {
                root_secant = x2;
                iter_secant = i + 1;
                break;
            }
            x0 = x1;
            x1 = x2;
        }

        // Метод Ньютона
        double x_newton = (a + b) / 2;
        int iter_newton = 0;
        double root_newton = NAN;

        for (int i = 0; i < max_iter; ++i) {
            double fx0 = pow(x_newton, 3) - 2 * pow(x_newton, 2) - 4 * x_newton + 7;
            double dfx0 = 3 * pow(x_newton, 2) - 4 * x_newton - 4;
            if (fabs(dfx0) < 1e-12) break; // предотвращение деления на ноль
            double x1 = x_newton - fx0 / dfx0;
            if (fabs(pow(x1, 3) - 2 * pow(x1, 2) - 4 * x1 + 7) < tol) {
                root_newton = x1;
                iter_newton = i + 1;
                break;
            }
            x_newton = x1;
        }

        cout << "  Метод хорд: корень = " << root_secant << ", итерации = " << iter_secant << "\n";
        cout << "  Метод касательных: корень = " << root_newton << ", итерации = " << iter_newton << "\n";
    }

    return 0;
}

