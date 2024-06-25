#pragma once
#include <iostream>
#include <fstream>
#include "MainController.h"
#include "../Tools/Tools.cpp"

const int NUM_RANDOM = 3300000;
const string RUTA_DATA = "../Data/data.bin";
const string RUTA_INDEX = "../Data/index.csv";

using namespace std;

MainController::MainController() : dniTree(25)
{
    genController = GeneradorController();
    binarySave.leerUltimaPosicion();
}

void MainController::run()
{
    int opt;
    do
    {
        system("cls");
        cout << "=== MENU PRINCIPAL ===" << endl;
        cout << "[1] Ingresar ciudadano" << endl;
        cout << "[2] Buscar ciudadano" << endl;
        cout << "[3] Generar 33 millones" << endl;
        cout << "[0] Cerrar" << endl;
        cin >> opt;
        system("cls");
        switch (opt)
        {
        case 1:
            addCiudadano();
            break;
        case 2:
            searchCiudadano();
            break;
        case 3:
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

    if (!dniTree.search(stoi(dni)))
    {
        Ciudadano nuevoCiudadano(dni, nombres, apellidos, nacionalidad, lugarNacimiento, direccion, telefono, correoElectronico, estadoCivil);
        dniTree.insert(stoi(dni));
        binarySave.save(nuevoCiudadano);
    }
    else
    {
        cout << "Ciudadano ya existente." << endl;
    }
}

void MainController::searchCiudadano()
{
    string dni;
    cin.ignore();
    cout << "=== BUSCAR CIUDADANO ===" << endl;
    cout << "Ingrese DNI: " << endl;
    getline(cin, dni);

    if (dniTree.search(stoi(dni)))
    {
        cout << "Ciudadano registrado." << endl;
        Ciudadano ciudadano;
        ciudadano = binarySave.buscar(dni);
        cout << ciudadano.getNombres();
    }
    else
    {
        cout << "Ciudadano no encontrado." << endl;
    }

    system("pause");
}

void MainController::deleteCiudadano()
{
}

void MainController::generateRandom()
{
    int i = 0;

    fstream file(RUTA_DATA, ios::out | ios::app | ios::binary);
    fstream indexFile(RUTA_INDEX, ios::in | ios::out | ios::app);

    if (file.is_open() & indexFile.is_open())
    {
        while (i < 33)
        {
            Ciudadano ciudadano = genController.generarCiudadano('0');

            int dni = stoi(ciudadano.getDNI());
            if (!dniTree.search(dni))
            {
                dniTree.insert(dni);
                binarySave.insert(ciudadano, file, indexFile);
            }
            i++;
        }
        file.close();
        indexFile.close();
    }
    else
    {
        cerr << "Failed to open file: " << RUTA_DATA<< "\n";
    }

    binarySave.sobreEscribirUltimaPosicion();
}

void MainController::loadBTree()
{

}