#include "GeneradorRegistros.h"
#include <string>
#include <random>
#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <sys/stat.h>

using namespace std;

bool fileExists(const string& rutaArchivo) {
    struct stat buffer;
    return (stat(rutaArchivo.c_str(), &buffer) == 0);
}

int GeneradorRegistros::generarDNIAleatorio() {
    default_random_engine generador(random_device{}());
    uniform_int_distribution<int> distribucion(10000000, 19999999);
    return distribucion(generador);
}

map<string, vector<string>> GeneradorRegistros::cargarNombresCSV(const string& rutaArchivo) {
    if (!fileExists(rutaArchivo)) {
        throw runtime_error("El csv no existe");
    }

    map<string, vector<string>> nombres;
    ifstream archivo(rutaArchivo);

    string linea;
    while (getline(archivo, linea)) {
        
        stringstream ss(linea);
        string nombre, genero;
        getline(ss, nombre, ',');
        getline(ss, genero, ',');
        nombres[genero].push_back(nombre);
    }
    return nombres;
}

vector<string> GeneradorRegistros::cargarApellidosCSV(const string& rutaArchivo) {

    vector<string> apellidos;
    ifstream archivo(rutaArchivo);

    string linea;
    while (getline(archivo, linea)) {
        apellidos.push_back(linea);
    }
    return apellidos;
}

string GeneradorRegistros::generarTelefono() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 9);
    string telefono = "9";
    for (int i = 0; i < 8; ++i) {
        telefono += to_string(dist(gen));
    }
    return telefono;
}

string GeneradorRegistros::generarCorreo(const string& nombre, const string& apellido) {
    return nombre + "." + apellido + "@gmail.com";
}

string GeneradorRegistros::generarDireccion() {
    return "Calle X 111";
}

string GeneradorRegistros::generarEstadoCivil() {
    vector<string> estados = {"Soltero", "Casado", "Viudo", "Divorciado"};
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, estados.size() - 1);
    return estados[dist(gen)];
}

Ciudadano GeneradorRegistros::generarCiudadanoAleatorio(const map<string, vector<string>>& nombres, const vector<string>& apellidos, const vector<string>& lugares) {
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distGenero(0, 1);
    string genero = (distGenero(gen) == 0) ? "MASCULINO" : "FEMENINO";

    uniform_int_distribution<> distNombres(0, nombres.at(genero).size() - 1);
    string nombre1 = nombres.at(genero)[distNombres(gen)];
    string nombre2 = nombres.at(genero)[distNombres(gen)];

    uniform_int_distribution<> distApellidos(0, apellidos.size() - 1);
    string apellido1 = apellidos[distApellidos(gen)];
    string apellido2 = apellidos[distApellidos(gen)];

    uniform_int_distribution<> distLugar(0, lugares.size() - 1);

    int dni = GeneradorRegistros::generarDNIAleatorio();
    string lugarNacimiento = lugares[distLugar(gen)];
    string direccion = GeneradorRegistros::generarDireccion();
    string telefono = GeneradorRegistros::generarTelefono();
    string correoElectronico = GeneradorRegistros::generarCorreo(nombre1, apellido1);
    string estadoCivil = GeneradorRegistros::generarEstadoCivil();

    return Ciudadano(dni, nombre1 + " " + nombre2, apellido1 + " " + apellido2, "Peruana", lugarNacimiento, direccion, telefono, correoElectronico, estadoCivil);
}