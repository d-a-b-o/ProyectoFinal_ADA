#pragma once
#include <iostream>
#include <unistd.h>
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

void BinarySave::addUltimaPosicion(streampos pos)
{
    ultimaPosicion += pos;
}

void BinarySave::setUltimaPosicion(streampos pos)
{
    ultimaPosicion = pos;
}

streampos BinarySave::buscarPos(string dni)
{
    fstream indexFile("../Data/index.csv", ios::in);
    if (!indexFile.is_open())
    {
        cerr << "No se pudo abrir el archivo indices.csv" << endl;
        return 0;
    }

    string linea;
    streampos posicion = 0;

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

    return posicion;
}

Ciudadano BinarySave::buscar(string dni)
{
    Ciudadano ciudadano;
    streampos posicion = buscarPos(dni);

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

    vector<string> lst;

    for(string i:lst)
    {

    }
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

streampos BinarySave::insert(Ciudadano &ciudadano, fstream &fileData, fstream &fileIndex, int opt)
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

    linea += string(195 - linea.length(), ' ') + ";";

    int tamanoStr = linea.size();

    fileData.write(reinterpret_cast<const char *>(&tamanoStr), sizeof(tamanoStr));
    fileData.write(linea.c_str(), tamanoStr);

    streampos posicion = fileData.tellp();

    fileIndex << ciudadano.getDNI() << "," << getUltimaPosicion() << "\n";

    return posicion;
}

void BinarySave::save(Ciudadano &ciudadano)
{
    fstream file("../Data/data.bin", ios::out | ios::app | ios::binary);
    fstream indexFile("../Data/index.csv", ios::in | ios::out | ios::app);

    if (file.is_open())
    {
        insert(ciudadano, file, indexFile, 1);
        addUltimaPosicion(200);
        file.close();
    }
    else
    {
        cerr << "No se pudo abrir el archivo data.bin" << endl;
    }

    sobreEscribirUltimaPosicion();
}

void BinarySave::erase(string dni)
{
    streampos posicionEliminar = buscarPos(dni);
    streampos posicionUltimo = ultimaPosicion.operator-(200);

    fstream file("../Data/data.bin", ios::in | ios::out | ios::binary);
    if (!file.is_open())
    {
        cerr << "No se pudo abrir el archivo data.bin" << endl;
        return;
    }

    // Eliminacion Data
    if (posicionEliminar == posicionUltimo)
    {
        file.close();
        truncate("../Data/data.bin", posicionUltimo);
    }
    else
    {
        file.seekg(posicionUltimo);
        int tamanoStr;
        file.read(reinterpret_cast<char *>(&tamanoStr), sizeof(tamanoStr));
        vector<char> buffer(tamanoStr);
        file.read(buffer.data(), tamanoStr);

        file.seekp(posicionEliminar);
        file.write(reinterpret_cast<const char *>(&tamanoStr), sizeof(tamanoStr));
        file.write(buffer.data(), tamanoStr);

        file.close();
        truncate("../Data/data.bin", posicionUltimo);
    }
    
    fstream indexFile("../Data/index.csv", ios::in | ios::out);
    if (!indexFile.is_open())
    {
        cerr << "No se pudo abrir el archivo indices.csv" << endl;
        return;
    }

    // Eliminacion Index
    string linea;
    vector<string> indexLines;
    while (getline(indexFile, linea))
    {
        stringstream ss(linea);
        string dniStr, posicionStr;
        getline(ss, dniStr, ',');
        getline(ss, posicionStr, ',');

        if (static_cast<streampos>(stoll(posicionStr)) == posicionUltimo)
        {
            indexLines.push_back(dniStr + "," + to_string(posicionEliminar) + "\n");
        }
        else if (dniStr != dni)
        {
            indexLines.push_back(linea + "\n");
        }
    }

    indexFile.close();

    ofstream indexFileTruncate("../Data/index.csv", ios::trunc);
    for (const auto &line : indexLines)
    {
        indexFileTruncate << line;
    }
    indexFileTruncate.close();

    setUltimaPosicion(posicionUltimo);
    sobreEscribirUltimaPosicion();
}