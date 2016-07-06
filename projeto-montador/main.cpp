#include <iostream>
#include "Montador.h"
#include <vector>
#include <string>
#include <map>

using namespace std;

int main()
{
    Montador m;

    m.assemblerOne("Entrada.txt");
    m.printObjectCode();

    return 0;
}
