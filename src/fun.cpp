#include "../include/include.hpp"
#include "../include/structures.hpp"

void fileNotOk(std::ifstream& fin, std::string message)
{
    cerr << message << endl;
    fin.ignore();
    fin.clear();
    fin.close();
    exit(-1);
}

void fileNotOk(std::ostream& fout, std::string message)
{
    cerr << message << endl;
    fout.clear();
    exit(-1);
}