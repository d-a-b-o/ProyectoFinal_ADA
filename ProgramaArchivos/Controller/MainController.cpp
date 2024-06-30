#pragma once
#include <iostream>
#include <fstream>
#include "MainController.h"
#include "../Tools/Tools.cpp"
#include <chrono>

const int NUM_RANDOM = 1000;
const string RUTA_DATA = "../Data/data.bin";
const string RUTA_INDEX = "../Data/index.csv";

using namespace std;
using namespace std::chrono;

MainController::MainController() : dniTree(25)
{
    genController = GeneradorController();
    binarySave.leerUltimaPosicion();
}

void MainController::run()
{
    loadBTree();
    int opt;
    do
    {
        system("clear");
        cout << "=== MENU PRINCIPAL ===" << endl;
        cout << "[1] Ingresar ciudadano" << endl;
        cout << "[2] Buscar ciudadano" << endl;
        cout << "[3] Eliminar ciudadano" << endl;
        cout << "[4] Generar 33 millones" << endl;
        cout << "[0] Cerrar" << endl;
        cin >> opt;
        system("clear");
        switch (opt)
        {
        case 1:
            addCiudadano();
            break;
        case 2:
            searchCiudadano();
            break;
        case 3:
            deleteCiudadano();
            break;
        case 4:
            generateRandom();
            break;

        default:
            break;
        }

    } while (opt != 0);
}

void MainController::addCiudadano()
{
    string dni, nombres, apellidos, nacionalidad, lugarNacimiento, direccion, telefono, correoElectronico, estadoCivil;

    cin.ignore();
    cout << "=== AGREGAR CIUDADANO ===" << endl;
    cout << "Ingrese DNI: " << endl;
    getline(cin, dni);
    cout << "Ingrese nombres: " << endl;
    getline(cin, nombres);
    cout << "Ingrese apellidos: " << endl;
    getline(cin, apellidos);
    cout << "Ingrese nacionalidad: " << endl;
    getline(cin, nacionalidad);
    cout << "Ingrese lugar de nacimiento: " << endl;
    getline(cin, lugarNacimiento);
    cout << "Ingrese dirección: " << endl;
    getline(cin, direccion);
    cout << "Ingrese teléfono: " << endl;
    getline(cin, telefono);
    cout << "Ingrese correo electrónico: " << endl;
    getline(cin, correoElectronico);
    cout << "Ingrese estado civil: " << endl;
    getline(cin, estadoCivil);

    auto start = high_resolution_clock::now();

    if (!dniTree.search(stoi(dni)))
    {
        Ciudadano nuevoCiudadano(dni, nombres, apellidos, nacionalidad, lugarNacimiento, direccion, telefono, correoElectronico, estadoCivil);
        dniTree.insert(stoi(dni));
        binarySave.save(nuevoCiudadano);
    }
    else
    {
        cout << "Ciudadano ya registrado." << endl;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "El tiempo de insercion es de " << duration.count() << " microsegundos.\n";
    cin.get();
}

void MainController::searchCiudadano()
{
    string dni;
    cin.ignore();
    cout << "=== BUSCAR CIUDADANO ===" << endl;
    cout << "Ingrese DNI: " << endl;
    getline(cin, dni);

    auto start = high_resolution_clock::now();

    if (!dniTree.search(stoi(dni)))
    {
        cout << "Ciudadano no encontrado." << endl;
        cin.get();
        return;
    }

    Ciudadano ciudadano;
    ciudadano = binarySave.buscar(dni);
    cout << "=== DETALLES DEL CIUDADANO ===" << endl;
    cout << "DNI: " << ciudadano.getDNI() << endl;
    cout << "Nombres: " << ciudadano.getNombres() << endl;
    cout << "Apellidos: " << ciudadano.getApellidos() << endl;
    cout << "Nacionalidad: " << ciudadano.getNacionalidad() << endl;
    cout << "Lugar de Nacimiento: " << ciudadano.getLugarNacimiento() << endl;
    cout << "Direccion: " << ciudadano.getDireccion() << endl;
    cout << "Telefono: " << ciudadano.getTelefono() << endl;
    cout << "Correo Electronico: " << ciudadano.getCorreoElectronico() << endl;
    cout << "Estado Civil: " << ciudadano.getEstadoCivil() << endl;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "El tiempo de busqueda es de " << duration.count() << " microsegundos.\n";
    cin.get();
}

void MainController::deleteCiudadano()
{
    string dni;
    cin.ignore();
    cout << "=== ELIMINAR CIUDADANO ===" << endl;
    cout << "Ingrese DNI: " << endl;
    getline(cin, dni);

    auto start = high_resolution_clock::now();

    if (!dniTree.search(stoi(dni)))
    {
        cout << "Ciudadano no encontrado." << endl;
        cin.get();
        return;
    }

    dniTree.remove(stoi(dni));
    binarySave.erase(dni);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "El tiempo de eliminacion es de " << duration.count() << " microsegundos.\n";
    cin.get();
}

void MainController::generateRandom()
{
    auto start = high_resolution_clock::now();

    int i = 0;

    fstream file(RUTA_DATA, ios::out | ios::app | ios::binary);
    fstream indexFile(RUTA_INDEX, ios::in | ios::out | ios::app);

    if (file.is_open() & indexFile.is_open())
    {
        streampos peso;
        while (i < NUM_RANDOM)
        {
            Ciudadano ciudadano = genController.generarCiudadano();

            int dni = stoi(ciudadano.getDNI());
            if (!dniTree.search(dni))
            {
                dniTree.insert(dni);
                peso = binarySave.insert(ciudadano, file, indexFile, 2);
                binarySave.setUltimaPosicion(peso);
            }
            i++;
        }
        file.close();
        indexFile.close();
    }
    else
    {
        cerr << "Failed to open file: " << RUTA_DATA << "\n";
    }

    binarySave.sobreEscribirUltimaPosicion();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);

    cout << "El tiempo de generacion y carga es de " << duration.count() << " segundos.\n";

    cin.get();
}

void MainController::loadBTree()
{
    auto start = high_resolution_clock::now();

    fstream indexFile("../Data/index.csv", ios::in);
    if (!indexFile.is_open())
    {
        cerr << "No se pudo abrir el archivo indices.csv" << endl;
    }

    string linea;

    while (getline(indexFile, linea))
    {
        stringstream ss(linea);
        string dniStr;
        getline(ss, dniStr, ',');
        dniTree.insert(stoi(dniStr));
    }
    indexFile.close();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);

    cout << "El tiempo de carga del arbol es de " << duration.count() << " segundos.\n";
    cin.get();
}