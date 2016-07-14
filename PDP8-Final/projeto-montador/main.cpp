#include <iostream>
#include "Montador.h"
#include <vector>
#include <string>
#include <map>

using namespace std;

int main()
{
    Montador m;

    m.assemblerOne("Entrada7.txt");
    m.printObjectCode();
    cout << "\n";
    m.printEDSTable();
    cout << "\n";
    m.printERS();

    return 0;
}
