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

const int maxWeightCap = 10000;

struct mstEdge {

	int src;
	int dest;
	int weight;

	mstEdge(int v = 0, int e = 0, int w = 0) {

		src = v;
		dest = e;
		weight = w;
	}

	bool operator < (const mstEdge& rhs) {
		return weight < rhs.weight;
	}	
};

struct makeSubSet {
	
	int index;
	int parent;	
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
			}
			sort(edgeVec.begin(), edgeVec.end());	//O(elogE)
			/*if (numEdge < numVer)
				strMinWeight.push_back(-1);
			else */
				kruskMST(numVer, numEdge);	
			cin >> numVer >> numEdge;						
		}
		printMinWeight();
	}

	//does union of on two sets of vertices
	//uses union by rank
	void unionSet(vector<makeSubSet>& subSet, int junc1, int junc2) {
		
		//make the smaller subtree the child of the 
		//largest subtree
		if (subSet[junc1].parent < subSet[junc2].parent)
			subSet[junc2].parent = junc1;
		else if (subSet[junc1].parent > subSet[junc2].parent)
			subSet[junc2].parent = junc1;
		//if both parents are same, make one as root
		//and decrement it's index by one
		else 
			subSet[junc2].parent = junc1;
	}

	//finds set of an element i
	//determines which set an item with key indx is in
	int findSet(vector<makeSubSet>& subSet, int indx) {

		//finds and makes the root as parent of indx
		//if root != index 
		if (subSet[indx].parent > 0) {	//subSet[indx].parent != indx-->prev
			subSet[indx].parent = findSet(subSet, subSet[indx].parent);
			return subSet[indx].parent;
		}
		return subSet[indx].index;
	}

	void kruskMST(int numVer, int numEdge) {
		
		int count = 0, minWeight, minCap = INT_MAX;
		int minWRange, maxWRange, numPar = 0;
		bool isCycle, inComplete;
		groupSet.resize(numVer+1);
				
		for (int i = 0; i < numEdge-2 /*- i*/; i++) {	//FIXME--> TRY i < numEdge - 2
			initializeSubSet(numVer);
			minWRange = INT_MAX, maxWRange = 0;
			isCycle = false, inComplete;
			count = i;
			
			while(count < (numVer - 1) + i) {
			//while (numEdge - i >= numVer - 1){
				int x = findSet(groupSet, edgeVec[count].src);
				int y = findSet(groupSet, edgeVec[count].dest);

				if (x != y) {
					unionSet(groupSet, x, y);
					findMinMax(minWRange, maxWRange, count);
				}
				else
					isCycle = true;
				count++;
			}

			if(!isCycle)
				minWeight = findMinWeight(minWRange, maxWRange, minCap);

			inComplete = isComplete(groupSet, numPar);
		}
		if (!inComplete)
			strMinWeight.push_back(minWeight);
		else
			strMinWeight.push_back(-1);
	};

	void initializeSubSet(int numVer) {

		for (int i = 1; i <= numVer; i++) {
			groupSet[i].index = i;
			groupSet[i].parent = -1;
		}
	}

	void findMinMax(int& minRange, int& maxRange, int count) {
				
		if (edgeVec[count].weight < minRange)
			minRange = edgeVec[count].weight;
		if (edgeVec[count].weight > maxRange)
			maxRange = edgeVec[count].weight;		
	}
	
	int findMinWeight(int minRange, int maxRange, int& minCap) {
		
		if ((maxRange - minRange < minCap) && (maxRange - minRange) <= maxWeightCap)
			minCap = maxRange - minRange;
		return minCap;
	}

	bool isComplete(vector<makeSubSet> subSets, int numPar) {
		
		for (int i = 1; i < subSets.size(); i++) 
			if (subSets[i].parent < 0) 
				numPar++;
		if(numPar > 1)
			return true;
		return false;
	}

	bool eofDataSet(int node, int pipe) {
		if (node == 0 && pipe == 0)
			return true;
		return false;
	}

	void printMinWeight() {
		for (int i = 0; i < strMinWeight.size(); i++)
			cout << strMinWeight[i] << endl;
	}
	
private:
	vector <mstEdge> edgeVec;
	vector <makeSubSet> groupSet;
	vector <int> strMinWeight;
};

int main() {

	mstGraph graph;
	mstEdge edge;
	int numVer, numEdge;

	cin >> numVer >> numEdge;
	graph.createGraph(numVer, numEdge);
	//graph.printMinWeight();

	return 0;
}