#include "./inc/encryption.h"
//#define bug

encryption::encryption(){
	NODE_Ary.clear();
	PI_Ary.clear();
	PO_Ary.clear();
	KEY_Ary.clear();
	name2node.clear();
	key="";
	area = 0;
}

encryption::~encryption(){
	for(auto p : NODE_Ary ){
		delete p;
	}
	NODE_Ary.clear();
	PI_Ary.clear();
	PO_Ary.clear();
	KEY_Ary.clear();
	name2node.clear();
	key="";
	area = 0;
}


void encryption::readfile(std::string _filename){
	std::fstream input;
	input.open(_filename,std::ios::in);
	
	std::string buffer;

	int coun = 0;
	while(std::getline(input, buffer)){
		std::string checkerflag = "";
		checkerflag.assign(buffer, 0, 2);
		//std::cout<<checkerflag<<std::endl;	
		//annotation
		if(buffer[0]=='#')
			continue;

		if(checkerflag == "IN"){
			std::string name = "";
			name.assign(buffer, 6, buffer.size()-7);
				
			Type	t  = Type::PI;
			FType	ft = FType::BUF;
			
			NODE *n;
			auto it = name2node.find(name);
			if(it == name2node.end() ){
				n =new NODE(t, ft, name);
				n->setId(coun++); //set ID	
				NODE_Ary.push_back(n);
				name2node[name] = n; 
			}
			else{
				n = it->second;
				n->setFtype(ft);
				n->setType(t);
			}
			//Input push in
			PI_Ary.push_back(n);


		}
		else if(checkerflag == "OU"){
			std::string name = "";
			name.assign(buffer, 7, buffer.size()-8);
			

			Type	t  = Type::PO;
			FType	ft = FType::BUF;
			
			NODE *n;
			auto it = name2node.find(name);
			if(it == name2node.end() ){
				n =new NODE(t, ft, name);
				n->setId(coun++); //set ID	
				NODE_Ary.push_back(n);
				name2node[name] = n; 
			}
			else{
				n = it->second;
				n->setFtype(ft);
				n->setType(t);
			}
			//push in
			PO_Ary.push_back(n);	
		}
		else{
		//	std::cout<<buffer<<std::endl;
			Type t =Type::Intl; //set type 
			FType ft;
			
			std::string tem_buf = "";
			std::stringstream ss;
			ss << buffer;
			
			//name
			std::string name = "";
			ss >> name;
		//	std::cout<<name<<std::endl;
			// = kill
			ss >> tem_buf;
		//	std::cout<<tem_buf<<std::endl;
			tem_buf.clear();
			

			//get Ftype
			ss >> tem_buf;
		//	std::cout<<tem_buf<<std::endl;
			std::string ft_name = "";
			ft_name.assign(tem_buf, 0, 3);

			std::transform(ft_name.begin(), ft_name.end(), ft_name.begin(), tolower);
		//	std::cout<<ft_name<<std::end;
			if(ft_name == "not"){
				ft = FType::NOT;
				tem_buf.assign(tem_buf, 4, tem_buf.size() - 4 );
			}
			else if(ft_name == "buf"){
				ft = FType::BUF;
				tem_buf.assign(tem_buf, 4, tem_buf.size() - 4 );
			}
			else if(ft_name == "and"){
				ft = FType::AND;
				tem_buf.assign(tem_buf, 4, tem_buf.size() - 4 );
			}
			else if(ft_name == "xor"){
				ft = FType::XOR;
				tem_buf.assign(tem_buf, 4, tem_buf.size() - 4 );
			}
			else if(ft_name == "xno"){
				ft = FType::XNOR;
				tem_buf.assign(tem_buf, 5, tem_buf.size() - 5 );
			}
			else if(ft_name == "nan"){
				ft = FType::NAND;
				tem_buf.assign(tem_buf, 5, tem_buf.size() - 5 );
			}
			else if(ft_name == "nor"){
				ft = FType::NOR;
				tem_buf.assign(tem_buf, 4, tem_buf.size() - 4 );
			}
			else if(ft_name == "or("){
				ft = FType::OR;
				tem_buf.assign(tem_buf, 3, tem_buf.size() - 3 );
			}
			else{
				continue;
			}

			//creat node & push
			auto it = name2node.find(name);
			NODE *n;
			if(it == name2node.end() ){
				n =new NODE(t, ft, name);
				n->setId(coun++); //set ID	
				NODE_Ary.push_back(n);
				name2node[name] = n; 
			}
			else{
				n = it->second;
				n->setFtype(ft);
			}

			//erase unuse char
			if(tem_buf[0] == '(')
				tem_buf.erase(tem_buf.begin());
			if(tem_buf[0] == ',')
				tem_buf.erase(tem_buf.begin());
			if(tem_buf[tem_buf.size()-1] == ',')
				tem_buf.pop_back();
			if(tem_buf[tem_buf.size()-1] == ')')
				tem_buf.pop_back();
		
			std::cout<<"insert node ( "<<name<<" ) = ";
			std::cout<<tem_buf<<" ";
			

			it = name2node.find(tem_buf);
			if(it == name2node.end() ){
				NODE *tem_n;
				tem_n =new NODE(t, FType::BUF, tem_buf);
				tem_n->setId(coun++); //set ID	
				NODE_Ary.push_back(tem_n);
				name2node[tem_buf] = tem_n; 
				//fan out
				tem_n->insertFO(n);
				//fan in
				n->insertFI(tem_n);
			}
			else{
				NODE *tem_n;
				tem_n = it->second;
				//fan out
				tem_n->insertFO(n);
				//fan in
				n->insertFI(tem_n);
			}

			
			//delete [] tem_n;

			//clear
			tem_buf.clear();
			tem_buf="";

			while(ss >> tem_buf){
				if(tem_buf[0] == '(')
					tem_buf.erase(tem_buf.begin());
				if(tem_buf[0] == ',')
					tem_buf.erase(tem_buf.begin());
				if(tem_buf[tem_buf.size()-1] == ',')
					tem_buf.pop_back();
				if(tem_buf[tem_buf.size()-1] == ')')
					tem_buf.pop_back();
			
				std::cout<<tem_buf<<" ";
				NODE *tem_n;	
				it = name2node.find(tem_buf);
				if(it == name2node.end() ){
					tem_n =new NODE(t, FType::BUF, tem_buf);
					tem_n->setId(coun++); //set ID	
					NODE_Ary.push_back(tem_n);
					name2node[tem_buf] = tem_n; 
				}
				else{
					tem_n = it->second;
				}
				//fan ou
				tem_n->insertFO(n);
				//fan in
				n->insertFI(tem_n);
			//	delete [] tem_n;
			}

			std::cout<<std::endl;
		}
		buffer.clear();
	}
	input.close();

	//caculate area
	this->caculateArea();


}

bool compareNode(NODE *_node1, NODE *_node2 ){
	return _node1->getEnd() > _node2->getEnd();
}

void encryption::caculateArea(){
	area = 0; //reset
	for(auto p : NODE_Ary){
		area += p->getCost();  
	}
}

void encryption::DFS(int _id, int* _time){
//	std::cout<<*_time<<std::endl;

	color[_id] = 2; //gray
	NODE_Ary[_id]->setStart((*_time)++);	
	for(auto p : NODE_Ary[_id]->getFO()){
		if(color[p->getId()] == 0){
			DFS(p->getId(), _time);	
		}
	}
//	std::cout<<*_time<<std::endl;
	color[_id] = 1;//black
	NODE_Ary[_id]->setEnd((*_time)++);

}


void encryption::topological_sort(){
	color = new int[NODE_Ary.size()];

	memset(color, 0, NODE_Ary.size()*sizeof(color)); //reset 0-> white , 1-> black , 2->gray

	int time = 0;
	
//	for(size_t i=0;i<NODE_Ary.size();i++)
//		std::cout<<color[i]<<std::endl;

	for(auto p : NODE_Ary){
		if(color[p->getId()]==0){
			DFS(p->getId() , &time);
		}
	}
	
//	for(size_t i=0;i<NODE_Ary.size();i++)
//		std::cout<<color[i]<<std::endl;

	delete [] color;

	//copy

	std::sort(NODE_Ary.begin(), NODE_Ary.end(), compareNode); //sory by finifsh time

	int count = 0;
	for(auto p :NODE_Ary){
		//reset id
		p->setId(count++); //set ID
		
		//and count 
		if(p->getFI().size()==0){
			p->setAndC(0);
			p->setOrC(0);
		}
		else{
			if(p->getFtype() == FType::AND){
				int max_and = 0;
				RecursiveFtype(p, max_and, FType::AND);
				//set ANDC
				p->setAndC(max_and+1);
			}
			else if(p->getFtype() == FType::OR){
				int max_or = 0;
				RecursiveFtype(p, max_or, FType::OR);
				//set ANDC
				p->setAndC(max_or+1);
			}
			else{
				p->setAndC(0);
				p->setOrC(0);
			}
			
		}
		//or count
		//std::cout<<p->getId()<<"->"<<p->getName()<<"("<<p->getStart()<<","<<p->getEnd()<<")"<<"\n";
	}
	
#ifdef bug
		std::cout<<"#node: "<<NODE_Ary.size()<<std::endl;
		for(auto p : NODE_Ary){
			std::cout<<"-------------------------------------------------------\n";
			std::cout<<"name: "<<p->getName()<<std::endl;
			std::cout<<"Gate type: "<<p->getFtype()<<std::endl;
			std::cout<<"Type: "<<p->getType()<<std::endl;
			std::cout<<"ID: "<<p->getId()<<std::endl;
			std::cout<<"And Count: "<<p->getAndC()<<std::endl;
			std::cout<<"Or Count: "<<p->getOrC()<<std::endl;

			std::cout<<"FI node : ";
			for(auto q :p->getFI()){
				std::cout<<q->getName()<<" ";
			}
			std::cout<<"\nFO node : ";
			for(auto q :p->getFO()){
				std::cout<<q->getName()<<" ";
			}
			std::cout<<"\n-------------------------------------------------------\n";
		}
		std::cout<<"area: "<<area<<std::endl;
	#endif
}

void encryption::RecursiveFtype(NODE* _node, int& max,FType _ft){
	for(auto p : _node->getFI()){
		if(p->getFtype() == _ft){
			switch(_ft)
			{
				case FType::OR :
					if(p->getOrC() > max)
						max = p->getOrC();
					break;
				case FType::AND :
					if(p->getAndC() > max)
						max = p->getAndC();
					break;
				default :
					break;
			}
		}
		else if(p->getFtype() == FType::BUF){
			this->RecursiveFtype(p, max, _ft);
		}
	}

}

void encryption::F_And_logic_cone(){
	
}
