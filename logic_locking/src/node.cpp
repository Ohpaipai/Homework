#include"./inc/node.h"

std::ostream& operator<<(std::ostream& os, Type _t)
{
    switch(_t)
    {
		case Type::Intl		: os << "Intl";   break;
		case Type::PI 		: os << "PI"; 	  break;
		case Type::PO 		: os << "PO";  	  break;
        default    			: os.setstate(std::ios_base::failbit);
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, FType _ft)
{
    switch(_ft)
    {
		case FType::AND   	: os << "AND";  	  break;
		case FType::OR 		: os << "OR"; 		  break;
		case FType::NOR 	: os << "NOR"; 	 	  break;
		case FType::NAND 	: os << "NAND";  	  break;
		case FType::NOT 	: os << "NOT"; 	 	  break;
		case FType::XNOR 	: os << "XNOR"; 	  break;
		case FType::XOR 	: os << "XOR";  	  break;
		case FType::BUF 	: os << "BUF";  	  break;
        default    			: os.setstate(std::ios_base::failbit);
    }
    return os;
}

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
