#pragma once
#include <fstream>
#include <string>
#include <functional>
#include <vector>
#include "../Model/Ciudadano.cpp"

using namespace std;

class BinarySave
{
private:
    streampos ultimaPosicion = 0;
public:
    void insert(Ciudadano &ciudadano, fstream &file, fstream &fileIndex);
    Ciudadano buscar(string dni);
    void leerUltimaPosicion();
    void sobreEscribirUltimaPosicion();
    streampos getUltimaPosicion();
    void save(Ciudadano &ciudadano);
};