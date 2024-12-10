#include <iostream>
#include <fstream>
using namespace std;

int main() {
  int n;
  int m;
  const int SIZE = 10;
  float IVEC[SIZE];
  float NEWVEC[SIZE/2];
  float summ = 0;
  float min = 0;


  ifstream SourceFile;
  SourceFile.open("files/source.txt");

  // Проверка на открытие файла
  if (!SourceFile.is_open()) {
    cout << "Неудалось прочитать файл";
    SourceFile.close();
    exit(1);
  }

}
