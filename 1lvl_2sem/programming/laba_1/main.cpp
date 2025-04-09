#include <iostream>
using namespace std;
const int SIZE = 100;

void similarWordsInTwoLines(char* str0, char* str1);

int main(){
  char str0[SIZE];
  char str1[SIZE];
  char ch;

  cout << "Введите 1-ую строку: ";
  cin.getline(str0, SIZE); 

  cout << "Введите 2-ую строку: ";
  cin.getline(str1, SIZE); 

  cout << "Символ: ";
  cin >> ch;
  
  similarWordsInTwoLines(str0, str1);
}

void similarWordsInTwoLines(char* str0, char* str1) {
  char word0[SIZE];
  char word1[SIZE];
  int k, m, l = 0;

  /* Считаем количество рядов массива хранящего массивы строк */
  for(int i = 0; str0[i] != '\0'; i++) {
    if(str0[i] == ' ') {
      word0[k] = '\0';
      k=0;

      for(int j = 0; str1[i] != '\0'; j++) {
        if(str1[j] == ' ') {
          word1[m] = '\0';
          m = 0;
          while(true) {
            if(word0[l] != word1[l]){
              cout << "Слова не совпали";
              break;
            }
            if(word0[l] == '\0' || word1[l] == '\0') {
              cout << "Слова одинаковые";
            }
            l++;
          }

          l = 0;
        }
        else {
          word1[m++] = str1[j];
        }
      }
    }
    else {
      word0[k++] = str0[i]; 
    }

  }
}
