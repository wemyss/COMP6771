// test 1: tests graph construction and node insertion

#include "Graph.h"
#include <cassert>

int main() {
	gdwg::Graph<int,int> g;

    assert(g.addNode(1) == true);
    assert(g.addNode(1) == false);
    assert(g.addNode(2) == true);
    assert(g.addNode(3) == true);
    assert(g.addEdge(1,1,1) == true);
    assert(g.addEdge(1,1,1) == false);
    assert(g.addEdge(1,1,2) == true);
    assert(g.addEdge(1,2,2) == true);
    assert(g.addEdge(2,1,2) == true);

    std::cout << "Graph g nodes before copy:" << std::endl;
	g.printNodes();

    auto gCopy = g;

    std::cout << "Graph g nodes after copy:" << std::endl;
	g.printNodes();

    assert(gCopy.addEdge(3,1,3) == true);
    assert(gCopy.replace(2, 4) == true);
    assert(gCopy.replace(4, 4) == false);

    std::cout << "Graph g nodes after copy & modifcation:" << std::endl;
	g.printNodes();
    g.printEdges(1);
    g.printEdges(2);
    g.printEdges(3);
    std::cout << "isNode: " << g.isNode(4) << std::endl;

    std::cout << "Graph gCopy:" << std::endl;
	gCopy.printNodes();
    gCopy.printEdges(1);
    gCopy.printEdges(4);
    gCopy.printEdges(3);

    gdwg::Graph<double,double> gEmpty;

    for (gEmpty.begin(); !gEmpty.end(); gEmpty.next())
        std::cout << gEmpty.value() << std::endl;

    // auto v = std::vector<int>{};
    // auto it = v.cbegin();
    // std::cout << "HI" << std::endl;


}
