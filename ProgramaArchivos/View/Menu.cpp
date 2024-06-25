#pragma once
#include <iostream>
#include <string>
#include "Menu.h"

using namespace std;

void Menu::mostrarMenuPrincipal()
{
    cout << "=================================" << endl;
    cout << "       Gestion de Registros      " << endl;
    cout << "=================================" << endl;
    cout << "1. Agregar Registro" << endl;
    cout << "2. Buscar Registro" << endl;
    cout << "3. Eliminar Registro" << endl;
    cout << "4. Salir" << endl;
    cout << "Seleccione una opción: ";
}

int Menu::leerOpcion()
{
    int opt;
    cin >> opt;
    return opt;
}

Ciudadano Menu::leerCiudadano()
{
    int dni;
    string nombre;

    cout << "Ingrese dni(8 digitos): ";
    cin >> dni;
    
    
    return Ciudadano();
}
