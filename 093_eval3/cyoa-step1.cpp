#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "page.hpp"
int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Wrong number of argument!." << std::endl;
    exit(EXIT_FAILURE);
  }
  Page p;
  p.ReadOnePage(argv[1]);
  return EXIT_SUCCESS;
}
