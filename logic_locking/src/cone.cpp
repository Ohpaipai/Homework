#include"./inc/cone.h"


void CONE::eraseInput(NODE* _node){
	std::set<NODE*>::iterator it;
	it = input.find(_node);
	input.erase(it);
}

int CONE::IntersectionSize(CONE* _cone){

	std::set<NODE*>U;
	U.clear();
	std::set_intersection(input.begin(), input.end(), _cone->getInput().begin(), _cone->getInput().end(), std::inserter(U, U.begin()));
	return U.size();
}


bool CONE::operator ==(CONE* _C){
	if( (_C->getInput() == input) && (_C->getOutput() == output) )
		return true;
	else
		return false;
}

std::ostream& operator<<(std::ostream& os, CONE* _cone){
	os<<_cone->output->getName()<<" -> \n";
	for(auto p: _cone->input){
		os<<p->getName()<<" ";
	}
	os<<"\n";

	return os;

}
