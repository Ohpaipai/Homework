#include "./inc/encryption.h"

encryption::encryption(){
	NODE_Ary.clear();
	PI_Ary.clear();
	PO_Ary.clear();
	KEY_Ary.clear();
	key 	= "";
	area 	= 0;
}


encryption::~encryption(){
	for(auto p : NODE_Ary){
		delete p;
	}
	NODE_Ary.clear();
	for(auto p : PI_Ary){
		delete p;
	}
	PI_Ary.clear();
	for(auto p : PO_Ary){
		delete p;
	}
	PO_Ary.clear();
	for(auto p : KEY_Ary){
		delete p;
	}
	KEY_Ary.clear();
}


void encryption::readfile(std::string _filename){
	std::fstream input;
	input.open(_filename,std::ios::in);
	
	std::string buffer;
	
	while(std::getline(input, buffer)){
		std::string checkerflag = "";
		checkerflag.assign(buffer, 0, 2);
		
		if(checkerflag == "IN"){
			std::string name = "";
			name = buffer.assign(buffer, 6, buffer.size()-6);
			
			NODE *n =new NODE();
			n->setName(name);

			//push in
			NODE_Ary.push_back(n);
			PI_Ary.push_back(n);	
			//make find graph
			name2index[name] = n;

		}
		else if(checkerflag == "OU"){
			std::string name = "";
			name = buffer.assign(buffer, 7, buffer.size()-7);
			
			NODE *n =new NODE();
			n->setName(name);

			//push in
			NODE_Ary.push_back(n);
			PO_Ary.push_back(n);	
			//make find graph
			name2index[name] = n;
		}
		else{
		}

	}

	input.close();



}
