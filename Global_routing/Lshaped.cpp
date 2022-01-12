#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>

int main(int argc, char* argv[]){
/*define parameter{{{*/
int gridX = 0;
int gridY = 0;
std::string unprocessed_str;  //temporary string
std::fstream input, output; //file in out
std::stringstream ss;
int capacity = 0;
int num_net  = 0;
std::vector<std::vector<int>>netx;
std::vector<std::vector<int>>nety;
std::vector<int>ID;
//temporary
std::string temS = "";
int temC = 0;
int count = 0;
/*}}}*/
	/*check command line{{{*/
	if(argc !=3 ){
		std::cout<< "Usage: ./[exe] [input file] [output file]"<<std::endl;
		exit(1);
	}
	/*}}}*/
	/*openfile{{{*/
	input.open(argv[1], std::ios::in);
	output.open(argv[2], std::ios::out);
	/*}}}*/
	/*check isn't open correctly{{{*/
	if(!input.is_open()){
		std::cout<<"Error: the input file is not opened!!"<<std::endl;
		exit(1);
	}
	if(!output.is_open()){
		std::cout<<"Error: the output file is not opened!!"<<std::endl;
		exit(1);
	}
	/*}}}*/
	/*read file{{{*/
	while(!input.eof()){
		std::getline(input,unprocessed_str);
		//check isn't empty
		if(unprocessed_str.empty()){
			continue;
		}
		ss.clear();
		ss.str("");
		if(temC <3){	
			ss << unprocessed_str;
			ss >> temS;
			if(temS.size() == 4){// grid size
				ss >>gridX;
				ss >>gridY;
				unprocessed_str.clear();
				temC += 1;

			}
			else if(temS.size() == 8){// capacity
				ss >> capacity;
				unprocessed_str.clear();
				temC += 1;
			}
			else if(temS.size() == 3 ){ //# net
				ss >> temS;
				ss >> num_net;
				netx.resize(num_net);	
				nety.resize(num_net);	
				ID.resize(num_net);
				unprocessed_str.clear();
				temC += 1;
			}
		}
		else{
			int startx, starty, endx, endy , id;
			ss << unprocessed_str;
			ss>>ID[count]>>startx>>starty>>endx>>endy;
			//transform
			startx 	= gridX - startx;
			starty 	= gridY - starty;
			endx 	= gridX - endx;
			endy 	= gridY - endy;

			// for x
			if(startx < endx){
				for(int i=startx; i<=endx; i++){
					netx[count].push_back(i);
					nety[count].push_back(starty);
				}
			}
			else{
				for(int i=startx; i>=endx; i--){
					netx[count].push_back(i);
					nety[count].push_back(starty);
				}
			
			}
			
			// for y
			if(starty < endy){
				for(int i=starty; i<=endy; i++){
					netx[count].push_back(endx);
					nety[count].push_back(i);
				}
			}
			else{
				for(int i=starty; i>=endy; i--){
					netx[count].push_back(endx);
					nety[count].push_back(i);
				}
			
			}
			count++;
		}
	}
	/*}}}*/
	
	for(int i=0; i<num_net;i++){
		output << ID[i] <<" " <<netx[i].size()-1<<std::endl;
		for(int j=0; j<=netx.size()-2; j++){
			output<<(gridX - netx[i][j])<<" ";
			output<<(gridY - nety[i][j])<<" ";
			output<<(gridX - netx[i][j+1])<<" ";
			output<<(gridY - nety[i][j+1])<<std::endl;
		}
	}

}
