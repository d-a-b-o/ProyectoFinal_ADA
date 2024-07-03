#pragma once
#include "BinarySave.h"

const string RUTA_DATA = "../Data/data.bin";
const int SIZE_REGISTRO = 200;

using namespace std;

int BinarySave::getNumRegistros()
{
    return numRegistros;
}

void BinarySave::addNumRegistros()
{
    numRegistros++;
}

Ciudadano BinarySave::buscar(streampos posicion)
{
    Ciudadano ciudadano;

    fstream file(RUTA_DATA, ios::in | ios::binary);
    if (!file.is_open())
    {
        cerr << "No se pudo abrir el archivo data.bin" << endl;
        return Ciudadano();
    }

    file.seekg(posicion * SIZE_REGISTRO);

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

void BinarySave::insert(Ciudadano &ciudadano, fstream &fileData)
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
    addNumRegistros();
}

void BinarySave::save(Ciudadano &ciudadano)
{
    fstream file(RUTA_DATA, ios::out | ios::app | ios::binary);
    if (!file.is_open())
    {
        cerr << "Fallo al abrir ../Data/data.bin \n";
        cin.get();
    }

    insert(ciudadano, file);

    file.close();
}

void BinarySave::erase(streampos posicion)
{
    streampos posicionEliminar = posicion * SIZE_REGISTRO;
    streampos posicionUltimo = (numRegistros - 1) * SIZE_REGISTRO;

    fstream file(RUTA_DATA, ios::in | ios::out | ios::binary);
    if (!file.is_open())
    {
        cerr << "No se pudo abrir el archivo data.bin" << endl;
        return;
    }

    if (posicionEliminar != posicionUltimo)
    {
        file.seekg(posicionUltimo);
        int tamanoStr;
        file.read(reinterpret_cast<char *>(&tamanoStr), sizeof(tamanoStr));
        vector<char> buffer(tamanoStr);
        file.read(buffer.data(), tamanoStr);

        file.seekp(posicionEliminar);
        file.write(reinterpret_cast<const char *>(&tamanoStr), sizeof(tamanoStr));
        file.write(buffer.data(), tamanoStr);
    }

    file.close();
    truncate("../Data/data.bin", posicionUltimo);

    numRegistros--;
}