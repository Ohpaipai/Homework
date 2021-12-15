#pragma once

#ifndef _ENCRYPTION_H
#define _ENCRYPTION_H

#include"./node.h"
#include<iostream>
#include<sstream>
#include<fstream>
#include<map>
#include<cctype>
#include<algorithm>

class encryption;

class encryption{
	public:
		encryption();
		~encryption();
		
		//operator
		const	int			getArea()				{ return area; 					}
		const 	std::string	getKey()				{ return key;					}
		const	int			getKeylen()				{ return KEY_Ary.size();		}
				void		insertNODE(NODE *_node)	{ NODE_Ary.push_back(_node);	}
				void		insertPI(NODE *_node)	{ PI_Ary.push_back(_node);		}
				void		insertPO(NODE *_node)	{ PO_Ary.push_back(_node);		}
				void		insertKey(NODE *_node)	{ KEY_Ary.push_back(_node);		}
				void		readfile(std::string);				//read .bench file
				void		witefile();				//write .bench file with encryption
				void		topological_sort();		// pre-process for logic cone
	private:
		std::vector<NODE*>			NODE_Ary;
		std::vector<NODE*>			PI_Ary;
		std::vector<NODE*>			PO_Ary;
		std::vector<NODE*>			KEY_Ary;
		std::map<std::string, NODE*>	name2node;
		std::string 			 	key;
		int 					 	area;
		void						caculateArea();
};

#endif
