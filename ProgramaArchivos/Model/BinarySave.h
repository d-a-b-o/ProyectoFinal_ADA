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
    streampos buscarPos(string dni);
    Ciudadano buscar(string dni);
    void insert(Ciudadano &ciudadano, fstream &file, fstream &fileIndex);
    void save(Ciudadano &ciudadano);
    void erase(string dni);
    void addNumRegistros();
    void setNumRegistros(streampos pos);
    int getNumRegistros();
};