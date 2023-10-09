#pragma once

#include "Graph.hxx"
#include <cinttypes>
#include <algorithm>


template<class TGraph>
class TestingGraph : public TGraph
{
public:
    static uint InitEdgesNumber(const uint &cols, const uint &rows) {
        return (cols-1)*2 * rows + (rows-1)*2 * cols;
    }
    static uint InitNodesNumber(const uint &cols, const uint &rows) {
        return cols * rows;
    }

    TestingGraph(const uint8_t &cols, const uint8_t &rows) :
        TGraph(cols, rows)
    {
        static_assert(std::is_base_of<AbstractGraph, TGraph>::value,
                      "Invalid Graph type given");
    }

    static bool TestTooFewNodes()
    {
        try {
            TestingGraph(1, 1);
            return false;
        } catch (std::out_of_range &) {
            return true;
        } catch (std::exception &) {
            return false;
        }
    }

    static bool TestCreation(const uint8_t &cols = 10,
                             const uint8_t &rows = 10)
    {
        TestingGraph g (cols, rows);

        const int startNodes = g.nodesNumber();
        const int startEdges = g.edgesNumber();
        return startNodes == InitNodesNumber(cols, rows) &&
               startEdges == InitEdgesNumber(cols, rows);
    }

    static bool TestRemoveDiagonal(const uint8_t &cols = 10,
                                   const uint8_t &rows = 10)
    {
        TestingGraph g (cols, rows);

        const int diagonalLength = std::min(cols, rows);

        int nodes = g.nodesNumber();
        int edges = g.edgesNumber();

        for (uint8_t x = 0; x < diagonalLength; ++x) {
            g.remove({x, x});
            --nodes;

            if (x == 0)
                edges -= 4;
            else if (x == diagonalLength - 1)
                edges -= std::max(cols, rows) > diagonalLength ? 6 : 4;
            else
                edges -= 8;
        }

        return nodes == g.nodesNumber() && edges == g.edgesNumber();
    }

    static bool TestRemoveNonExist(const uint8_t &cols = 10,
                                   const uint8_t &rows = 10)
    {
        TestingGraph g (cols, rows);

        g.remove({cols, rows});
        return g.nodesNumber() == InitNodesNumber(cols, rows) &&
               g.edgesNumber() == InitEdgesNumber(cols, rows);
    }


    static bool TestAddNeighbour(const uint8_t &cols = 10,
                                 const uint8_t &rows = 10)
    {
        if (std::max(cols, rows) == 255)
            throw std::out_of_range(
                "Cols/rows must not exceed 254 in this test");

        TestingGraph g (cols, rows);

        g.add({cols, 0});
        return g.nodesNumber() == (InitNodesNumber(cols, rows) + 1) &&
               g.edgesNumber() == (InitEdgesNumber(cols, rows) + 2);
    }

    static bool TestAddNonNeighbour(const uint8_t &cols = 10,
                                    const uint8_t &rows = 20)
    {
        if (std::max(cols, rows) == 255)
            throw std::out_of_range(
                "Cols/rows must not exceed 254 in this test");

        TestingGraph g (cols, rows);
        try {
            g.add({cols, rows});
            return false;
        } catch (std::out_of_range &) {
            return true;
        } catch (std::exception &) {
            return false;
        }
    }
};
