/**
 * Trabalho de PAA - EX. 1
 * @details arquivo principal (apenas a função main nesse arquivo)
 * @authors:
 * @Bernardo46-2
 * @ToniLommez
 * @SauloMFreitas
 */
#include "include/graphs.hpp"
using namespace std;
using namespace chrono;

#include <cstdlib>  // Para std::system
void updateProgressBar(int current, int total);

// A verbosidade foi 'comentada' devido ao custo computacional do mesmo, 
// para nao interferir na contagem de tempo das operações reais
int main() {
    // Limpeza da tela
    #ifdef _WIN32
    std::system("cls");
    #else
        std::system("clear");
    #endif

    // --- inicialização de variáveis ---
    graph *g = new adjMatrix(5);
    int numGraphs = 0;
    int numVertex = 0;
    int numEdges = 0;
    int vertexEdge1 = 0;
    int vertexEdge2 = 0;
    int algoritmo = 0;
    // ----------------------------------

    // --- abrir e inicializar arquivo para guardar tempos de operação ---
    ofstream outFile(opTimeCSV);
    if (!outFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
        return 1;
    }

    outFile << "GraphNumber,VertexNumber,EdgeNumber,PermutationTime(us),DFSTimev1(us),DFSTimev2(us)" << endl;
    // -------------------------------------------------------------------

    // --- abrir e inicializar arquivo para guardar tempos de operação ---

    ofstream outFile2(opCountCSV);
    if (!outFile2.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
        return 1;
    }

    outFile2 << "GraphNumber,VertexNumber,EdgeNumber,PermutationOpCount,DFSv1OpCount,DFSv2OpCount" << endl;
    // -------------------------------------------------------------------

    std::cout << "==========================================================\n";
    std::cout << "Escolha quais algoritmos voce deseja rodar\n";
    std::cout << "1 - Permutacao\n";
    std::cout << "2 - Caminhamento\n";
    std::cout << "3 - Ambos\n";
    std::cout << "> ";
    cin >> algoritmo;
    std::cout << endl;

    std::cout << "Qual o numero de grafos que deve ser gerado para teste?\n";
    std::cout << "Considere um crescimento linear. Por exemplo, 3 significa:\n";
    std::cout << "- 5 vertices\n";
    std::cout << "- 4 vertices\n";
    std::cout << "- 3 vertices\n";
    std::cout << "> ";
    cin >> numGraphs;
    std::cout << endl;

    

    // --- gerar *numGraphs* grafos para teste e guardar ---
    std::cout << "Gerando grafos...\n";
    graphGenerator::generateAndPrintGraphs(numGraphs, graphTXT, false);
    std::cout << "==========================================================\n";

    // --- abrir arquivo com os grafos escritos ---
    ifstream inFile(graphTXT);

    if (!inFile) {
        cerr << "Erro ao abrir o arquivo." << endl;
    }
    inFile >> numGraphs;

    std::cout << "Iniciando busca de ciclos nos grafos...\n";
    for (int i = 0; i < numGraphs; i++) // cria *numGraphs* grafos e busca por TODOS os ciclos
    {

        // cout << "Grafo " << i+1 << endl;

        inFile >> numVertex;

        g = new adjMatrix(numVertex);

        inFile >> numEdges;

        for (int j = 0; j < numEdges; j++) {
            inFile >> vertexEdge1;
            inFile >> vertexEdge2;
            g->addEdge(vertexEdge1, vertexEdge2);
        }

        // cout << "busca de ciclos por permutação" << endl;

        auto inicio_Permutation = high_resolution_clock::now();

        if ((algoritmo & 1) && !g->permutationFindCycles()) {
            // cout << " Nenhum ciclo encontrado" << endl;
        }

        auto fim_Permutation = high_resolution_clock::now();

        auto duracao_Permutation = duration_cast<microseconds>(fim_Permutation - inicio_Permutation);

        // cout << "busca de ciclos por caminhamento DFS sem filtro de ciclos repetidos" << endl;

        auto inicio_DFSv1 = high_resolution_clock::now();

        if ((algoritmo & 2) && !g->searchAlgortihmFindCycles()) {
            // cout << " Nenhum ciclo encontrado" << endl;
        }

        auto fim_DFSv1 = high_resolution_clock::now();

        auto duracao_DFSv1 = duration_cast<microseconds>(fim_DFSv1 - inicio_DFSv1);

        // cout << "busca de ciclos por caminhamento DFS com filtro de ciclos repetidos" << endl;

        auto inicio_DFSv2 = high_resolution_clock::now();

        if ((algoritmo & 2) && !g->searchAlgortihmFindCyclesv2()) {
            // cout << " Nenhum ciclo encontrado" << endl;
        }

        auto fim_DFSv2 = high_resolution_clock::now();

        auto duracao_DFSv2 = duration_cast<microseconds>(fim_DFSv2 - inicio_DFSv2);

        int duracao_perm   = (algoritmo & 1)?duracao_Permutation.count():0;
        int duracao_dfsv1  = (algoritmo & 2)?duracao_DFSv1.count():0;
        int duracao_dfsv2  = (algoritmo & 2)?duracao_DFSv2.count():0;

        int op_count_perm  = (algoritmo & 1)?g->getopCountPermutation():0;
        int op_count_dfsv1 = (algoritmo & 2)?g->getopCountDFSv1():0;
        int op_count_dfsv2 = (algoritmo & 2)?g->getopCountDFSv2():0;

        outFile << i + 1 << "," << numVertex << "," << numEdges << "," << duracao_perm << "," << duracao_dfsv1 << "," << duracao_dfsv2 << endl;
        outFile2 << i + 1 << "," << numVertex << "," << numEdges << "," << op_count_perm << "," << op_count_dfsv1 << "," << op_count_dfsv2 << endl;
        updateProgressBar(i, numGraphs);
    }
    updateProgressBar(numGraphs, numGraphs);

    std::cout << "\nBusca de ciclos completa!\n";
    std::cout << "Arquivos gerados:\n";
    std::cout << "- Grafos: \"graphs.txt\"\n";
    std::cout << "- Metadados de tempo de processamento: \"" << opTimeCSV << "\"\n";
    std::cout << "- Metadados de contagem de operacoes: \"" << opCountCSV << "\"\n";
    std::cout << "==========================================================\n";

    outFile.close();
    outFile2.close();

    return 0;
}

// Função para atualizar e exibir a barra de progresso
void updateProgressBar(int current, int total) {
    const int barWidth = 50;  // Largura da barra de progresso
    const string greenBar = "\033[32m";  // Código ANSI para texto verde
    const string resetColor = "\033[0m";  // Reseta a cor para o padrão do terminal

    float progress = static_cast<float>(current) / total;
    int pos = static_cast<int>(barWidth * progress);

    cout << greenBar;
    cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) cout << "=";  // Preenche a barra em verde
        else if (i == pos) cout << ">";  // Indicador de progresso em verde
        else cout << " ";  // Completa o resto da barra com espaços
    }
    if (current != total) {
        cout << "] " << current+1 << "/" << total << resetColor << "\r";
    } else {
        cout << "] " << current << "/" << total << resetColor << endl;
    }
    cout.flush();
}
