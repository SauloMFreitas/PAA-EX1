/**
 * Trabalho de PAA - EX. 1
 * @details arquivo biblioteca para definição de variáveis e métodos gerais para grafos
 * @authors:
 * @Bernardo46-2
 * @ToniLommez
 * @SauloMFreitas
*/

#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <set>
#include <list>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class graph
{
protected:
    int V;
    bool digraph;
    

public:
    // constructor
    graph(int size) : V(size), digraph(false){};
    graph(int size, bool isDigraph) : V(size), digraph(isDigraph){};
    virtual ~graph(){};

    // Vertex
    virtual bool hasVertex(int v) const = 0;
    virtual void addVertex(int quant) = 0;
    virtual bool removeVertex(int v) = 0;

    // Edge
    virtual bool viableEdge(int from, int to) const = 0;
    virtual bool hasEdge(int from, int to) = 0;
    virtual bool addEdge(int from, int to) = 0;
    virtual bool addEdge(int from, int to, int weight) = 0;
    virtual bool editEdge(int from, int to, int weight) = 0;
    virtual bool removeEdge(int from, int to) = 0;
    virtual void removeAllEdgesTo(int to) = 0;
    virtual void removeAllEdgesFrom(int from) = 0;

    // search algorithm

    virtual void BFS(int v) = 0;
    virtual void DFS(int v) = 0;

    // Find Cycles

    virtual bool permutationFindCycles() = 0;
    virtual bool searchAlgortihmFindCycles() = 0;


    // Debug
    virtual void print() const = 0;

};
#endif // GRAPH_HPP