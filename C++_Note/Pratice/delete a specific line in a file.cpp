#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 建立檔案填上內容
void create_file() {
  ofstream F;
  F.open("file.txt");
  if (F.fail())
    cout << "Error opening file.\n";
  F << "line 1\n"
    << "line 2\n";
}
int main() {
  create_file();

  string file_name;
  cout << "Input file name : ";
  getline(cin, file_name);
  int line;
  cout << "delete line ";
  cin >> line;

  // 先打開檔案
  ifstream file;
  file.open(file_name);
  if (file.fail()) {
    cout << "Error opening file.\n";
    return 1;
  }

  vector<string> store;
  string lines;

  // 把檔案內的文字全部讀取
  while (getline(file, lines)) {
    store.push_back(lines);
  }
  int line_length = store.size();
  file.close();

  // 把檔案打開
  ofstream f;
  f.open(file_name);
  if (f.fail()) {
    cout << "Error opening file.\n";
    return 1;
  }

  line--;
  for (int i = 0; i < line_length; i++) {
    if (i != line) {
      f << store[i] << endl;
    }
  }
  f.close();

  return 0;
}
