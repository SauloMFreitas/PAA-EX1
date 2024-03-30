#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib> // Para rand() e srand()
#include <ctime> // Para time()

using namespace std;

class graphGenerator
{
public:
    static void generateAndPrintGraphs(int numberOfGraphs, const string& fileName, const bool useRand);
};
