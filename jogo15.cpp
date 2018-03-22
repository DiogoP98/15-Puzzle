/*
 * IA work_1
 * Description: search algorithm for finding solutions for 15 puzzle game
 * Author: Afonso, Diogo, Lucas
 */

#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <queue>
#include <functional>
#include <unistd.h>
#include "sys/types.h"
//#include "sys/sysinfo.h"

using namespace std;

/****class****/
class Node;

/****algorithms****/
bool bfs();
bool ldfs(int k);
bool idfs();
bool greedy_Manhattan();
bool greedy_misplaced();
bool A_star_Manhattan();
bool A_star_misplaced();

/****input****/
void read();

/****output****/
string print(Node *a);

/****aux****/
bool   hassolution();
int    checkinv(int v[]);
int    myswap(int x);
int    Manhattan (Node *x);
int    misplaced (Node *x);
void   creat_dicf(); //for better performance in heuristics
string myhash(int v[]);
bool   eq(int a[],int b[]);
bool   nodeEq(Node *a, Node *b);
void   cp(int a[],int b[]);

/****print memory****/
int parseLine(char* line);
int getValue();

/****global var****/
//to go up,down,left,tight
pair<int,int> tr[] = {make_pair(-1, 0),
					  make_pair( 1, 0),
					  make_pair( 0, 1),
					  make_pair( 0,-1)};
//to create start and final nodes when necessary
int ar_i[16],z_i[2],ar_f[16],z_f[2];
vector<int> finalpos(16);
map<string,int> setx;

int main(){
	//input
	read();
	creat_dicf();
	
	//check if there is solution
	if(!hassolution()){
		printf("No solution!\n");
		return 0;
	}
	
	//Search for solution
	int start_s=clock();
	printf("Searching..\n");
	
	
	//Choose one of the following to alternate between algorithms: 
	// bool ok = ldfs(15);
	// bool ok = bfs();
	// bool ok = idfs();
	// bool ok = greedy_misplaced();
	// bool ok = greedy_Manhattan();
	// bool ok = A_star_misplaced();
	// bool ok = A_star_Manhattan();	
	bool ok = A_star_Manhattan();
	
	if(!ok){
		//if no solution found
		printf("No solution\n");
	}
	else{
		// found a solution
		int stop_s=clock();
		cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
		printf("memory: %dKB\n",getValue());
		
	}
	return 0;
}

/****Class****/
class Node{
	
	public:
	int array[16]; //configuration
	int zero[2];   //position of zero {i, j}
	int depth;     //depth
	string path;   //stores path in form of a string ready to be printed
	
	//descontructor
	~Node(){
		
	}
	
	//constructor
	Node(int array[],int zero[], int depth, string path){
		cp(array,this->array);
		this->zero[0]=zero[0];
		this->zero[1]=zero[1];
		this->depth = depth;
		if(depth == 0){
			this->path = print(this);
		}
		else{
			this->path = path + print(this);
		}
	}
	
	//make the descendents	
	vector<Node*> make_desc(){
		int i,j;
		
		vector<Node*> l;
		for(int k=0;k<4;k++){
			int c[16],t[2];
			//tr is in the begin of the code, used for going, up,down,left or rigth
			i=this->zero[0]+tr[k].first;
			j=this->zero[1]+tr[k].second;
			if(i>=0 && i<4 && j>=0 && j<4){
				
				cp(this->array,c);
				c[this->zero[0]*4+this->zero[1]]=c[i*4+j];
				
				c[i*4+j]=0;
				t[0]=i;
				t[1]=j;
				
				//check if note already seen, if not seen add
				//if seen but depth is smaller than previous, add also
				if(setx.find(myhash(c))==setx.end()){
					Node *tt = new Node(c,t,this->depth+1,this->path);
					l.push_back(tt);
				}
				else if(setx[myhash(c)]>this->depth+1){
					setx[myhash(c)]=this->depth+1;
					Node *tt = new Node(c,t,this->depth+1,this->path);
					l.push_back(tt);
				}
			}
		}
		return l;
	}
};

/****Algorithms****/
//Depth first search limited by k
bool ldfs(int k){
	//initialize nodes start and end
	Node *end = new Node(ar_f,z_f,0,"");
	Node *start = new Node(ar_i,z_i,0,"");
	vector<Node*> l;
	vector<Node*>  tt;
	l.push_back(start);
	Node *t;
	int flag;
	while(l.size()>0){
		flag=0;
		t = l.back();
		l.pop_back();
		//check if current node was already visited
		if(setx.find(myhash(t->array))==setx.end())
			setx.insert(make_pair(myhash(t->array),t->depth));
		//if was visited but is a better solution
		else if(setx[myhash(t->array)]>=t->depth){
			setx[myhash(t->array)]=t->depth;
		}
		//if was already visited and its not optimal node
		else{
			flag=1;
		}
		//check if found objective
		if(nodeEq(t,end)){
			cout << t->path;
			printf("Depth: %d\n",t->depth);
			return true;
		}
		if(t->depth<k && !flag){
			tt = t->make_desc();
			for(int i=0;i<(int)tt.size();i++){
				l.push_back(tt[i]);
			}
		}
		delete t;
	}
	return false;
}

//Breath first search
bool bfs(){
	//initialize nodes start and end
	Node *end = new Node(ar_f,z_f,0,"");
	Node *start = new Node(ar_i,z_i,0,"");
	queue<Node*> l;
	vector<Node*>  tt;
	l.push(start);
	Node *t;
	int flag;
	while(l.size()>0){
		flag = 0;
		t = l.front();
		l.pop();
		//check if current node was already visited
		if(setx.find(myhash(t->array))==setx.end())
			setx.insert(make_pair(myhash(t->array),t->depth));
		//if was visited but is a better solution
		else if(setx[myhash(t->array)]>=t->depth){
			setx[myhash(t->array)]=t->depth;
		}
		//if was already visited and its not optimal node
		else{
			flag=1;
		}
		//check if found objective
		if(nodeEq(t,end)){
			cout << t->path;
			printf("Depth: %d\n",t->depth);
			return true;
		}
		if(t->depth<80 && !flag){
			tt = t->make_desc();			
			for(int i=0;i<(int)tt.size();i++){
				l.push(tt[i]);
			}
		}
		delete t;
	}
	return false;
}

//Iterative Depth first search
bool idfs(){
	//use ldfs, iterating on the limit
	for(int i=0;i<80;i++){
		if(ldfs(i)){
			return true;
		}
		setx.clear();
	}
	return false;
}

struct f{
	bool operator()(const pair<int,Node*>& a, pair<int,Node*>& b){
		return a.first>b.first;
	}
};

//greedy with manhattan heuristics
bool greedy_Manhattan(){
	//initialize nodes start and end
	Node *end = new Node(ar_f,z_f,0,"");
	Node *start = new Node(ar_i,z_i,0,"");
	priority_queue< pair<int,Node*>, vector <pair<int,Node*> > , f > pq;
	pq.push (make_pair(0,start));
	Node *current_node;
	int flag;
	while (!pq.empty()) {
		flag = 0;
		current_node = pq.top().second;
		pq.pop();
		//check if current node was already visited
		if(setx.find(myhash(current_node->array))==setx.end())
			setx.insert(make_pair(myhash(current_node->array),current_node->depth));
		//if was visited but is a better solution
		if(setx[myhash(current_node->array)]>=current_node->depth){
			setx[myhash(current_node->array)]=current_node->depth;
		}
		//if was already visited and its not optimal node
		else{
			flag=1;
		}
		//check if found objective
		if(nodeEq(current_node,end)){
			cout << current_node->path;
			printf("Depth: %d\n",current_node->depth);
			return true;
		}
		if(!flag){
			vector<Node*> dsc = current_node->make_desc();
			for (int i=0; i<(int)dsc.size();i++) {
				pq.push(make_pair(Manhattan(dsc[i]),dsc[i]));
			}
		}
		delete current_node;
	}
	return false;
}

//greedy with misplace tiles heuristics
bool greedy_misplaced(){
	//initialize nodes start and end
	Node *end = new Node(ar_f,z_f,0,"");
	Node *start = new Node(ar_i,z_i,0,"");
	priority_queue< pair<int,Node*>, vector <pair<int,Node*> > , f > pq;
	pq.push (make_pair(0,start));
	Node *current_node;
	int flag;
	while (!pq.empty()) {
		flag = 0;
		current_node = pq.top().second;
		pq.pop();
		//check if current node was already visited
		if(setx.find(myhash(current_node->array))==setx.end())
			setx.insert(make_pair(myhash(current_node->array),current_node->depth));
		//if was visited but is a better solution
		if(setx[myhash(current_node->array)]>=current_node->depth){
			setx[myhash(current_node->array)]=current_node->depth;
		}
		//if was already visited and its not optimal node
		else{
			flag=1;
		}
		//check if found objective
		if(nodeEq(current_node,end)){
			cout << current_node->path;
			printf("Depth: %d\n",current_node->depth);
			return true;
		}
		if(!flag){
			vector<Node*> dsc = current_node->make_desc();
			for (int i=0; i<(int)dsc.size();i++) {
				pq.push(make_pair(misplaced(dsc[i]),dsc[i]));
			}
		}
		delete current_node;
	}
	return false;
}

//greedy with manhattan heuristics
bool A_star_Manhattan () {
	//initialize nodes start and end
	Node *end = new Node(ar_f,z_f,0,"");
	Node *start = new Node(ar_i,z_i,0,"");
	//start->cost = 0;
	priority_queue< pair<int,Node*>, vector <pair<int,Node*> > , f > pq;
	pq.push (make_pair(0,start));
	Node *current_node;
	int flag;
	while (!pq.empty()) {
		flag = 0;
		current_node = pq.top().second;
		pq.pop();
		//check if current node was already visited
		if(setx.find(myhash(current_node->array))==setx.end())
			setx.insert(make_pair(myhash(current_node->array),current_node->depth));
		//if was visited but is a better solution
		if(setx[myhash(current_node->array)]>=current_node->depth){
			setx[myhash(current_node->array)]=current_node->depth;
		}
		//if was already visited and its not optimal node
		else{
			flag=1;
		}
		//check if found objective
		if(nodeEq(current_node,end)){
			cout << current_node->path;
			printf("Depth: %d\n",current_node->depth);
			return true;
		}
		if(!flag){
			vector<Node*> dsc = current_node->make_desc();
			for (int i=0; i<(int)dsc.size();i++) {
				pq.push(make_pair(Manhattan(dsc[i])*1.1+dsc[i]->depth,dsc[i]));
			}
		}
		delete current_node;
	}
	return false;
}

//greedy with misplace tiles heuristics
bool A_star_misplaced () {
	//initialize nodes start and end
	Node *end = new Node(ar_f,z_f,0,"");
	Node *start = new Node(ar_i,z_i,0,"");
	priority_queue< pair<int,Node*>, vector <pair<int,Node*> > , f > pq;
	pq.push (make_pair(0,start));
	Node *current_node;
	int flag;
	while (!pq.empty()) {
		flag = 0;
		current_node = pq.top().second;
		pq.pop();
		//check if current node was already visited
		if(setx.find(myhash(current_node->array))==setx.end())
			setx.insert(make_pair(myhash(current_node->array),current_node->depth));
		//if was visited but is a better solution
		if(setx[myhash(current_node->array)]>=current_node->depth){
			setx[myhash(current_node->array)]=current_node->depth;
		}
		//if was already visited and its not optimal node
		else{
			flag=1;
		}
		//check if found objective
		if(nodeEq(current_node,end)){
			cout << current_node->path;
			printf("Depth: %d\n",current_node->depth);
			return true;
		}
		if(!flag){
			vector<Node*> dsc = current_node->make_desc();
			for (int i=0; i<(int)dsc.size();i++) {
				pq.push(make_pair(misplaced(dsc[i])*3+misplaced(current_node)*1+dsc[i]->depth,dsc[i]));
			}
		}
		delete current_node;
	}
	return false;
}

/****input****/
//read input and place the values in the global variables
void read(){
	int x;
	printf("conf ini:\n");
	for(int i=0;i<16;i++){
		scanf("%d",&x);
		if(!x){
			z_i[0]=i/4;
			z_i[1]=i%4;
		}
		ar_i[i]=x;
	}
	printf("conf fin:\n");
	for(int i=0;i<16;i++){
		scanf("%d",&x);
		if(!x){
			z_f[0]=i/4;
			z_f[1]=i%4;
		}
		ar_f[i]=x;
	}
}

/****output****/
//return pretty string with the configuration
string print(Node *a){
	if(a==NULL){
		printf("No node\n");
		return "";
	}
	char s[1000];s[0]='\0';
	for(int i=0;i<16;i++){
		sprintf(s,"%s %2d ",s,a->array[i]);
		if(((i+1)%4)==0)
			sprintf(s,"%s\n",s);
	}
	sprintf(s,"%s\n",s);
	return string(s);
}

/****aux****/
//verify if configuration is solvable
bool hassolution(){
	Node *end = new Node(ar_f,z_f,0,"");
	Node *start = new Node(ar_i,z_i,0,"");
	int inv_i,inv_f,br_i,br_f;
	inv_i = checkinv(start->array);
	inv_f = checkinv(end->array);
	br_i  = myswap(start->zero[0]);
	br_f  = myswap(end->zero[0]);
	if (((inv_i % 2 == 0) == (br_i % 2 == 1)) == ((inv_f % 2 == 0) == (br_f % 2 == 1)))
		return true;
	return false; 
}

//count number of inversions
int checkinv(int v[]){
	int sum=0;
	for(int i=0;i<16;i++){
		for(int j=i+1;j<16;j++){
			if(v[i]>v[j] && v[i]!=0 && v[j]!=0)
				sum+=1;
		}
	}
	return sum;
}

//change x as it was counted from bottom starting at 1, for checking solvability
int myswap(int x){
	switch(x){
		case 3:return 1;
		case 2:return 2;
		case 1:return 3;
		case 0:return 4;
	}
	//because warning
	return 0;
}

//calculation of manhattan distance heuristic
int Manhattan (Node *x) {
  int acc = 0;
  for (int i=0; i<16; i++) {
    if (x->array[i]!=0) {
      int index= finalpos[x->array[i]];
      int xf = index/4;
      int yf = index%4;
      int xa = i/4;
      int ya = i%4;
      acc+= abs(xf-xa) + abs(yf-ya);
    }
  }
  return acc;
}

//calculation of misplaced tiles heuristic
int misplaced (Node *x) {
  int acc=0;
  for (int i=0;i<16;i++) {
    if (x->array[i]!=0) {
      int index = finalpos[x->array[i]];
      if (index!=i)
	acc++;
    }
  }
  return acc;
}

//for better performance calculating the euristics, creats a sort of dictionary
//for given a tile k, the index is finalpos[k]
void creat_dicf() {
  for (int i=0; i<16;i++) {
    int g = ar_f[i];
    finalpos[g]=i;
  }
}

//return the array as a string
string myhash(int v[]){
	string s = "";
	for(int  i =0;i<16;i++)
		s+=to_string(v[i]);
	return s;
}

//check if 2 arrays of configurations are equal
bool eq(int a[], int b[]){
	for(int i=0;i<16;i++)
		if(a[i]!=b[i]) return false;
	return true;
}

//check if 2 nodes are equals
bool nodeEq(Node *a, Node *b){
	if(a && b)return eq(a->array,b->array);
	return false;
}

//copy array a to b
void cp(int a[], int b[]){
	for(int i=0;i<16;i++){
		b[i]=a[i];
	}
}

/****print memory****/
//the 2 function below are taken from here:https://stackoverflow.com/a/64166 ,to see memory usage
int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}
 
int getValue(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

