#include"./inc/node.h"

const int NODE::FIfind(NODE* _node){
	int return_index = -1;
	for(auto p : FI_Ary){
		if(*p == _node){
			return ++return_index;
		}
		++return_index;
	}
	return return_index;
}

const int NODE::FOfind(NODE* _node){
	int return_index = -1;
	for(auto p : FO_Ary){
		if(*p == _node){
			return ++return_index;
		}
		++return_index;
	}
	return return_index;
}
