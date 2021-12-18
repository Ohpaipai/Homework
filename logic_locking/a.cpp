#include<iostream>
#include <set>
#include<vector>
void A(std::set<int> &S){
	S.insert(10);
}

int main(){
	std::set<int>B;
	A(B);
	std::vector<std::set<int>>C;
	C.push_back(B);
	return 0;

}
