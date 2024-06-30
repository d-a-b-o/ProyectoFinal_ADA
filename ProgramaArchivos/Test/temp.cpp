#include <iostream>
#include "../Model/Ciudadano.cpp"
#include "../Controller/GeneradorController.cpp"

using namespace std;
GeneradorController gen;

int main(int argc, char const *argv[])
{
    Ciudadano temp = gen.generarCiudadano();
    string holis = "Holis";
    cout << holis.length();
    return 0;
}
