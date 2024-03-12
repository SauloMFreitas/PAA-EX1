/**
 * Trabalho de PAA - EX. 1
 * @details arquivo principal (apenas a função main nesse arquivo)
 * @authors:
 * @Bernardo46-2
 * @ToniLommez
 * @SauloMFreitas
*/
#include "include/graphs.hpp"

int main()
{

    // --- inicialização de variáveis ---
    graph *g = new adjMatrix(5);
    int numGraphs = 0;
    int numVertex = 0;
    int numEdges  = 0;
    int vertexEdge1 = 0;
    int vertexEdge2 = 0;
    // ----------------------------------

    // --- abrir e inicializar arquivo para guardar tempos de operação ---
    ofstream outFile(opTimeCSV);
        if (!outFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
        return 1;
    }

    outFile << "GraphNumber,VertexNumber,EdgeNumber,PermutationTime(us),DFSTimev1(us),DFSTimev2(us)"<<endl;
    // -------------------------------------------------------------------

    // --- abrir e inicializar arquivo para guardar tempos de operação ---

        ofstream outFile2(opCountCSV);
        if (!outFile2.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
        return 1;
    }

    outFile2 << "GraphNumber,VertexNumber,EdgeNumber,PermutationOpCount,DFSv1OpCount,DFSv2OpCount"<<endl;
    // -------------------------------------------------------------------

    cout << "quantos grafos devem ser gerados para teste?: ";
    cin >> numGraphs;
    cout << endl;
    
    // --- gerar *numGraphs* grafos para teste e guardar ---
    graphGenerator::generateAndPrintGraphs(numGraphs, graphTXT);

    // --- abrir arquivo com os grafos escritos ---
    ifstream inFile(graphTXT);
    
    if (!inFile) {
        cerr << "Erro ao abrir o arquivo." << endl;
    }
    inFile >> numGraphs;

    for (int i = 0; i < numGraphs; i++) // cria *numGraphs* grafos e busca por TODOS os ciclos
    {

        cout << "Grafo " << i+1 << endl;

        inFile >> numVertex;


        g = new adjMatrix(numVertex);

        inFile >> numEdges;
        
        for (int j = 0; j < numEdges; j++)
        {
            inFile >> vertexEdge1;
            inFile >> vertexEdge2;
            g->addEdge(vertexEdge1, vertexEdge2);
        }

        cout << "busca de ciclos por permutação" << endl;

        auto inicio_Permutation = high_resolution_clock::now();
        
        if (!g->permutationFindCycles())
        {
            cout << " Nenhum ciclo encontrado" << endl;
        }
        
        auto fim_Permutation = high_resolution_clock::now();

        auto duracao_Permutation = duration_cast<microseconds>(fim_Permutation - inicio_Permutation);


        cout << "busca de ciclos por caminhamento DFS sem filtro de ciclos repetidos" << endl;


        auto inicio_DFSv1 = high_resolution_clock::now();

        if (!g->searchAlgortihmFindCycles())
        {
            cout << " Nenhum ciclo encontrado" << endl;
        }
        
        auto fim_DFSv1 = high_resolution_clock::now();

        auto duracao_DFSv1 = duration_cast<microseconds>(fim_DFSv1 - inicio_DFSv1);


        cout << "busca de ciclos por caminhamento DFS com filtro de ciclos repetidos" << endl;
        

        auto inicio_DFSv2 = high_resolution_clock::now();

        if (!g->searchAlgortihmFindCyclesv2())
        {
            cout << " Nenhum ciclo encontrado" << endl;
        }
        
        auto fim_DFSv2 = high_resolution_clock::now();

        auto duracao_DFSv2 = duration_cast<microseconds>(fim_DFSv2 - inicio_DFSv2);


        outFile  << i+1 << numVertex << "," << numEdges << "," << duracao_Permutation.count() << "," << duracao_DFSv1.count() << "," << duracao_DFSv2.count();
        outFile2 << i+1 << numVertex << "," << numEdges << "," << g->getopCountPermutation()  << "," << g->getopCountDFSv1()  << "," << g->getopCountDFSv2() << endl;
    }
    outFile.close();

    

    
    return 0;
}
