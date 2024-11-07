#include <iostream>
#include "MyTemplate.h"

int main(int argc, char** argv)
{

  Test<int> t1(1, 2);
  Test<double> t2(1.0, 2);

  std::cout << t1.bigger() << std::endl;
  std::cout << t2.bigger() << std::endl;
 
  return 0;
}