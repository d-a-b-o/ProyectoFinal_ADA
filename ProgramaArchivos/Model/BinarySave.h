#pragma once
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <string>
#include "../Model/Ciudadano.cpp"
#include "../Tools/Tools.cpp"

using namespace std;

class BinarySave
{
private:
    int numRegistros = 0;
public:
    Ciudadano buscar(streampos posicion);
    void insert(Ciudadano &ciudadano, fstream &file);
    void save(Ciudadano &ciudadano);
    void erase(streampos posicion);
    void addNumRegistros();
    int getNumRegistros();
};