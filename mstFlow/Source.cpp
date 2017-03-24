/*
	Name        : Eranus Thompson
	Description : Given a gaph that has a complete set of pipes (edges) that connect
			      all junctions (vertices), the program uses minimum spanning tree, 
				  find, or union to pick the pipes (edges) which most closely have the 
				  same capacity to be replaced. The input (read from a keyboard) consists 
				  of multiple datasets followed by a line containing two zeros separated
				  by a space (which indicates the end of the input datasets). The junctions
				  (vertices) >= 2 and the pipes (edges) <= 0 && >= ( vertices(vertices - 1)/2).
				  For a complete set of pipes that connect all junctions, the program outputs
				  the set with the smallest range of capacities. Otherwise, it outputs -1.				  
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct mstEdge {

	int src;
	int dest;
	int weight;

	mstEdge(int v = 0, int e = 0, int w = 0) {

		src = v;
		dest = e;
		weight = w;
	}

	//int mstEdge[];

	bool operator < (const mstEdge& rhs) {
		return weight < rhs.weight;
	}
	
	//sort(edgeSet.begin(), edgeSet.end())
	
};

//struct orderWeight {
//
//	bool operator () (const mstEdge& ver1, const mstEdge& ver2) {
//		return (ver1.weight < ver2.weight);
//	}
//
//	//sort(edgeSet.begin(), edgeSet.end(), orderWeight());
//	
//
//	
//};

struct makeSubSet {
	
	int parent;
	int index;
};

class mstGraph {

public:

	void createGraph(int numVer, int numEdge) { //creates an undirected mstGraph
		
		int ver1, ver2, wght, count = 0;
		
		while (!eofDataSet(numVer, numEdge)) { //while data isn't 0, 0
			edgeVec.resize(numEdge);

			for (int i = 0; i < numEdge; i++) {
				cin >> ver1 >> ver2 >> wght;
				edgeVec[i].src = ver1;
				edgeVec[i].dest = ver2;
				edgeVec[i].weight = wght;
				//count++;
				//FIXME
			}
			sortEdge(edgeVec);
			//cin >> numVer >> numEdge;
						
		}
	}

	void sortEdge(vector<mstEdge> edgeSet) {	//sort edges in non-decreasing order

		sort(edgeSet.begin(), edgeSet.end());
	}
	
	//does union of on two sets of vertices
	//uses union by rank
	void unionSet(mstEdge parent[], int junc1, int junc2) {
		
		int vert1 = findSet(parent, junc1);
		int vert2 = findSet(parent, junc2);
		parent[junc1] = junc2;
	}

	//finds set of an element i
	int findSet(makeSubSet subSet[], int indx) {

		//finds and makes the root as parent of indx
		//if root != index 
		if (subSet[indx].parent != indx)
			subSet[indx].parent = findSet(subSet, subSet[indx].parent);
		return subSet[indx].parent;
	}

	int kruskMST(int numVer, int numEdge, mstEdge edgeSet) {
		
		groupSet.resize(0);
		for (int i = 0; i < numVer; i++) {
			groupSet[i].parent = i;
			groupSet[i].index = -1;
		}

		while (numEdge < numVer - 1) {

			int x = findSet(groupSet, edgeSet.src);
			int y = findSet(groupSet, edgeSet.dest);
		}
	};

	bool eofDataSet(int node, int pipe) {
		if (node == 0 && pipe == 0)
			return true;
		return false;
	}
	
private:
	vector <mstEdge> edgeVec;
	vector <makeSubSet> groupSet;
};

int main() {

	mstGraph graph;
	mstEdge edge;
	int numVer, numEdge;

	cin >> numVer >> numEdge;
	graph.createGraph(numVer, numEdge);

	return 0;
}

