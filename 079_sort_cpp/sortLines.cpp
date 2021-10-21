#include <ifstream>
#include <iostream>

int main(int argc, char ** argv) {
  if (argc == 1) {
    cin.getline();  //
  }
  else {
    for (int i = 1; i < argc; i++) {
      ifstream infile;
      infile.open(argv[i]);
      istream & is = NULL;
      string & str = NULL;
      while (std::getline(is, str) >= 0) {  //
      }
    }
  }
  infile.close();
  return 0;
}
