#pragma once

#ifndef NODE_H
#define NODE_H

#include<string>
#include<iostream>
#include<vector>

#define cost(arg1,arg2) ({ \
	int flag = 0; \
	if(arg1 == FType::XNOR || arg1 == FType::XOR) {\
		flag = 3; \
	} else if(arg1 == FType::NOT || arg1 == FType::BUF){\
		flag = 1; \
	} else { \
		flag = (int)arg2-1;\
	}\
	flag; \
})

enum class Type{ 
	Intl, 
	PI, 
	PO
};

enum class FType {
	AND, 
	OR, 
	NOR, 
	NAND, 
	NOT, 
	BUF, 
	XOR, 
	XNOR
};

class NODE;

class NODE{
	public:
		NODE(){}
		NODE()(Type t, FType _ft, std::string _name)
			:t(
	private:
		Type					t;
		FType					ft;
		std::vector<NODE*>		FI_Ary;
		std::vector<NODE*>		FO_Ary;
		std::string				name;
};

#endif
