#pragma once
#include "MainController.h"

using namespace std;
using namespace std::chrono;

MainController::MainController() : dniTree(25)
{
    loadBTree();
}

void MainController::run()
{
    int opt;
    do
    {
        system("clear");
        cout << "=== MENU PRINCIPAL ===" << endl;
        cout << "[1] Ingresar ciudadano" << endl;
        cout << "[2] Buscar ciudadano" << endl;
        cout << "[3] Eliminar ciudadano" << endl;
        cout << "[0] Cerrar" << endl;
        cin >> opt;
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

        default:
            break;
        }

    } while (opt != 0);
}

void MainController::addCiudadano()
{
    string dni, nombres, apellidos, nacionalidad, lugarNacimiento, direccion, telefono, correoElectronico, estadoCivil;

    system("clear");
    cin.ignore();
    cout << "=== AGREGAR CIUDADANO ===" << endl;
    cout << "Ingrese DNI: " << endl;
    getline(cin, dni);

    if (dniTree.search(stoi(dni)))
    {
        cout << "Ciudadano ya registrado." << endl;
        cin.get();
        return;
    }

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

    Ciudadano nuevoCiudadano(dni, nombres, apellidos, nacionalidad, lugarNacimiento, direccion, telefono, correoElectronico, estadoCivil);
    dniTree.insert(stoi(dni));
    binarySave.save(nuevoCiudadano);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "El tiempo de insercion es de " << duration.count() << " microsegundos.\n";
    cin.get();
}

void MainController::searchCiudadano()
{
    string dni;

    system("clear");
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

    system("clear");
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

void MainController::loadBTree()
{
    auto start = high_resolution_clock::now();

    fstream indexFile("../Data/index.csv", ios::in);
    if (!indexFile.is_open())
    {
        cerr << "Fallo al abrir ../Data/index.csv \n";
        cin.get();
    }

    string linea;

    while (getline(indexFile, linea))
    {
        vector<string> cut = Tools::splitString(linea, ',');
        string dniStr = cut[0];
        dniTree.insert(stoi(dniStr));
        binarySave.addNumRegistros();
    }
    indexFile.close();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);

    cout << "El tiempo de carga del arbol es de " << duration.count() << " segundos.\n";
    cin.get();
}