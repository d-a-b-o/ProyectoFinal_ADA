#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "../Model/Ciudadano.cpp"

using namespace std;

class BinarySave
{
private:
    streampos ultimaPosicion = 0;
public:
    streampos insert(Ciudadano &ciudadano, fstream &file, fstream &fileIndex, int opt);
    streampos buscarPos(string dni);
    Ciudadano buscar(string dni);
    void leerUltimaPosicion();
    void sobreEscribirUltimaPosicion();
    streampos getUltimaPosicion();
    void addUltimaPosicion(streampos pos);
    void setUltimaPosicion(streampos pos);
    void save(Ciudadano &ciudadano);
    void erase(string dni);
};