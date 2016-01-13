/**
 * g++ -std=c++11 -Wall -Werror -O2 -o test31 SMatrix.cpp test31.cpp
 * On williams this test take about 0.2 secs when executed 
 * with my implementation, * which only uses straightforward
 * optimisations.
 *
 *
 * % uname -a
 % Linux wagner 2.6.38-2-amd64 #1 SMP Thu Apr 7 06:43:20 UTC 2011 x86_64 GNU/Linux
 * % time ./test3 > test3.out
 * 
 * real	0m0.230s
 * user	0m0.092s
 * sys	0m0.016s
 */

#include <iostream>
#include "SMatrix.h"

int main(void) {
  SMatrix a(5000, 1000);
  for (SMatrix::size_type i = 0; i < 200; ++i)
    for (SMatrix::size_type j = 0; j < 200; ++j)
      a.setVal(i + 1000, j + 1000, -1);

  SMatrix b(1000, 5000);
  for (SMatrix::size_type i = 0; i < 200; ++i)
    for (SMatrix::size_type j = 0; j < 200; ++j)
      b.setVal(i + 1000, j + 1000, -1);

  //std::cout << a * b << std::endl;
   std::cout << a << std::endl;
  return 0;
}
