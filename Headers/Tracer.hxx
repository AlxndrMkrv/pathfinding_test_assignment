#pragma once

#include "CellContainers.hxx"

class AbstractTracer {
public:
    explicit AbstractTracer(const EdgeContainer & edges);
    Route findRoute(const Cell & start, const Cell & end) const;
    virtual const char * name() const = 0;

protected:
    inline size_t nodesNumber() const noexcept { return _edges.size(); }
    virtual Route implementation(const Cell & start,
                                 const Cell & end) const = 0;

protected:
    const EdgeContainer & _edges;
};

/* ************************************************************************** *
 *                              Deep-first search                             */

class DFS : public AbstractTracer {
public:
    using AbstractTracer::AbstractTracer;
    virtual const char * name() const override { return "DFS"; }

protected:
    virtual Route implementation(const Cell & start,
                                 const Cell & end) const override;

private:
    void trace(Route & path, CellSet & visited, const Cell & end) const;
};

/* ************************************************************************** *
 *                            Beadth-first search                            */

class BFS : public AbstractTracer {

public:
    using AbstractTracer::AbstractTracer;
    virtual const char * name() const override { return "BFS"; }

protected:
    virtual Route implementation(const Cell & start,
                                 const Cell & end) const override;
};
