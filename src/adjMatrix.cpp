/**
 * Trabalho de PAA - EX. 1
 * @details arquivo para desenvolvimento dos métodos para um grafo em matriz de adjacência
 * @authors:
 *   @Bernardo46-2
 *   @ToniLommez
 *   @SauloMFreitas
 */

#include "../include/adjMatrix.hpp"
using namespace std;

/*
 * ===========================================================================
 * =                               CONSTRUCTOR                               =
 * ===========================================================================
 */
/**
 * @brief Constructor
 * @param size - quantidade inicial de vértices do grafo
 */
adjMatrix::adjMatrix(int size) : graph(size) {
    adjmatrix.resize(size, vector<int>(size, 0));
}

/**
 * @brief Constructor
 * @param size - quantidade inicial de vértices do grafo
 * @param isDigraph - true se o grafo foi um grafo direcionado
 */
adjMatrix::adjMatrix(int size, bool isDigraph) : graph(size, isDigraph) {
    adjmatrix.resize(size, vector<int>(size, 0));
}

/*
 * ===========================================================================
 * =                                 GETTERs                                 =
 * ===========================================================================
 */

int adjMatrix::getopCountPermutation() {
    return this->opCountPermutation;
}

int adjMatrix::getopCountDFSv1() {
    return this->opCountDFSv1;
}

int adjMatrix::getopCountDFSv2() {
    return this->opCountDFSv2;
}

/*
 * ===========================================================================
 * =                                  VERTEX                                 =
 * ===========================================================================
 */

/**
 *  @brief Verifica a existência de um vértice no grafo
 *  @param v - vértice a ser verificado
 *  @return true se o vértice está no grafo
 */
bool adjMatrix::hasVertex(int v) const {
    return v < this->V;
}

/**
 *  @brief adiciona uma quantidade (quant) nova de vértices ao grafo
 *  @param quant - quantidade de vértices a ser adicionado ao grafo
 */
void adjMatrix::addVertex(int quant) {
    this->V += quant;
    adjmatrix.resize(this->V, vector<int>(this->V, 0));
}

/**
 *  @brief remove um vértice do grafo(não implementado)
 *  @param v - vértice a ser removido
 *  @return true se o vértice foi removido
 */
bool adjMatrix::removeVertex(int v) {
    return v < V;
}

/*
 * ===========================================================================
 * =                                   EDGE                                  =
 * ===========================================================================
 */

/**
 *  @brief verifica se uma aresta{from, to} pode ser adicionada
 *  @param from - vértice 1 a ser verificado
 *  @param to   - vértice 2 a ser verificado
 *  @return true se a aresta é viável a existir entre os 2 vértices
 */
bool adjMatrix::viableEdge(int from, int to) const {
    return hasVertex(from) && hasVertex(to) && adjmatrix[from][to] == 0;
}

/**
 *  @brief verifica a existência de uma aresta{from, to}
 *  @param from - vértice 1 a ser verificado
 *  @param to   - vértice 2 a ser verificado
 *  @return true se a aresta existe entre os 2 vértices
 */
bool adjMatrix::hasEdge(int from, int to) {
    return hasVertex(from) && hasVertex(to) && adjmatrix[from][to] != 0;
}

/**
 *  @brief adiciona uma aresta{from, to} de peso 1 entre 2 vértices
 *  @param from - vértice de conexão 1
 *  @param to   - vértice de conexão 2
 *  @return true se a aresta foi adicionada
 */
bool adjMatrix::addEdge(int from, int to) {
    return addEdge(from, to, 1);
}

/**
 *  @brief adiciona uma aresta{from, to} de peso w(weight) entre 2 vértices
 *  @param from   - vértice de conexão 1
 *  @param to     - vértice de conexão 2
 *  @param weight - peso da aresta a ser adicionada
 *  @return true se a aresta foi adicionada
 */
bool adjMatrix::addEdge(int from, int to, int weight) {
    bool success = false;
    if (viableEdge(from, to) && adjmatrix[from][to] == 0) {
        adjmatrix[from][to] = weight;
        if (!digraph) {
            adjmatrix[to][from] = weight;
        }

        success = true;
    }
    return success;
}

/**
 *  @brief edita o peso de uma aresta{from, to} já existente
 *  @param from - vértice 1 ligado a aresta
 *  @param to   - vértice 2 ligado a aresta
 *  @param weight - novo peso da aresta
 *  @return true se a aresta foi editada
 */
bool adjMatrix::editEdge(int from, int to, int weight) {
    bool success = false;
    if (hasEdge(from, to)) {
        adjmatrix[from][to] = weight;
        if (!digraph) {
            adjmatrix[to][from] = weight;
        }

        success = true;
    }
    return success;
}

/**
 *  @brief remove uma aresta{from, to} do grafo(muda o valor para 0)
 *  @param from - vértice 1 em que a aresta está ligada
 *  @param to   - vértice 2 em que a aresta está ligada
 *  @return true se a aresta foi removida
 */
bool adjMatrix::removeEdge(int from, int to) {
    bool success = false;
    if (hasEdge(from, to)) {
        adjmatrix[from][to] = 0;
        if (!digraph) {
            adjmatrix[to][from] = 0;
        }

        success = true;
    }
    return success;
}

/**
 *  @brief remove todas as arestas de entrada de um vértice{to}
 *  @param to - vértice a ter suas arestas de entrada removidas
 */
void adjMatrix::removeAllEdgesTo(int to) {
    if (digraph) {
        for (int i = 0; i < V; i++) {
            adjmatrix[i][to] = 0;
        }
    }
}

/**
 *  @brief remove todas as arestas de saída de um vértice{to}
 *  @param to - vértice a ter suas saída de entrada removidas
 */
void adjMatrix::removeAllEdgesFrom(int from) {
    if (digraph) {
        for (int i = 0; i < V; i++) {
            adjmatrix[from][i] = 0;
        }
    }
}

/*
 * ===========================================================================
 * =                          SEARCH ALGORITHMS                              =
 * ===========================================================================
 */

// ---------------------------- PRIVATE AUXILIARY METHODS ----------------------------

/**
 *  @brief método recursivo para realizar a DFS
 *  @param v        - vértice a ser caminhado
 *  @param visitado - lista de vértices já visitados - true no espaço x do vector se o vértice x já foi visitado
 */
void adjMatrix::DFSUtil(int v, vector<bool> &visitado) {
    visitado[v] = true;
    // cout << v << " ";

    for (int i = 0; i < V; ++i) {
        if (adjmatrix[v][i] && !visitado[i]) {
            DFSUtil(i, visitado);
        }
    }
}
// ------------------------------------------------------------ PUBLIC METHODS

/**
 *  @brief algoritmo de busca em profundidade a partir do vértice v
 *  @param v - vértice de partida para a busca em profundidade
 */
void adjMatrix::DFS(int v) {
    vector<bool> visitado(V, false);
    DFSUtil(v, visitado);
}

/**
 *  @brief método interativo para o algoritmo de busca em largura
 *  @param v - vértice de partida para a busca em largura
 */
void adjMatrix::BFS(int v) {
    vector<bool> visitado(V, false);
    list<int> fila;

    visitado[v] = true;
    fila.push_back(v);

    while (!fila.empty()) {
        v = fila.front();
        // cout << v << " ";
        fila.pop_front();

        for (int i = 0; i < V; ++i) {
            if (adjmatrix[v][i] && !visitado[i]) {
                visitado[i] = true;
                fila.push_back(i);
            }
        }
    }
}

/*
 * ===========================================================================
 * =                               FIND CYCLES                               =
 * ===========================================================================
 */

// ---------------------------- PRIVATE AUXILIARY METHODS ----------------------------

// ------------------------ AUXILIARY PERMUTATION METHODS

/**
 *  @brief verifica a existência de um ciclo a partir de uma lista de vértices
 *  @param perm - lista de vértices para teste
 *  @return true se a lista entregue é um ciclo(na sequencia da lista)
 */
bool adjMatrix::isCycle(const vector<int> &perm) {
    for (size_t i = 0; i < perm.size(); ++i) {
        int next = (i + 1) % perm.size(); // Circular
        if (!hasEdge(perm[i], perm[next]))
            return false;
    }
    return true;
}

/**
 *  @brief método auxiliar recursivo para gerar todas as permutações de subconjuntos de tamanho r do conjunto s
 *  @param s       - conjunto de vértices
 *  @param r       - tamanho desejado para o subconjunto
 *  @param subset  - subconjunto a ser construido durante a recursão
 *  @param index   - O índice atual no conjunto s para considerar o próximo elemento
 *  @param subsets - Uma lista para armazenar todos os subconjuntos gerados
 */
void adjMatrix::findSubsets(vector<int> &s, int r, vector<int> &subset, int index, vector<vector<int>> &subsets) {
    if (subset.size() == r) {
        subsets.push_back(subset);
        return;
    }
    for (int i = index; i < s.size(); i++) {
        subset.push_back(s[i]);
        opCountPermutation++; // conta operações com vértices no algoritmo de permutação
        findSubsets(s, r, subset, i + 1, subsets);
        subset.pop_back();
    }
}

// ------------------------ AUXILIARY SEARCH ALGORITHM METHODS

/**
 *  @brief método recursivo de busca em profundidade adaptado para localizar um ciclo em um grafo
 *  @param v      - O vértice atual na DFS.
 *  @param start  - O vértice de início do ciclo potencial.
 *  @param parent - O vértice pai do vértice atual na árvore de DFS, usado para prevenir
 *                  a volta imediata para o vértice pai.
 *  @param found  - true se pelo menos 1 ciclo foi encontrado
 */
void adjMatrix::dfs(int v, int start, int parent, bool &found) {
    visited[v] = true;
    path.push_back(v);
    opCountDFSv1++; // Incrementa por adicionar um vértice ao path

    for (int next = 0; next < V; ++next) {
        if (adjmatrix[v][next] == 1) { // Verifica a existência de uma aresta
            if (next == start && path.size() > 2) {
                found = true;
                ++cicleCount;
                // cout << "ciclo " << ++cicleCount << ": ";
                // // Encontramos um ciclo, imprima ou salve o ciclo
                // for(const int& vertex : path) cout << vertex << " ";
                // cout << start << endl; // Completa o ciclo
                continue;
            }
            if (!visited[next] && next != parent) {
                dfs(next, start, v, found);
            }
        }
    }

    path.pop_back();
    opCountDFSv1++; // Incrementa por remover um vértice do path
    visited[v] = false;
}

/**
 *  @brief método recursivo de busca em profundidade adaptado para localizar ciclos em um grafo
 *         modificado para filtrar ciclos repetidos e mostrar apenas os ciclos unicos.
 *         Objetivo: testar eficiencia da modificação
 *  @param v      - O vértice atual na DFS.
 *  @param start  - O vértice de início do ciclo potencial.
 *  @param parent - O vértice pai do vértice atual na árvore de DFS, usado para prevenir
 *                  a volta imediata para o vértice pai.
 *  @param found  - true se pelo menos 1 ciclo foi encontrado
 */
void adjMatrix::dfsv2(int v, int start, int parent, bool &found) {
    visited[v] = true;
    path.push_back(v);
    opCountDFSv2++; // Incrementa por adicionar um vértice ao path

    for (int next = 0; next < V; ++next) {
        if (adjmatrix[v][next] == 1) { // Verifica a existência de uma aresta
            if (next == start && path.size() > 2) {
                found = true;
                if (isUniqueCycle(path)) {
                    ++cicleCount;
                    // cout << "ciclo " << ++cicleCount << ": ";
                    // // Encontramos um ciclo, imprima ou salve o ciclo
                    // for(const int& vertex : path) cout << vertex << " ";
                    // cout << start << endl; // Completa o ciclo
                }
                continue;
            }
            if (!visited[next] && next != parent) {
                dfsv2(next, start, v, found);
            }
        }
    }

    path.pop_back();
    opCountDFSv2++; // Incrementa por remover um vértice do path
    visited[v] = false;
}

bool adjMatrix::isUniqueCycle(vector<int> path) {
    int n = path.size();
    vector<int> normalizedCycle = path, reversedCycle = path;
    opCountDFSv2 += 2 * n; // Conta a cópia de elementos para normalizedCycle e reversedCycle

    // Inverte o ciclo para comparação
    reverse(reversedCycle.begin(), reversedCycle.end());
    // reverse não aumenta opCountDFSv2 pois não há movimentação real de elementos

    // Rotaciona ambos os ciclos para que comecem com o menor vértice
    rotate(normalizedCycle.begin(), min_element(normalizedCycle.begin(), normalizedCycle.end()), normalizedCycle.end());
    opCountDFSv2 += n; // Conta a movimentação de elementos em normalizedCycle
    rotate(reversedCycle.begin(), min_element(reversedCycle.begin(), reversedCycle.end()), reversedCycle.end());
    opCountDFSv2 += n; // Conta a movimentação de elementos em reversedCycle

    // Escolhe o menor lexicograficamente entre o ciclo normalizado e o inverso
    if (reversedCycle < normalizedCycle) {
        normalizedCycle = reversedCycle;
        opCountDFSv2 += n; // Conta a cópia de elementos de reversedCycle para normalizedCycle
    }

    // Constrói a string do ciclo normalizado para verificar a unicidade
    string cycleStr;
    for (int v : normalizedCycle) {
        cycleStr += to_string(v) + " ";
    }

    // Verifica se o ciclo já foi encontrado antes
    if (uniqueCycles.find(cycleStr) == uniqueCycles.end()) {
        uniqueCycles.insert(cycleStr);
        return true; // Ciclo é único
    }
    return false; // Ciclo repetido
}

// ---------------------------------- PUBLIC METHODS ----------------------------------

/**
 *  @brief método para encontrar e imprimir todos os ciclos em um grafo não direcionado por permutação, testa cada possibilidade permutada de vértices e verifica se essa permutação é um ciclo
 *  @return true se existe pelo menos 1 ciclo
 */
bool adjMatrix::permutationFindCycles() {
    opCountPermutation = 0;
    int quantity = 0;
    bool found = false;
    vector<int> nodes(V);
    for (int i = 0; i < V; i++)
        nodes[i] = i; // Inicializando nós

    // Gera todas as permutações possíveis para cada tamanho de subconjunto
    for (int r = 3; r <= V; r++) { // Cada ciclo precisa de pelo menos 3 vértices
        vector<vector<int>> subsets;
        vector<int> subset;
        findSubsets(nodes, r, subset, 0, subsets);

        for (auto &s : subsets) {
            do {
                if (isCycle(s)) {
                    quantity++;
                    // cout << "ciclo " << quantity << ": ";
                    // for (int n : s)
                    //     cout << n << " ";
                    // cout << s[0];
                    // cout << endl;
                    found = true;
                }
            } while (next_permutation(s.begin(), s.end()));
        }
    }
    return found;
}

/**
 *  @brief método para encontrar todos os ciclos em um grafo não direcionado por caminhamento, usando DFS(Depth First Search)
 *  @return true se pelo menos um ciclo foi encontrado
 */
bool adjMatrix::searchAlgortihmFindCycles() {
    opCountDFSv1 = 0;
    bool found = false;
    cicleCount = 0;
    for (int i = 0; i < V; i++) {
        visited.resize(V, false);
        path.clear();
        dfs(i, i, -1, found); // Começa a DFS de cada vértice
    }
    return found;
}

/**
 *  @brief método para encontrar todos os ciclos em um grafo não direcionado por caminhamento, usando DFS(Depth First Search)
 *  @return true se pelo menos um ciclo foi encontrado
 */
bool adjMatrix::searchAlgortihmFindCyclesv2() {
    opCountDFSv2 = 0;
    bool found = false;
    cicleCount = 0;
    for (int i = 0; i < V; i++) {
        visited.resize(V, false);
        path.clear();
        dfsv2(i, i, -1, found); // Começa a DFS de cada vértice
    }
    return found;
}

/*
 * ===========================================================================
 * =                                   DEBUG                                 =
 * ===========================================================================
 */

/**
 *  @brief imprime o grafo em formato de matriz de adjacência
 */
void adjMatrix::print() const {
    cout << "  ";
    for (int i = 0; i < V; i++) {
        cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < V; i++) {
        cout << i << " ";
        for (int j = 0; j < V; j++) {
            cout << adjmatrix[i][j] << " ";
        }
        cout << endl;
    }
}