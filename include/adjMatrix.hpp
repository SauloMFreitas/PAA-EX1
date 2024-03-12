/**
 * Trabalho de PAA - EX. 1
 * @details arquivo biblioteca para definição variáveis e métodos
 * @authors:
 * @Bernardo46-2
 * @ToniLommez
 * @SauloMFreitas
*/

#ifndef GRAPH_MATRIX_HPP
#define GRAPH_MATRIX_HPP

#include "graph.hpp"
class adjMatrix : public graph
{
private:
    vector<vector<int>> adjmatrix;

    // --- variáveis para o método de localização de ciclos com caminhamento ---
    vector<bool> visited;
    vector<int> path;
    set<string> uniqueCycles;
    int ia;

    // --- variáveis para contar operações ---
    int opCountPermutation;
    int opCountDFSv1;
    int opCountDFSv2;

    // --- PERMUTATION PRIVATE METHODS ---
    bool isCycle(const vector<int>& perm);
    void findSubsets(vector<int>& s, int r, vector<int>& subset, int index, vector<vector<int>>& subsets);

    // --- SEARCH ALGORITHMS PRIVATE METHOD --- 
    void DFSUtil(int v, vector<bool>& visitado);

    // --- SEARCH ALGORITHMS TO FIND CYCLES PRIVATE METHODS --- 
    void dfs(int v, int start, int parent, bool &found);
    void dfsv2(int v, int start, int parent, bool &found);
    bool isUniqueCycle(vector<int> path);

public:
    
    // constructor
    adjMatrix(int size);
    adjMatrix(int size, bool isDigraph);

    // getters
    int getopCountPermutation();
    int getopCountDFSv1();
    int getopCountDFSv2();

    // Vertex
    bool hasVertex(int v) const override;
    void addVertex(int quant) override;
    bool removeVertex(int v) override;

    // Edge
    bool viableEdge(int from, int to) const override;
    bool hasEdge(int from, int to) override;
    bool addEdge(int from, int to) override;
    bool addEdge(int from, int to, int weight) override;
    bool editEdge(int from, int to, int weight) override;
    bool removeEdge(int from, int to) override;
    void removeAllEdgesTo(int to) override;
    void removeAllEdgesFrom(int from) override;    
    
    // Find Cycles
    bool permutationFindCycles() override;
    bool searchAlgortihmFindCycles()override;
    bool searchAlgortihmFindCyclesv2()override;

    //search algorithm
    void BFS(int v) override;
    void DFS(int v) override;

    // Debug
    void print() const override;
};
#endif // GRAPH_MATRIX_HPP