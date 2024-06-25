#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include "GeneradorController.h"
#include "../Tools/Tools.cpp"

const string RUTA_NOMBRES = "../Data/nombres.csv";
const string RUTA_APELLIDOS = "../Data/apellidos.csv";
const string RUTA_DEPARTAMENTOS = "../Data/departamentos.csv";

using namespace std;

GeneradorController::GeneradorController()
{
    loadMapNombres();
    loadMapDepartamentos();
    loadLstApellidos();
    lstCalles = {"Azangaro", "La Merced", "Ingenieros", "Javier Prado", "Huerfanos", "Emancipacion", "Flora Tristan", "Sauce", "Velasco Astete", "Chacarilla", "Benavides", "Carabaya"};
    lstTipoCalle = {"Calle", "Avenida", "Jiron", "Pasaje"};
    lstEstados = {"Soltero", "Casado", "Viudo", "Divorciado"};
}

void GeneradorController::loadMapNombres()
{
    ifstream file(RUTA_NOMBRES);
    string linea;

    while (getline(file, linea))
    {
        stringstream ss(linea);
        string nombre, genero;
        getline(ss, nombre, ',');
        getline(ss, genero, ',');
        mapNombres[genero].push_back(nombre);
    }
}

void GeneradorController::loadLstApellidos()
{
    ifstream file(RUTA_APELLIDOS);
    string linea;

    while (getline(file, linea))
        lstApellidos.push_back(linea);
}

void GeneradorController::loadMapDepartamentos()
{
    ifstream file(RUTA_DEPARTAMENTOS);
    string linea;

    while (getline(file, linea))
    {
        stringstream ss(linea);
        string departamento, provincias;

        if (getline(ss, departamento, ',') && getline(ss, provincias))
        {
            lstDepartamentos.push_back(departamento);
            mapDepartamentos[departamento] = Tools::splitString(provincias, ';');
        }
    }
}

string GeneradorController::generarDni(char inicial)
{
    string dni = "";

    for (int i = 0; i < 8; i++)
        dni += to_string(Tools::getRandomNumber(0, 9));

    return dni;
}

string GeneradorController::generarNombres()
{
    string genero = (Tools::getRandomNumber(0, 1) == 0) ? "MASCULINO" : "FEMENINO";
    int posPrimerNombre = Tools::getRandomNumber(0, mapNombres.at(genero).size() - 1);
    int posSegundoNombre = Tools::getRandomNumber(0, mapNombres.at(genero).size() - 1);
    string primerNombre = mapNombres.at(genero)[posPrimerNombre];
    string segundoNombre = mapNombres.at(genero)[posSegundoNombre];

    return primerNombre + " " + segundoNombre;
}

string GeneradorController::generarApellidos()
{
    int posPrimerApellido = Tools::getRandomNumber(0, lstApellidos.size() - 1);
    int posSegundoApellido = Tools::getRandomNumber(0, lstApellidos.size() - 1);
    string primerApellido = lstApellidos[posPrimerApellido];
    string segundoApellido = lstApellidos[posSegundoApellido];

    return primerApellido + " " + segundoApellido;
}

string GeneradorController::generarNacionalidad()
{
    return "Peruana";
}

string GeneradorController::generarLugarNacimiento()
{
    return Tools::selectRandomElement(lstDepartamentos);
}

string GeneradorController::generarDireccion()
{
    string numeroCalle = to_string(Tools::getRandomNumber(1, 9999));
    string nombreCalle = Tools::selectRandomElement(lstCalles);
    string tipoCalle = Tools::selectRandomElement(lstTipoCalle);
    string departamento = Tools::selectRandomElement(lstDepartamentos);
    int posProvincia = Tools::getRandomNumber(0, mapDepartamentos.at(departamento).size() - 1);
    string provincia = mapDepartamentos.at(departamento)[posProvincia];
    string codigoPostal = to_string(Tools::getRandomNumber(10000, 99999));

    return tipoCalle + " " + nombreCalle + " " + numeroCalle + " " + provincia + ", " + departamento + " " + codigoPostal;
}

string GeneradorController::generarTelefono()
{
    string telefono = "9";

    for (int i = 0; i < 8; i++)
        telefono += to_string(Tools::getRandomNumber(0, 9));

    return telefono;
}

string GeneradorController::generarCorreo(string &nombres, string &apellidos)
{
    int posSpaceNombres = nombres.find(' ');
    int posSpaceApellidos = apellidos.find(' ');

    return nombres.substr(0, posSpaceNombres) + "." + apellidos.substr(0, posSpaceApellidos) + "@example.com";
}

string GeneradorController::generarEstadoCivil()
{
    return Tools::selectRandomElement(lstEstados);
}

Ciudadano GeneradorController::generarCiudadano(char inicial)
{
    string DNI = generarDni(inicial);
    string nombres = generarNombres();
    string apellidos = generarApellidos();
    string nacionalidad = generarNacionalidad();
    string lugarNacimiento = generarLugarNacimiento();
    string direccion = generarDireccion();
    string telefono = generarTelefono();
    string correo = generarCorreo(nombres, apellidos);
    string estadoCivil = generarEstadoCivil();

    return Ciudadano(DNI, nombres, apellidos, nacionalidad, lugarNacimiento, direccion, telefono, correo, estadoCivil);
}
