#include <iostream>
#include "Montador.h"
#include <vector>
#include <string>
#include <map>

using namespace std;

int main()
{
    Montador m;

    m.assemblerOne("Entrada4.txt");

    m.printLiteralTable();

    return 0;
}
