#include "GraphTest.hxx"
#include <cstdint>
#include <vector>


int main()
{
    const uint8_t cols = 10, rows = 10;

    std::vector<bool> results{TestingGraph::TestTooFewNodes(),
                              TestingGraph::TestCreation(cols, rows),
                              TestingGraph::TestRemoveDiagonal(cols, rows),
                              TestingGraph::TestRemoveNonExist(cols, rows),
                              TestingGraph::TestAddNeighbour(cols, rows),
                              TestingGraph::TestAddNonNeighbour(cols, rows)};

    // set breakpoint here if something goes wrong
    if (std::all_of(results.begin(), results.end(),
                    [](bool i){return i;}))
        return 0;
    else
        return 1;
}
