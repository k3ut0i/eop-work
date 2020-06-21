#include<Types.h>
#include<iostream>

template<typename Op>
Codomain(Op) square(Domain(Op) i, Op op) {
  return op.func(std::array<Domain(Op), 2>{i, i});
};

int mult_v(std::array<int, 2> a){return a[0] * a[1];}
int add_v(std::array<int, 2> a){return a[0] + a[1];}
std::string concat_v(std::array<std::string, 2> a){return a[0] + a[1];}
int main()
{
  
  // Expected Computed
  std::cout << 49 << " "
	    << square<binaryOperation<int>>(7, mult_v) << " "
	    << "multiplication" << std::endl;
  std::cout << 14 << " "
	    << square<binaryOperation<int>>(7, add_v) << " "
	    << "addition" << std::endl;
  std::cout << "hey1hey1" << " "
	    << square<binaryOperation<std::string>>("hey1", concat_v) << " "
	    << "string-concatenation" << std::endl;
  return 0;
}
