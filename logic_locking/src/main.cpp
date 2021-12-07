#include "./inc/node.h"

int main(){
	
	FType a = FType::XNOR;
	FType b = FType::XOR;
	FType c = FType::NOR;
	std::cout<<(a==b)<<std::endl;
	std::cout<<cost(c,100)<<std::endl;
	return 0;
}
