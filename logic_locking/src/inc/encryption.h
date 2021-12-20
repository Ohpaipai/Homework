#pragma once

#ifndef _ENCRYPTION_H
#define _ENCRYPTION_H

#include"./node.h"
#include"./cone.h"
#include<iostream>
#include<sstream>
#include<fstream>
#include<map>
#include<cctype>
#include<algorithm>
#include<stdio.h>
#include<cstring>

#define bug



class encryption;

bool compareNode(NODE *_node1, NODE *_node2 );


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
				void		Flogic_cone();			//get logic cone
				void		tree_encryption();		//encryption
				void		outputfile();
	private:
		std::vector<NODE*>				NODE_Ary;
		std::vector<NODE*>				PI_Ary;
		std::vector<NODE*>				PO_Ary;
		std::vector<NODE*>				KEY_Ary;
		std::vector<NODE*>				ENCY_Ary;
		std::map<std::string, NODE*>	name2node;
		std::string 			 		key;
		std::vector<CONE*>				LogicCone;
		std::string	 			 		filename;	
		int 					 		area;
		int 							keyCount;	
		std::vector<int>				color;
		std::vector<int>				color2;
		void							caculateArea();
		void							DFS(int,int*);
		void 							RecursiveFtype(NODE* _node, int& max, FType _ft);
		void  							RecursiveLogicCone(CONE*, NODE*, FType);
		void							AND_encryption(CONE*);
		void							OR_encryption(CONE*);
};

#endif
