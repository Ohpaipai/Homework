//#include "./inc/node.h"
#include "./inc/encryption.h"
int main(int argc, char* argv[]){

	#ifndef debug
		std::cout<<"debug\n";	
		FType a = FType::XNOR;
		FType b = FType::XOR;
		FType c = FType::NOR;
		std::cout<<(a==b)<<std::endl;
		std::cout<<cost(c,100)<<std::endl;
		
		NODE *A =new NODE();
		NODE *B =new NODE();
		NODE *C =new NODE();
		std::vector<NODE*>ary;
		ary.push_back(A);
		A->setName("A");
		ary.push_back(B);
		B->setName("B");
		ary.push_back(C);
		C->setName("C");

		ary[1]->insertFO(C);
		ary[1]->insertFO(A);
		std::cout<<"Index="<<ary[1]->FOfind(A)<<std::endl;
		std::cout<<(A==ary[0])<<std::endl;
	#endif
	

		encryption* enc = new encryption();
		enc->readfile(argv[1]);
		enc->topological_sort();
		enc->Flogic_cone();
	return 0;
}
