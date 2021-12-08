#pragma once

#ifndef _NODE_H
#define _NODE_H

#include<string>
#include<iostream>
#include<vector>

#define debug

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

		NODE()
			:t(Type::Intl), ft(FType::BUF), name(""){
		}



		NODE(Type _t, FType _ft, std::string _name)
			:t(_t), ft(_ft), name(_name){
		}

		~NODE(){}
		
		//operator overloading
		bool operator ==(NODE* _A){
			//std::cout<<"test ->" <<name<<" , "<<_A->getName()<<std::endl;
			return name == _A->getName();
		}
		bool operator ==(std::string _name){
			//std::cout<<"testB ->" <<name<<" , "<<_name<<std::endl;
			return name == _name;
		}

		
		//operator
		const 	int 		getCost()					{ return cost(ft, FI_Ary.size());	}
		const 	int 		getFIlen()					{ return FI_Ary.size();				} 
		const 	int 		getFOlen()					{ return FO_Ary.size();				}
		const 	std::string	getName()					{ return name;						}
			 	void		setName(std::string _name)	{ name = _name;						}
		const 	int	 		getPathlen()				{ return path_len;					}
		 		void	  	setPathlen(int _len)		{ path_len = _len;					}
				void		insertFI(NODE* _node)		{ FI_Ary.push_back(_node);			}
				void		eraseFI(NODE* _node);
				void		insertFO(NODE* _node)		{ FO_Ary.push_back(_node);			}
				void		eraseFO(NODE* _node);
		const	int		 	FIfind(NODE* _node);		//return index
		const	int		 	FOfind(NODE* _node);		//return index
	private:
		Type				t;
		FType				ft;
		std::vector<NODE*>	FI_Ary;
		std::vector<NODE*>	FO_Ary;
		std::string			name;
		int		 	 		path_len;
};

#endif
