#include "Graph.h"

int main() {
    const auto graph = new Graph<int>();
    graph->addVertex(0);
    graph->addVertex(1);
    graph->addVertex(2);
    graph->addVertex(3);
    graph->addVertex(4);
    graph->addVertex(5);

    graph->createEdge(0, 1, 1);
    graph->createEdge(0, 2, 1);
    graph->createEdge(1, 4, 1);
    graph->createEdge(2, 3, 1);
    graph->createEdge(4, 5, 1);
    graph->createEdge(3, 5, 1);

    for (int i=0;i<7;i++) {
        graph->dijkstra(i);
    }
    return 0;
}
