#include <stdio.h>
#include <math.h>
#include <string.h> 
#include <time.h>

char AUTHOR_SECOND_NAME[] = "egorov";

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
  printf("\n%s",
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
  for(int i=48,s; i != -1 ; i += 10) {

    /* Расчёт квадрата двойки */
    two_grade_demical = pow(2, i);

    /* Остановка цикла при выходе значения переменной за размер типа данных */
    if (two_grade_demical == 0) {
      break;
    }

    /* Просчёт разницы старого и нового значения степени двойки т.е. нахождение разницы в 1 000 000 000 с последующей печатью фамилии автора */
    if ((two_grade_demical - two_grade_demical_old) >= 1000000000000) {
      printf("%s %-19llu %-16s","|", two_grade_demical, "|");
      printf("%s %-15s %s\n", "|", "Egorov", "|");
      two_grade_demical_old = two_grade_demical;
    }
    else {
      printf("%llu\n", two_grade_demical);
    }

    /* Обновление старго значения по концу цикла */
    i+=1;
  }
  /* Вывод конеца */
  printf("%s", "---------------------------------------------------------\n");
}

 /* 
 * Функция выполнения побитового сдвига принимает на вход 4 параметра:
 * 0. первое направление сдвига (l - левое и r - правое)
 * 1. второе направление сдвига, параметры аналогично первому
 * 2. передаваемое число для сдвига
 * 3. фамилия автора (подсчёт кол-ва символов в фамилии - сдвиг на это кол-во символов)
 */ 
void bitShiftAction(char * dir_first, char * dir_second, int input_num, char * AUTHOR_SECOND_NAME) {
  int lenth_author_second_name = strlen(AUTHOR_SECOND_NAME); // Расчёт кол-ва символов в фамилии
  double bit_shift_left; // Значение "input_num" после сдвига влево
  double bit_shift_right; // Значение "input_num" после сдвига вправо

  /* Побитовый сдвиг влево, затем вправо на кол-во символов в фамилии автора */
  if (strcmp(dir_first, "l") == 0 && strcmp(dir_second, "r") == 0) {
    bit_shift_left = input_num << lenth_author_second_name; // Побитовый сдвиг влево 
    printf("\t%s %0.f\n", "Bit shift left:", bit_shift_left); // Вывод побитового сдвига влево
    bit_shift_right = input_num >> lenth_author_second_name;  // Побитовый сдвиг вправо
    printf("\t%s %0.f\n", "Bit shift right:", bit_shift_right); // Вывод побитового сдвига вправо
  }

  /* Побитовый сдвиг влево, затем влево на кол-во символов в фамилии автора */
  if (strcmp(dir_first, "r") == 0 && strcmp(dir_second, "l") == 0) {
    bit_shift_right = input_num >> lenth_author_second_name; // Побитовый сдвиг вправо
    printf("\t%s %0.f\n", "Bit shift right:", bit_shift_right); // Вывод побитового сдвига вправо
    bit_shift_left = input_num << lenth_author_second_name;  // Побитовый сдвиг влево
    printf("\t%s %0.f\n", "Bit shift left:", bit_shift_left); // Вывод побитового сдвига влево
  }
}

/* Функция вывода побитового сдвига */
void bitShift(void) {
  int two_grade_32_shift = pow(2, 32);

  printf("\n%s",
  "#########################################################\n"
  "# ########   #######  #### ##    ## ########   #######  #\n"
  "# ##     ## ##     ##  ##  ###   ##    ##     ##     ## #\n"
  "# ##     ## ##     ##  ##  ####  ##    ##            ## #\n"
  "# ########  ##     ##  ##  ## ## ##    ##      #######  #\n"
  "# ##        ##     ##  ##  ##  ####    ##            ## #\n"
  "# ##        ##     ##  ##  ##   ###    ##     ##     ## #\n"
  "# ##         #######  #### ##    ##    ##      #######  #\n"
  "#########################################################\n");

  /* Вывод двойки в 32 степени (базовый вывод) */
  printf("%s \n\t%s %d\n\n", "Basic output:", "2^32:", two_grade_32_shift);

  /* Вывод побитового сдвига для первой и второй переменной (дополнительный вывод) */
  printf("%s\n", "Bit shift for first varible.");
  bitShiftAction("l", "r", two_grade_32_shift, AUTHOR_SECOND_NAME);
  printf("\n%s\n", "Bit shift for second varible.");
  bitShiftAction("r", "l", two_grade_32_shift, AUTHOR_SECOND_NAME);
  }


int main() {
  clock_t clock_time_start;
  clock_t clock_time_end;
  time_t real_time_start;
  time_t real_time_end;
  double clock_time_used;
  double real_time_used;

  clock_time_start = clock();
  time(&real_time_start);

  countGradeOfTwo(); // Подсчёт и вывод степени двойки в 2-х системах счисления
  authorSecondName(); // Вывод фамилии автора спустя каждый 1 000 000 000 
  bitShift(); // Расчёт и вывод побитового сдвига влево, затем вправо

  clock_time_end = clock(); 
  time(&real_time_end);

  clock_time_used = ((double) (clock_time_end - clock_time_start)) / CLOCKS_PER_SEC;
  real_time_used = difftime(real_time_end, real_time_start);

  printf("\nTIME METRICKS:\n\tCPU time used: %0.4f\n\tReal time used:%0.4f\n", clock_time_used, real_time_used);
}
