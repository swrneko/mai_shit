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
}
