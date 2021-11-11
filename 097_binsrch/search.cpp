#include <cstdio>
#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  while (low + 1 < high) {
    int midium = (low + high) / 2;
    int f_x = f->invoke(midium);
    if (f_x == 0) {
      return midium;
    }
    else if (f_x > 0) {
      high = midium;
    }
    else {
      low = midium;
    }
  }
  return low;
}
