#pragma once
#include "BinarySave.h"

const string RUTA_DATA = "../Data/data.bin";
const string RUTA_INDEX = "../Data/index.csv";

using namespace std;

int BinarySave::getNumRegistros()
{
    return numRegistros;
}

void BinarySave::addNumRegistros()
{
    numRegistros++;
}

void BinarySave::setNumRegistros(streampos pos)
{
    numRegistros = pos / 200;
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
        vector<string> cut = Tools::splitString(linea, ',');
        string dniStr = cut[0];
        string posicionStr = cut[1];

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

    vector<string> cut = Tools::splitString(registro, ';');

    ciudadano.setDNI(cut[0]);
    ciudadano.setNombres(cut[1]);
    ciudadano.setApellidos(cut[2]);
    ciudadano.setNacionalidad(cut[3]);
    ciudadano.setLugarNacimiento(cut[4]);
    ciudadano.setDireccion(cut[5]);
    ciudadano.setTelefono(cut[6]);
    ciudadano.setCorreoElectronico(cut[7]);
    ciudadano.setEstadoCivil(cut[8]);

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

    linea += string(195 - linea.length(), ' ') + ";";

    int tamanoStr = linea.size();

    fileData.write(reinterpret_cast<const char *>(&tamanoStr), sizeof(tamanoStr));
    fileData.write(linea.c_str(), tamanoStr);

    fileIndex << ciudadano.getDNI() << "," << getNumRegistros() * 200 << "\n";
}

void BinarySave::save(Ciudadano &ciudadano)
{
    fstream file("../Data/data.bin", ios::out | ios::app | ios::binary);
    if (!file.is_open())
    {
        cerr << "Fallo al abrir ../Data/data.bin \n";
        cin.get();
    }
    
    fstream indexFile("../Data/index.csv", ios::in | ios::out | ios::app);
    if (!indexFile.is_open())
    {
        cerr << "Fallo al abrir ../Data/index.csv \n";
        cin.get();
    }

    insert(ciudadano, file, indexFile);

    file.close();
    indexFile.close();

    addNumRegistros();
}

void BinarySave::erase(string dni)
{
    streampos posicionEliminar = buscarPos(dni);
    streampos posicionUltimo = (numRegistros - 1) * 200;

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
        vector<string> cut = Tools::splitString(linea, ',');
        string dniStr = cut[0];
        string posicionStr = cut[1];

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

    setNumRegistros(posicionUltimo);
}