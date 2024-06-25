#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "BinarySave.h"
#include "../Controller/GeneradorController.cpp"

const string RUTA_ULTIMA_POSICION = "../Data/final.txt";

using namespace std;

void BinarySave::leerUltimaPosicion()
{
    ifstream archivo(RUTA_ULTIMA_POSICION);
    int numero;

    if (archivo.is_open())
    {
        archivo >> numero;
        archivo.close();
        ultimaPosicion = numero;
    }
}

void BinarySave::sobreEscribirUltimaPosicion()
{
    ofstream archivo(RUTA_ULTIMA_POSICION);

    if (archivo.is_open())
    {
        archivo << ultimaPosicion;
        archivo.close();
    }
}

streampos BinarySave::getUltimaPosicion()
{
    return ultimaPosicion;
}

Ciudadano BinarySave::buscar(string dni)
{
    fstream indexFile("../Data/index.bin", ios::in);
    if (!indexFile.is_open())
    {
        cerr << "No se pudo abrir el archivo indices.csv" << endl;
        return Ciudadano();
    }

    string linea;
    streampos posicion = -1;

    while (getline(indexFile, linea))
    {
        stringstream ss(linea);
        string dniStr, posicionStr;
        getline(ss, dniStr, ',');
        getline(ss, posicionStr, ',');

        if (dniStr == dni)
        {
            posicion = static_cast<streampos>(stoll(posicionStr));
            break;
        }
    }
    indexFile.close();

    fstream file("../Data/data.bin", ios::in | ios::binary);
    if (!file.is_open())
    {
        cerr << "No se pudo abrir el archivo data.bin" << endl;
        return Ciudadano();
    }

    file.seekg(posicion);

    int tamanoStr;
    file.read(reinterpret_cast<char *>(&tamanoStr), sizeof(tamanoStr));

    vector<char> buffer(tamanoStr);
    file.read(buffer.data(), tamanoStr);
    file.close();

    string registro(buffer.begin(), buffer.end());
    stringstream ss(registro);
    string token;


    Ciudadano ciudadano;
    getline(ss, token, ';');
    ciudadano.setDNI(token);
    getline(ss, token, ';');
    ciudadano.setNombres(token);
    getline(ss, token, ';');
    ciudadano.setApellidos(token);
    getline(ss, token, ';');
    ciudadano.setNacionalidad(token);
    getline(ss, token, ';');
    ciudadano.setLugarNacimiento(token);
    getline(ss, token, ';');
    ciudadano.setDireccion(token);
    getline(ss, token, ';');
    ciudadano.setTelefono(token);
    getline(ss, token, ';');
    ciudadano.setCorreoElectronico(token);
    getline(ss, token, ';');
    ciudadano.setEstadoCivil(token);

    return ciudadano;
}

void BinarySave::insert(Ciudadano &ciudadano, fstream &fileData, fstream &fileIndex)
{
    string linea = ciudadano.getDNI() + ";" +
                   ciudadano.getNombres() + ";" +
                   ciudadano.getApellidos() + ";" +
                   ciudadano.getNacionalidad() + ";" +
                   ciudadano.getLugarNacimiento() + ";" +
                   ciudadano.getDireccion() + ";" +
                   ciudadano.getTelefono() + ";" +
                   ciudadano.getCorreoElectronico() + ";" +
                   ciudadano.getEstadoCivil() + ";";

    int tamanoStr = linea.size();

    fileData.write(reinterpret_cast<const char *>(&tamanoStr), sizeof(tamanoStr));
    fileData.write(linea.c_str(), tamanoStr);

    streampos tamanio = fileData.tellp();

    fileIndex << ciudadano.getDNI() << "," << getUltimaPosicion() << "," << tamanio << "\n";

    ultimaPosicion += tamanio;
}

void BinarySave::save(Ciudadano &ciudadano)
{
    fstream file("../Data/data.bin", ios::out | ios::app | ios::binary);
    fstream indexFile("../Data/index.bin", ios::in | ios::out | ios::app);

    if (file.is_open())
    {
        insert(ciudadano, file, indexFile);
        file.close();
    }
    else
    {
        cerr << "No se pudo abrir el archivo data.bin" << endl;
    }

    sobreEscribirUltimaPosicion();
}