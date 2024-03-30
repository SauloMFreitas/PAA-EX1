#include "../include/graphGenerator.hpp"

void graphGenerator::generateAndPrintGraphs(int numberOfGraphs, const string& fileName, const bool useRand) {
    ofstream outFile(fileName);
    if (!outFile) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return;
    }

    // Inicializa a semente do gerador de números aleatórios
    srand(static_cast<unsigned int>(time(nullptr)));

    outFile << numberOfGraphs << endl;

    int prevNumVertices = 2; // Começa com um grafo de tamanho mínimo de 2 vértices
    int prevNumEdges = 1; // Começa com pelo menos uma aresta

    for (int g = 1; g <= numberOfGraphs; g++) {
        // Garante que cada novo grafo tem mais vértices e arestas que o anterior
        int numVertices;
        int numEdges;

        if (useRand) {
            numVertices = prevNumVertices + (rand() % 3 + 1); // Incrementa de 1 a 3 vértices
            numEdges = prevNumEdges + (rand() % 3 + 1) + (numVertices - prevNumVertices); // Garante mais arestas que o anterior
        } else {
            numVertices = prevNumVertices + 1; // Incrementa de 1 a 3 vértices
            numEdges = prevNumEdges + 1 + (numVertices - prevNumVertices); // Garante mais arestas que o anterior
        }

        prevNumVertices = numVertices;
        prevNumEdges = numEdges;

        outFile << numVertices << endl;
        outFile << numEdges << endl;

        // Gerando arestas de forma a conectar os vértices de maneira simples
        for (int e = 0; e < numEdges && e < numVertices; e++) {
            outFile << e << " " << (e + 1) % numVertices << endl;
        }

        // Adicionando arestas extras de forma aleatória para atingir o numEdges
        for (int e = numVertices; e < numEdges; e++) {
            int v1 = rand() % numVertices;
            int v2 = rand() % numVertices;
            outFile << v1 << " " << v2 << endl;
        }
    }

    outFile.close();
    cout << "Grafos gerados e impressos em " << fileName << endl;
}
