#include <stdio.h>
#include <math.h>

/* Функция подсчта и вывода степени двойки */
void countGradeOfTwo(void) {
  unsigned long long two_grade_demical = 1; // Значение степени двойки в 10 системе счисления
  unsigned long long two_grade_hexademical = 1; // Значение степени двойки в 16 системе счисления
  int grade = 64; // Количество степеней двойки
  int i = 0; // Счётчик итераций цикла вывода дынных
  int n = 0; // Счётчик итераций цикла подсчёта данных

  printf("%s", 
    "#########################################################\n"
    "# ########   #######  #### ##    ## ########       ##   # \n"
    "# ##     ## ##     ##  ##  ###   ##    ##        ####   # \n"
    "# ##     ## ##     ##  ##  ####  ##    ##          ##   # \n"
    "# ########  ##     ##  ##  ## ## ##    ##          ##   # \n"
    "# ##        ##     ##  ##  ##  ####    ##          ##   # \n"
    "# ##        ##     ##  ##  ##   ###    ##          ##   # \n"
    "# ##         #######  #### ##    ##    ##        ###### # \n"
    "#########################################################\n");


  /* Печать шапки */
  printf("%s", "---------------------------------------------------------\n");
  printf("%s %s %s %-28s %s %s %15s","|", "2^i", "|", "demical", "|", "hex", "|\n");
  printf("%s", "---------------------------------------------------------\n");

  /* Цикл вывода данных степеней двойки*/
  while(i != grade) {

    /* Подсчёт степени двойки в 2-х системах счисления */
    two_grade_demical = pow(2, i); // Подсчёт степени двойки в 10 системе счисления
    two_grade_hexademical = pow(2, i); // Подсчёт степени двойки в 16 системе счисления
    
    /* Форматирование вывода */
    if (i < 10) { // Добавление дополнительного пробела при порядковом номере меньше 10
      printf("%s%3d%s %-2s","|", i, ")", "|");
    }
    else { // Дефолтный вывод порядкового номера
      printf("%-2s%d%s %-2s","|", i, ")", "|");
    }
    printf("%-28llu %s %-16llx %s\n", two_grade_demical, "|", two_grade_hexademical, "|"); // Вывод значений двоек в 2-х системах счисления
    i += 1;
  }
  printf("%s", "---------------------------------------------------------\n");
}

/* Функция для вывод фамилии автора спустя каждый 1 000 000 000 */
void authorSecondName(void) {
  unsigned long long two_grade_demical = 1; // Значение степени двойки в степени
  unsigned long long two_grade_demical_old = 1; // Страрое значение двойки в степени (для вычисления разности) 

  /* Печать шапки */
  printf("%s",
    "#########################################################\n"
    "# #######   #######   #### ##    ## ########   #######  #\n"
    "# ##     ## ##     ##  ##  ###   ##    ##     ##     ## #\n"
    "# ##     ## ##     ##  ##  ####  ##    ##            ## #\n"
    "# ########  ##     ##  ##  ## ## ##    ##      #######  #\n"
    "# ##        ##     ##  ##  ##  ####    ##     ##        #\n"
    "# ##        ##     ##  ##  ##   ###    ##     ##        #\n"
    "# ##         #######  #### ##    ##    ##     ######### #\n"
    "#########################################################\n");

  printf("%s", "---------------------------------------------------------\n");

  /* Цикл для вывода фамилии автора при отличии значения на 1 000 000 000 */
  for(int i=63,s; i != -1 ; i += 10) {

    /* Расчёт квадрата двойки */
    two_grade_demical = pow(2, i);

    /* Остановка цикла при выходе значения переменной за размер типа данных */
    if (two_grade_demical == 0) {
      break;
    }

    /* Просчёт разницы старого и нового значения степени двойки т.е. нахождение разницы в 1 000 000 000 с последующей печатью фамилии автора */
    if ((two_grade_demical - two_grade_demical_old) >= 1000000000) {
      printf("%s %llu %-16s","|", two_grade_demical, "|");
      printf("%s %-15s %s\n", "|", "Egorov", "|");
      two_grade_demical_old = two_grade_demical;
    }
    else {
      printf("%llu\n", two_grade_demical);
    }

    /* Обновление старго значения по концу цикла */
    i+=1;
  }
  printf("%s", "---------------------------------------------------------\n");
}

int main() {
  countGradeOfTwo(); // Подсчёт и вывод степени двойки в 2-х системах счисления
  authorSecondName(); // Вывод фамилии автора спустя каждый 1 000 000 000 
}
