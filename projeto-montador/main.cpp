#include <iostream>
#include "Montador.h"
#include <vector>
#include <string>
#include <map>

using namespace std;

int main()
{
    Montador m;

    m.assemblerOne("Entrada2.txt");
    m.printObjectCode();
    cout << "\n";
    m.printERS();

    return 0;
}
