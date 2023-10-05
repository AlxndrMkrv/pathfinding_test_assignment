#include "Graph.hxx"
#include <cinttypes>


uint initEdgesNumber(const uint &cols, const uint &rows)
{
    return (cols-1)*2 * rows + (rows-1)*2 * cols;
}


uint initNodesNumber(const uint &cols, const uint &rows)
{
    return cols * rows;
}


int main()
{
    const uint8_t cols = 10, rows = 10;

    DFS g (cols, rows);
    int startVertices = g.nodesNumber();
    int startEdges = g.edgesNumber();

    for (uint8_t x : {2, 5, 7})
        g.remove({x, x}); // remove 1 node and 8 edges (x3)

    g.remove({0, 0}); // remove 1 node and 4 edges
    g.remove({cols-1, rows/2}); // remove 1 node and 6 edges

    int endVertices = g.nodesNumber();
    int endEdges = g.edgesNumber();

    bool success = (startVertices == initNodesNumber(cols, rows)) &&
                   (endVertices == (startVertices - 5)) &&
                   (startEdges == initEdgesNumber(cols, rows)) &&
                   (endEdges == startEdges - (8*3 + 4 + 6));
    return ! success;
}
