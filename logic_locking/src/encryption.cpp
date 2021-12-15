#include "./inc/encryption.h"

encryption::encryption(){
}

encryption::~encryption(){
	for(auto p : NODE_Ary ){
		delete p;
	}
	NODE_Ary.clear();
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
			NODE *n = new NODE(t, ft, name);
			
			if(n == NULL)
				std::cout<<"error\n";
		
		// 	std::cout<<n->getName()<<" "<<n->getCost()<<std::endl;
			
			n->setPathlen(0); //if pathlen equal to -1 mean is output
			n->setId(coun++); //set ID	
			//push in
			NODE_Ary.push_back(n);
			PI_Ary.push_back(n);


			//make find graph
			name2node[name] = n;

		}
		else if(checkerflag == "OU"){
			std::string name = "";
			name.assign(buffer, 7, buffer.size()-8);
			

			Type	t  = Type::PO;
			FType	ft = FType::BUF;
			NODE *n =new NODE(t, ft, name);
			
			n->setPathlen(-1); //if pathlen equal to -1 mean is output
			n->setId(coun++); //set ID	
			
			//push in
			NODE_Ary.push_back(n);
			PO_Ary.push_back(n);	
			//make find graph
			name2node[name] = n;
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
			NODE* n =new NODE(t, ft, name);
			n->setId(coun++); //set ID	
			NODE_Ary.push_back(n);
			name2node[name] = n; 

			//first node push
			if(tem_buf[0] == '(')
				tem_buf.erase(tem_buf.begin());
			if(tem_buf[tem_buf.size()-1] == ',')
				tem_buf.pop_back();
			if(tem_buf[tem_buf.size()-1] == ')')
				tem_buf.pop_back();
		
			std::cout<<"insert node ( "<<name<<" ) = ";
			std::cout<<tem_buf<<" ";
				
			NODE *tem_n = name2node[tem_buf];
			//fan out
			tem_n->insertFO(n);
			//fan in
			n->insertFI(tem_n);

			while(ss >> tem_buf){
				if(tem_buf[0] == '(')
					tem_buf.erase(tem_buf.begin());
				if(tem_buf[tem_buf.size()-1] == ',')
					tem_buf.pop_back();
				if(tem_buf[tem_buf.size()-1] == ')')
					tem_buf.pop_back();
			
				std::cout<<tem_buf<<" ";
				tem_n = name2node[tem_buf];
				//fan ou
				tem_n->insertFO(n);
				//fan in
				n->insertFI(tem_n);
			}

			std::cout<<std::endl;
		}
		buffer.clear();
	}
	input.close();

	//caculate area
	this->caculateArea();
}


void encryption::caculateArea(){
	area = 0; //reset
	for(auto p : NODE_Ary){
		area += p->getCost();  
	}
}


void encryption::topological_sort(){

}
