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
#include <string>

using namespace std;

struct mstEdge {

	int src;
	int dest;
	int weight;
	//int mstEdge[];
};

class mstGraph {

public:

	void createGraph(mstGraph strData, int numVer, int numEdge) { //creates an undirected mstGraph
		int ver1, ver2, wght, count = 0;
		cin >> numVer >> numEdge;

		while (!eofDataSet(numVer, numEdge)) {
			
			for (int i = 1; i <= numEdge; i++) {
				cin >> ver1 >> ver2 >> wght;
				edgeArr[i].src = ver1;
				edgeArr[i].dest = ver2;
				edgeArr[i].weight = wght;
				
				//count++;
				//FIXME
			}
		}
	}

	bool isCycle();
	
private:
	mstEdge edgeArr[];
};



bool eofDataSet(int node, int pipe) {
	if (node == 0 && pipe == 0)
		return false;
	return true;
}


int main() {

	return 0;
}

