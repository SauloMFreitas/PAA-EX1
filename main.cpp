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
    graph *g = new adjMatrix(5);
    g->addEdge(0,1);
    g->addEdge(0,2);
    g->addEdge(0,3);
    g->addEdge(0,4);
    g->addEdge(1,2);
    g->addEdge(1,3);
    g->addEdge(1,4);
    g->addEdge(2,3);
    g->addEdge(2,4);
    g->addEdge(3,4);
    g->print();
    auto inicio = high_resolution_clock::now();

    if (!g->permutationFindCycles())
    {
        cout << " Nenhum ciclo encontrado" << endl;
    }
    
    auto fim = high_resolution_clock::now();

    auto ducacao = duration_cast<microseconds>(fim - inicio);

    cout << ducacao.count() << " microsegundos" << endl;

    auto inicio_2 = high_resolution_clock::now();

    if (!g->searchAlgortihmFindCycles())
    {
        cout << " Nenhum ciclo encontrado" << endl;
    }
    

    auto fim_2 = high_resolution_clock::now();

    auto duracao_2 = duration_cast<microseconds>(fim_2- inicio_2);
    cout << duracao_2.count() << " microsegundos" << endl;

    
    return 0;
}
