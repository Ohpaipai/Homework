#include<iostream>
#include<cstdlib>
#include<fstream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<string>
#include<sstream>
#include<map>

void printChords(int*, char**, int, int, std::fstream&);
int main(int argc, char* argv[]){
	/*check command line{{{*/
	if(argc !=3 ){
		std::cout<< "Usage: ./[exe] [input file] [output file]"<<std::endl;
		exit(1);
	}
	/*}}}*/
	std::string unprocessed_str;  //temporary string
	std::fstream input, output; //file in out
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
	/*number of pins{{{*/
	//first line is number of pins
	std::getline(input,unprocessed_str);
	std::stringstream ss;
	ss << unprocessed_str;
	int num_pins;
	ss >> num_pins;
	unprocessed_str.clear();
	ss.clear();
	/*}}}*/
	/*variable declaration{{{*/
	int *chords= new int[num_pins]();
	int **MIS  = new int*[num_pins]; //answer DP
	char **bt  = new char*[num_pins]; //backtrace data
	for(size_t i=0;i<num_pins;i++){
		MIS[i]  = new int[num_pins]();
		bt[i]  = new char[num_pins]();
	}
	/*}}}*/
	/* read file {{{*/
	unprocessed_str.clear();
	int d1, d2;
	for(size_t i=0;i<(num_pins/2);i++){
		std::getline(input,unprocessed_str);
		ss << unprocessed_str;
		ss >> d1;
		ss >> d2;
		chords[d1]=d2;
		chords[d2]=d1;
		ss.clear();
		unprocessed_str.clear();
	}
	//read over
	input.close();
	/*}}}*/
	/*MIS algorithm{{{*/
	for(int j=0;j<num_pins;j++){
		int k = chords[j];
		for(int i=j;i>=0;i--){
			if(i!=j){
				if( k == i){ //CASE 3
					MIS[i][j] = MIS[i+1][j-1]+1;
					bt[i][j] ='!'; //'↙'
				}
				else{
					if(k>=i && k<=j){ //CASE 2
						int d1 = MIS[i][j-1];
						int d2 = (MIS[i][k-1]+1+MIS[k+1][j-1]);
						if(d1 > d2 ){
							MIS[i][j] = d1 ;
							bt[i][j] ='#';//'←'
						}
						else{
							MIS[i][j] = d2;
							bt[i][j] ='@'; //'↑'
						}
					}
					else{ //CASE 1
						MIS[i][j]=MIS[i][j-1];
						bt[i][j] ='#'; //'←'
					}
				}
			}
			else{
				MIS[i][j] = 0;
			}
		}
	}
	output<<MIS[0][num_pins-1]<<"\n";
	//std::cout<<MIS[0][num_pins-1]<<"\n";
	/*}}}*/
	/* Debug {{{*/
/*				
	 	for(size_t i=0;i<num_pins;i++){
			for(size_t j=0;j<num_pins;j++){
				if(bt[i][j]==0){
					std::cout<<'-'<<" ";
				}
				else{
					if(bt[i][j] == '!')
						std::cout<<"↙"<<" ";
					else if(bt[i][j] == '@')
						std::cout<<"↑"<<" ";
					else
						std::cout<<"←"<<" ";
				}
			}
			std::cout<<std::endl;
		}
*/	
	/*}}}*/
	/*Back trace{{{*/
	printChords(chords, bt, 0, num_pins-1, output);
	/*}}}*/
	/*delete Varaible{{{*/
	for(size_t i=0;i<num_pins;i++){
		delete [] MIS[i];
		delete [] bt[i];
	}
	delete [] MIS;
	delete [] bt;
	delete [] chords;
	/*}}}*/
	/*close file{{{*/
	output.close();
	/*}}}*/
	return 0;
}

/*print chors to file -- recursive{{{*/
void printChords(int* Data, char** Trace, int i, int j, std::fstream& output){
	//debug
//	std::cout<<"("<<i<<","<<j<<")"<<" = "<<(char)Trace[i][j]<<std::endl;
	
	if(i==j||(i<0||j<0)||(i>j)) //in the end;
		return;
	else{
		if(Trace[i][j] == '!'){ //'↙'
			//std::cout<<Data[j]<<" "<<j<<std::endl;
			output<<Data[j]<<" "<<j<<std::endl;
			printChords(Data, Trace, i+1,j-1,output);
		}
		else if(Trace[i][j] == '#'){
			printChords(Data, Trace, i,j-1,output);
		}
		else{
			printChords(Data, Trace, i, Data[j]-1,output);
			//std::cout<<Data[j]<<" "<<j<<std::endl;
			output<<Data[j]<<" "<<j<<std::endl;
			printChords(Data, Trace, Data[j]+1, j-1,output);
		}
	}
	return;
}
/*}}}*/
