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

string GeneradorController::generarDni()
{
    string dni = "";

    for (int i = 0; i < 8; i++)
        dni += to_string(Tools::getRandomNumber(0, 9));

    return dni;
}

string GeneradorController::generarNombres()
{
    string genero = (Tools::getRandomNumber(0, 1) == 0) ? "MASCULINO" : "FEMENINO";
    int num = mapNombres.at(genero).size() - 1;
    int posPrimerNombre = Tools::getRandomNumber(0, num);
    int posSegundoNombre = Tools::getRandomNumber(0, num);
    string primerNombre = mapNombres.at(genero)[posPrimerNombre];
    string segundoNombre = mapNombres.at(genero)[posSegundoNombre];
    string nombres = primerNombre + " " + segundoNombre;

    return nombres;
}

string GeneradorController::generarApellidos()
{
    int posPrimerApellido = Tools::getRandomNumber(0, lstApellidos.size() - 1);
    int posSegundoApellido = Tools::getRandomNumber(0, lstApellidos.size() - 1);
    string primerApellido = lstApellidos[posPrimerApellido];
    string segundoApellido = lstApellidos[posSegundoApellido];
    string apellidos = primerApellido + " " + segundoApellido;


    return apellidos;
}

string GeneradorController::generarNacionalidad()
{
    string nacionalidad = "Peruana";


    return nacionalidad;
}

string GeneradorController::generarLugarNacimiento()
{
    string departamento = Tools::selectRandomElement(lstDepartamentos);

    return departamento;
}

string GeneradorController::generarDireccion()
{
    string numeroCalle = to_string(Tools::getRandomNumber(1, 9999));
    string nombreCalle = Tools::selectRandomElement(lstCalles);
    string tipoCalle = Tools::selectRandomElement(lstTipoCalle);
    string departamento = Tools::selectRandomElement(lstDepartamentos);
    int posProvincia = Tools::getRandomNumber(0, mapDepartamentos.at(departamento).size() - 1);
    string provincia = mapDepartamentos.at(departamento)[posProvincia];

    string direccion = tipoCalle + " " + nombreCalle + " " + numeroCalle + " " + provincia + ", " + departamento;

    return direccion;
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

    string correo = nombres.substr(0, posSpaceNombres) + "." + apellidos.substr(0, posSpaceApellidos) + "@example.com";

    return correo;
}

string GeneradorController::generarEstadoCivil()
{
    string estadoCivil = Tools::selectRandomElement(lstEstados);

    return estadoCivil;
}

Ciudadano GeneradorController::generarCiudadano()
{
    string DNI = generarDni();
    string nombres = "Francisco Arturo";
    string apellidos = "Sanchez Astete";
    string nacionalidad = generarNacionalidad();
    string lugarNacimiento = generarLugarNacimiento();
    string direccion = "Av. La Fontana 550, La Molina";
    string telefono = generarTelefono();
    string correo = generarCorreo(nombres, apellidos);
    string estadoCivil = generarEstadoCivil();

    return Ciudadano(DNI, nombres, apellidos, nacionalidad, lugarNacimiento, direccion, telefono, correo, estadoCivil);
}
