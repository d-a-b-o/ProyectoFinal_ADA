#pragma once
#include "../Model/Ciudadano.cpp"

using namespace std;

class Menu
{
public:
    void mostrarMenuPrincipal();
    int leerOpcion();
    Ciudadano leerCiudadano();
    void menuIngresarUsuario();
};