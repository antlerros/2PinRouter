//Algorithm Programming Assignment HW#3
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "parser.h"

using namespace std;

typedef pair< pair<int, int>,pair<int, int> > NetPos;


class Edge
{
public:
	Edge(int i, int c = 1): eNo(i), capacity(c) { demand = 0; }
	const double getCost() { return (double)(demand + 1)/capacity; }
	void setDemand() { demand += 1; }
	double getDmd() { return demand; } 
	double getCap() { return capacity; }
private:
	int eNo;
	int capacity;
	int demand;
};


class Tile
{
public:
	Tile() { pre = -1; counts = 0; }
	Tile(const int i, const pair<int, int> p): tNo(i), posi(p) { pre = -1; counts = 0; done = false; }
	void setDone() { done = true; }
	void setLength(const double& l) { length = l; }
	void setEdge(const int& v, const int& e) { conn.push_back(make_pair(v, e)); }
	void setPre(const int& p) { pre = p; }
	void setCount(const int& c) { counts = c + 1; }
	void Relax(vector<Edge>& edges, vector<Tile>& grids, vector<Tile>& temp);
	// bool cmp(Tile t1){
	// 	int c1 = posi.first + posi.second;
	// 	int c2 = t1.posi.first + t1.posi.second;
	// 	if(abs(c1 - c2) != 1)
	// 		return false;
	// 	return true;
	// }

	const int gettNo() { return tNo; }
	const int getPre() { return pre; }
	const int getCount() { return counts; }
	void printPos(ofstream& ouput) { ouput << posi.first << " " << posi.second; }
	const double getLength() const { return length; }
	const bool isDone() { return done; }
private:
	int tNo;
	pair<int, int> posi;
	double length;
	int counts;
	int pre;
	bool done;
	vector< pair<int, int> > conn;
};

bool compare(const Tile& t1, const Tile& t2) { return t1.getLength() > t2.getLength(); }

void Tile::Relax(vector<Edge>& edges, vector<Tile>& grids, vector<Tile>& temp){
	int i , j;
	bool dup;
	for(i = 0; i < conn.size(); ++i){
		if(grids[conn[i].first].isDone())
			continue;
		if(double(grids[conn[i].first].getLength()) <= double(length + edges[conn[i].second].getCost()))
			continue;
		grids[conn[i].first].setLength(double(length + edges[conn[i].second].getCost()));
		grids[conn[i].first].setPre(tNo);
		grids[conn[i].first].setCount(counts);
		edges[conn[i].second].setDemand();
		dup = false;
		for(j = 0; j < temp.size(); ++j){
			if(temp[j].gettNo() == conn[i].first){
				dup = true;
				break;
			}
		}
		if(dup)
			temp.erase(temp.begin() + j);
		temp.push_back(grids[conn[i].first]); 
		make_heap(temp.begin(), temp.end(), compare);
	}
}


void Initialization(vector<Tile>& grids, const int& source){
	for(int i = 0; i < grids.size(); ++i)
		grids[i].setLength(grids.size());
	grids[source].setLength(0);
	grids[source].setCount(-1);
}

void Dijkstra(vector<Tile> vs, vector<Edge>& es, const int& str, const int& end, const int& pNo, ofstream& op){
	Initialization(vs, end);
	vector<Tile> temp; 
	temp.push_back(vs[end]);
	Tile u;
	while(temp.size()){	
		pop_heap(temp.begin(), temp.end(), compare);
		u = temp.back();
		temp.pop_back();
 		if(u.gettNo() == str) 
			break;
		u.Relax(es, vs, temp);
		vs[u.gettNo()].setDone();
	}
	op << pNo << " " << u.getCount() << endl;
	while(u.getPre() != -1 && u.gettNo() != end){
		u.printPos(op);
		op << " ";
		u = vs[u.getPre()];
		u.printPos(op);
		op << endl;
	}
}
	// int cnt = 0;
	// int total = u.getCount();
		// if(!u.cmp(vs[u.getPre()]) && u.gettNo() != end){
		// 	cerr << "pairNo = " << pNo << endl;
		// 	cerr << u.gettNo() << " pre = " << u.getPre() << endl;
		// 	getchar();
		// }
		// if(u.getPre() == -1 && (u.gettNo() != end)){
		// 	cerr << "pairNo = " << pNo << endl;
		// 	cerr << "end = " << end << endl;
		// 	cerr << "stop = " << u.gettNo() << endl;
		// 	getchar();
		// }
		// ++cnt;
	// if(cnt != total){
	// 	cerr << "pairNo = " << pNo << endl;
	// 	cerr << "end = " << end << endl;
	// 	cerr << "stop = " << u.gettNo() << endl;
	// 	cerr << "cnt = " << cnt << " total = " << total << endl;
	// 	getchar();
	// }



int main(int argc, char** argv){
	AlgParser parser;
	AlgTimer timer;

	if(!parser.read(argv[1])) return 0;
	ofstream outfile(argv[2]);

	int idx = 0, temp;
	int htiles = parser.gNumHTiles();
	int vtiles = parser.gNumVTiles();
	int cap = parser.gCapacity();
	vector<Tile> vertice;
	vector<Edge> Edges;


	for(int i = 0; i < htiles; ++i){
		for(int j = 0; j < vtiles; ++j)
			vertice.push_back(Tile(idx++, make_pair(j, i)));
	}
	idx = 0;
	for(int i = 0; i < htiles; ++i){
		for(int j = 0; j < vtiles - 1; ++j){
			Edges.push_back(Edge(idx, cap));
			temp = (vtiles * i) + j;
			vertice[temp].setEdge(temp + 1, idx);
			vertice[temp + 1].setEdge(temp, idx++);
		}
	}
	for(int i = 0; i < htiles - 1; ++i){
		for(int j = 0; j < vtiles; ++j){
			Edges.push_back(Edge(idx, cap));
			temp = (vtiles * i) + j;
			vertice[temp].setEdge(temp + vtiles, idx);
			vertice[temp + vtiles].setEdge(temp, idx++);
		}
	}
	int str, end;
	for(int i = 0; i < parser.gNumNets(); ++i){
		str = (parser.gNetStart(i).second * htiles) + parser.gNetStart(i).first;
		end = (parser.gNetEnd(i).second * htiles) + parser.gNetEnd(i).first;
		Dijkstra(vertice, Edges, str, end, i, outfile);
    }
	return 0;
}

