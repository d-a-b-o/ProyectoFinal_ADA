#include <iostream>
#include "../Tools/GeneradorRegistros.cpp"

using namespace std;

int main()
{
    cout << GeneradorRegistros::generarDNIAleatorio();
    return 0;
}