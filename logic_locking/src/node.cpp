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

void NODE::eraseFI(NODE* _node){
	FI_Ary.erase( FI_Ary.begin() + FIfind(_node) );	
}

void NODE::eraseFO(NODE* _node){
	FO_Ary.erase( FO_Ary.begin() + FOfind(_node) );	
}
