#include "bits/stdc++.h"
#include "fstream"
using namespace std;

int main(){
	fstream out;
	out.open("5000x4000.in",std::ios::out);
    out <<"grid 5000 4000"<<endl;
    out <<"capacity 40"<<endl;
    out <<"num net 2000"<<endl;
    int num=0;
    while(num<2000){
        out <<num<<" ";
        out<< rand()%5000<<" "<<rand()%4000<<" ";
        out<< rand()%5000<<" "<<rand()%4000<<endl;
        num++;
    }
}
