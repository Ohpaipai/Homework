#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<bits/stdc++.h>
#include<algorithm>
#include<queue>
#include<math.h>
#include<iomanip>
#include<map>

/* Data structure {{{*/
class Node;

class Node{
	public :
		int x, y;
		double F;
		int step;
		int turn; 
		int k;
		Node *parent;
		Node(){
			x = 0;
			y = 0;
			F = -1;
			step = 0;
			turn =  0;
		}
		Node(int _x, int _y, double _F,int _s){
			//constructor
			x = _x;
			y = _y;
			F = _F;
			step = _s;
			turn =  0;
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
	std::vector<Node*>path;
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
Node *best;  //minheap's head
int last; //heap length
//temporary
std::string temS = "";
int temC = 0;
int count = 0;
int constraintx1 = 0;
int constrainty1 = 0;
int constraintx2 = 0;
int constrainty2 = 0;
/*}}}*/
/* min Heap operation{{{*/
void Swap(int x, int y){
	minheap[x]->k = y;
	minheap[y]->k = x;
	Node *tmp 	= minheap[x];
	minheap[x] 	= minheap[y];
	minheap[y]		= tmp;
}

void InsertNode(){
	
//	minheap[last]->k = last;
	int now  = last;
	int base = last >> 1; // derived 2
	while(base>0 && minheap[base]->F > minheap[now]->F){
		Swap(now, base);
		now = base;
		base >>= 1; //base = base derived 2
	}
}


void minheapFilterUp(int k){
	int parent;

	while(k!=1){ //k has a parent node
		parent = k >> 1;
		if(minheap[k]->F < minheap[parent]->F){
			Swap(k,parent);
			k = parent;
		}
		else
			break;
	}
}

void minheapFilterDown(int k){
	int child1, child2;
	while(2*k <= last){ 		//has any child node
		child1 = k<<1; 			//left child
		child2 = child1+1;		// right child
		
		if(child2 <= last){		//if true, k has 2 childs
			/* 
			 * Node k has 2 children nodes
             * Find the min. of 3 nodes 
             */
			if(minheap[k]->F< minheap[child1]->F && minheap[k]->F < minheap[child2]->F){
				/* Node k in correction*/
				break;
			}
			else{
				/*
				 * replace Node k with the smaller child node
				 */
				if(minheap[child1]->F < minheap[child2]->F){
					/*
					 * child1 is smaller, swap with k
					 */
					Swap(k,child1);
					k = child1;
				}
				else{
					Swap(k,child2);
					k = child2;
				}
			}
		}
		else{
			/* 
			 * Node k only has 1 children node
             */
			if(minheap[k]->F < minheap[child1]->F){
				/* Node k in correction*/
				break;
			}
			else{
					Swap(k,child1);
					k = child1;
			}
		}
	}
}

void UpdateNode(int k){
	int parent;
//	minheap[k] = minheap[last];
//	last--;
	parent = k>>1;
	if( k==1 || minheap[parent]->F < minheap[k]->F)
		minheapFilterDown(k);
	else
		minheapFilterUp(k);
}

int Find(Node *_n){
/*	int return_index = 0;
	for(int i=1;i<=last;i++){
		if((minheap[i]->x == _n->x) && (minheap[i]->y == _n->y))
			return i;
	}
	return return_index;
*/
	return _n->k;
}

void Pophead(){
	int now = 1;
	int derived = now << 1; //*2
	Swap(1, last--);
	minheap[last+1]->k=0;
	minheap[last+1]= NULL;
	UpdateNode(1);
	/*while(derived <= last){
		if (minheap[derived + 1]->F < minheap[derived]->F && derived < last) 
			derived++;
		if (minheap[now]->F <= minheap[derived]->F) 
			break;
		Swap(now, derived);
		now = derived ;
		derived <<= 1;
	}*/
}
/*}}}*/

/* Chebyshev distance -> H-function  */
int H(Node *_n, Node _e){
	return std::max( std::abs(_e.x - _n->x), std::abs(_e.y - _n->y) );
}

/* Manhatten method for Source to current node -> G-function */
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
	/*out of range*/
	if(_x < 0 || _x >= gridY || _y < 0 || _y >= gridX)
		return;
	if(!(_x>=constraintx1 && _x<=constraintx2) || !(_y>=constrainty1 && _y<=constrainty2))
		return;
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
	else if(_from == 3){
		demand = Grid[_x][_y].right+1; 
	}
	else{
		demand = 0;
	}
	double C = std::pow(2 , (double)((double)(demand+1)/(double)capacity)) - 1;
	
	int pseudoTurn;

	if(_x == routing_net[_cur].start.x && _y == routing_net[_cur].start.y){
		pseudoTurn = 0;
	}
	else{
		int p2px = std::abs(Map[best->x][best->y]->parent->x - Map[best->x][best->y]->x);
		int p2nx = std::abs(Map[best->x][best->y]->x - _x);
		
		if(p2px == p2nx)
			pseudoTurn = best->turn;
		else
			pseudoTurn = best->turn + 1;
	}


//	double pseudoF = (double)((double)H(Map[_x][_y] , routing_net[_cur].end)  + best->F + (double)G(Map[_x][_y], routing_net[_cur].start) + pseudoTurn )*C;
	//double pseudoF = (double)(best->F + (double)H(Map[_x][_y], routing_net[_cur].end)*0.5 + (double)pseudoTurn )*C;
	double pseudoF = best->F + (double)C;
	//double pseudoF = (double)(best->F + pseudoTurn )*C;



	if( (Map[_x][_y]->F > pseudoF && Map[_x][_y]->step == (Map[best->x][best->y]->step +1 )) || (Map[_x][_y]->step > (Map[best->x][best->y]->step+1)) || Map[_x][_y]->step == -1 ){
	//if( Map[_x][_y]->F > pseudoF || Map[_x][_y]->step == -1 ){
		Map[_x][_y]->step = Map[best->x][best->y]->step+1;
		Map[_x][_y]->parent =Map[best->x][best->y];
		Map[_x][_y]->turn = pseudoTurn;
		Map[_x][_y]->F = pseudoF;
		//update heap
		int value = Find(Map[_x][_y]);
		if(value==0){
			last++;
			minheap[last] = Map[_x][_y]; 
			//minheap[last]->k = last; 
			InsertNode();
		}
		else{
			UpdateNode(value);	
		}
	}
}
void Astar(int _cur){
	/* reset Map which store steps*/
	for(int i=constraintx1; i<=constraintx2;i++){
		for(int j=constrainty1; j<=constrainty2;j++){
			Map[i][j]->step 	= -1;
			Map[i][j]->F		=  0;
			Map[i][j]->parent	= NULL;
			Map[i][j]->turn		=  0;
			Map[i][j]->k        =  0;
		}
	}
	for(int i=0;i<=last;i++){
		minheap[i]=NULL;
	}
	last = 0;
	//Judge(routing_net[_cur].start.x, routing_net[_cur].start.y, -1, _cur);
	Map[routing_net[_cur].start.x][routing_net[_cur].start.y]->F = (double)(H(Map[routing_net[_cur].start.x][routing_net[_cur].start.y], routing_net[_cur].end) + G(Map[routing_net[_cur].start.x][routing_net[_cur].start.y], routing_net[_cur].start));
	Map[routing_net[_cur].start.x][routing_net[_cur].start.y]->step=0;
	Map[routing_net[_cur].start.x][routing_net[_cur].start.y]->parent = Map[routing_net[_cur].start.x][routing_net[_cur].start.y];
	last++;
	minheap[last] = Map[routing_net[_cur].start.x][routing_net[_cur].start.y];
	minheap[last]->k = last;
	InsertNode();


	while (last > 0){
		best = minheap[1];
		if(best->x == routing_net[_cur].end.x && best->y == routing_net[_cur].end.y)
			break;
		Pophead();

		Judge(best->x+1, best->y,0, _cur); //up
		Judge(best->x-1, best->y,1, _cur); //down
		Judge(best->x, best->y+1,2, _cur); //left
		Judge(best->x, best->y-1,3, _cur); //right
/*		for(int i=1; i<=last;i++){
			std::cout<<"("<<minheap[i]->x<<","<<minheap[i]->y<<") ";
		}
		std::cout<<std::endl;*/	
	}

	Node *t;
	t = Map[routing_net[_cur].end.x][routing_net[_cur].end.y];
	Node *pt;
	while(1){
		routing_net[_cur].path.push_back(t);
		pt =t;
		t = t->parent;
		if(pt->x - t->x ==1){
			Grid[pt->x][pt->y].up +=1;
			Grid[t->x][t->y].down +=1;
		}
		else if(pt->x - t->x ==-1){
			Grid[pt->x][pt->y].down +=1;
			Grid[t->x][t->y].up +=1;
		}
		else{
			if(pt->y - t->y ==1){
				Grid[t->x][t->y].right +=1;
				Grid[pt->x][pt->y].left  +=1;
			}
			else{
				Grid[pt->x][pt->y].right +=1;
				Grid[t->x][t->y].left  +=1;
			}
			
		}

		if(t->x == routing_net[_cur].start.x && t->y == routing_net[_cur].start.y){
			routing_net[_cur].path.push_back(t);
			break;
		}
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
				Grid.resize(gridY);
				Map.resize(gridY);
				minheap.resize(gridX*gridY);
				for(int i=0;i<gridY;i++){
					Grid[i].resize(gridX);
					Map[i].resize(gridX);
					for(int j=0;j<gridX;j++){
						Map[i][j] = new Node(i,j,0.0,-1);
						Map[i][j]->step 	= -1;
						Map[i][j]->F		=  0;
						Map[i][j]->parent	= NULL;
						Map[i][j]->turn		=  0;
						Map[i][j]->k        =  0;
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
			ss >> routing_net[count].start.y;
			ss >> routing_net[count].start.x;
			ss >> routing_net[count].end.y;
			ss >> routing_net[count].end.x;

//			std::cout<<"("<<routing_net[count].start.y<<" , "<<routing_net[count].start.x<<") , ";
//			std::cout<<"("<<routing_net[count].end.y<<" , "<<routing_net[count].end.x<<") --> ";
			//transform
			routing_net[count].start.x 	= (gridY-1) - routing_net[count].start.x; 
			//routing_net[count].start.y 	= (gridY-1) - routing_net[count].start.y;
			routing_net[count].end.x 	= (gridY-1) - routing_net[count].end.x;
			//routing_net[count].end.y 	= (gridY-1) - routing_net[count].end.y;

//			std::cout<<"("<<routing_net[count].start.x<<" , "<<routing_net[count].start.y<<") , ";
//			std::cout<<"("<<routing_net[count].end.x<<" , "<<routing_net[count].end.y<<")\n";
			count++;
		}
	}
	/*}}}*/
	/*sort net by HPWL*/
	std::sort(routing_net.begin(), routing_net.end(),cmpNet);
	/* A* algorithm */
	for(int i = 0; i < routing_net.size(); i++){
		if(routing_net[i].start.x < routing_net[i].end.x){
			constraintx1 = routing_net[i].start.x;
			constraintx2 = routing_net[i].end.x;
		}
		else{
			constraintx2 = routing_net[i].start.x;
			constraintx1 = routing_net[i].end.x;
		}
		if(routing_net[i].start.y < routing_net[i].end.y){
			constrainty1 = routing_net[i].start.y;
			constrainty2 = routing_net[i].end.y;
		}
		else{
			constrainty2 = routing_net[i].start.y;
			constrainty1 = routing_net[i].end.y;
		}
/*constraint routing range  {{{*/
		int c = 1;
		while(true){
			if((constraintx1 -c) >= 0){
				constraintx1 -=c;
				break;
			}
			else{
				c--;
				if(c == 0)
					break;
			}
		}
		c =1;
		while(true){
			if((constraintx2 +c) < gridY){
				constraintx2 +=c;
				break;
			}
			else{
				c--;
				if(c == 0)
					break;
			}
		}
		c = 1;
		while(true){
			if((constrainty1 - c) >= 0){
				constrainty1 -=c;
				break;
			}
			else{
				c--;
				if(c == 0)
					break;
			}
		}
		c = 1;
		while(true){
			if((constrainty2 + c) < gridX){
				constrainty2 +=c;
				break;
			}
			else{
				c--;
				if(c == 0)
					break;
			}
		}
	/*}}}*/
		//std::cout<<i<<std::endl;
		Astar(i);
	}
	for(int i=0; i< num_net;i++){
		output << routing_net[i].id<<" "<<routing_net[i].path.size()-1<<std::endl;
		for(int j=routing_net[i].path.size()-1;j>=1;j--){
		 	output << routing_net[i].path[j]->y<<" "<<(gridY -1 - routing_net[i].path[j]->x)<<" ";
		 	output << routing_net[i].path[j-1]->y<<" "<<(gridY -1 - routing_net[i].path[j-1]->x)<<std::endl;
		}
	}
}
