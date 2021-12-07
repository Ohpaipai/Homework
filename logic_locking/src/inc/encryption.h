#pragma once

#ifndef _ENCRYPTION_H
#define _ENCRYPTION_H

#include"./node.h"
#include<iostream>

class ENCRYPTION;

class ENCRYPTION{
	public:
		ENCRYPTION(){}
		~ENCRYPTION(){}
		
		//operator
		const	int			getArea()				{ return area; 					}
		const 	std::string	getKey()				{ return key;					}
		const	int			getKeylen()				{ return KEY_Ary.size();		}
				void		insertNODE(NODE *_node)	{ NODE_Ary.push_back(_node);	}
				void		insertPI(NODE *_node)	{ PI_Ary.push_back(_node);		}
				void		insertPO(NODE *_node)	{ PO_Ary.push_back(_node);		}
				void		insertKey(NODE *_node)	{ KEY_Ary.push_back(_node);		}
	private:
		std::vector<NODE*>	NODE_Ary;
		std::vector<NODE*>	PI_Ary;
		std::vector<NODE*>	PO_Ary;
		std::vector<NODE*>	KEY_Ary;
		std::string 		key;
		int 				area;
};

#endif
