#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<bits/stdc++.h>
#include<algorithm>
#include<queue>
#include<math.h>

/* Data structure {{{*/
class Node{
	public :
		int x, y;
		double F;
		int step;
		Node(){
			x = 0;
			y = 0;
			F = -1;
			step = 0;
		}
		Node(int _x, int _y, double _F,int _s){
			//constructor
			x = _x;
			y = _y;
			F = _F;
			step = _s;
		}
		bool operator ==(Node* _n2){
			if( (x == _n2->x) && (y == _n2->y))
				return true;
			else
				return false;
		}
};


typedef struct Net{
	int id;
	Node start, end;
	std::vector<Node>path;
}Net;

bool cmpNet(const Net &n1, const Net &n2){
	int d1 = std::abs(n1.start.x - n1.end.x) + std::abs(n1.start.y - n1.end.y);
	int d2 = std::abs(n2.start.x - n2.end.x) + std::abs(n2.start.y - n2.end.y);
	return d1 < d2;
}

typedef struct Tile{
	int up;
	int left;
	int right;
	int down;
}Tile;

/*}}}*/
/*define parameter{{{*/
int gridX = 0;
int gridY = 0;
std::string unprocessed_str;  //temporary string
std::fstream input, output; //file in out
std::stringstream ss;
int capacity = 0;
int num_net  = 0;
std::vector<Net>routing_net;
std::vector<std::vector<Tile> >Grid;
std::vector<std::vector<Node*> >Map;	
std::vector<Node*>minheap;
Node best;  //minheap's head
int last;
//temporary
std::string temS = "";
int temC = 0;
int count = 0;
/*}}}*/

void Swap(int x, int y){
	Node *tmp 	= minheap[x];
	minheap[x] 	= minheap[y];
	minheap[y]		= tmp;
}

void InsertNode(){
	int now  = last;
	int base = last >> 1; // derived 2
	while(base>0 && minheap[base]->F > minheap[now]->F){
		Swap(now, base);
		now = base;
		base >>= 1; //base = base derived 2
	}
}

void DelNode(){
	int now = 1;
	int derived = now << 1; //*2
	Swap(1, last--);
	while(derived <= last){
		if (minheap[derived + 1]->F < minheap[derived]->F && derived < last) 
			derived++;
		if (minheap[now]->F <= minheap[derived]->F) 
			break;
		Swap(now, derived);
		now = derived ;
		derived <<= 1;
	}
}









/* Chebyshev distance */
int H(Node *_n, Node _e){
	return std::max( std::abs(_e.x - _n->x), std::abs(_e.y - _n->y) );
}

/* Manhatten method for Source to current node */
int G(Node *_n, Node _s){
	return std::abs(_n->x - _s.x) + std::abs(_n->y - _s.y);
}

/* judge function to update node cost and push in min heap
 * x and y means current node
 * from means from which direction to Node _n
 * 0->up, 1->down, 2->left, 3->right
 * _cur means current route index
*/
void Judge(int _x, int _y, short _from, int _cur){
	
	if(Map[_x][_y]->step > (Map[best.x][best.y]->step +1) || Map[_x][_y]->step == -1 ){
		int demand = 0;
		if( _from == 0){
			demand = Grid[_x][_y].up+1; 
		}
		else if(_from == 1){
			demand = Grid[_x][_y].down+1; 
		}
		else if(_from == 2){
			demand = Grid[_x][_y].left+1; 
		}
		else{
			demand = Grid[_x][_y].right+1; 
		}

		/*edge cost = 2^(demand/capacity)-1*/
		double C = std::pow(2 , (double)((double)demand/(double)capacity)) + 1;
		Map[_x][_y]->F = (double)(H(Map[_x][_y] , routing_net[_cur].end) + G(Map[_x][_y], routing_net[_cur].start))*C;
	}
}

void Astar(int _cur){
	/* reset Map which store steps*/
	for(int i=0;i<gridX;i++)
		for(int j=0;j<gridY;j++){
			Map[i][j]->step 	= -1;
			Map[i][j]->F		=  0;
		}
	
}


int main(int argc, char* argv[]){
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
				
				// set grid size and reset
				Grid.resize(gridX);
				Map.resize(gridX);
				for(int i=0;i<gridX;i++){
					Grid[i].resize(gridY);
					Map[i].resize(gridY);
					for(int j=0;j<gridY;j++){
						Map[i][j] = new Node(i,j,0.0,-1);
						Grid[i][j].up  		= 0;
						Grid[i][j].down		= 0;
						Grid[i][j].left 	= 0;
						Grid[i][j].right 	= 0;
					}
				}

			}
			else if(temS.size() == 8){// capacity
				ss >> capacity;
				unprocessed_str.clear();
				temC += 1;
			}
			else if(temS.size() == 3 ){ //# net
				ss >> temS;
				ss >> num_net;
				routing_net.resize(num_net); 
				unprocessed_str.clear();
				temC += 1;
			}
		}
		else{
			ss << unprocessed_str;
			ss >> routing_net[count].id;
			ss >> routing_net[count].start.x;
			ss >> routing_net[count].start.y;
			ss >> routing_net[count].end.x;
			ss >> routing_net[count].end.y;
			count++;
		}
	}
	/*}}}*/
	
	/*sort net by HPWL*/
	std::sort(routing_net.begin(), routing_net.end(),cmpNet);
	/* A* algorithm */


}
