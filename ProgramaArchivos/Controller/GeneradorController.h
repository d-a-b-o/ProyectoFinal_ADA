#pragma once
#include <string>
#include <map>
#include <vector>
#include "../Model/Ciudadano.h"

using namespace std;

class GeneradorController
{
private:
    map<string, vector<string>> mapNombres;
    map<string, vector<string>> mapDepartamentos;
    vector<string> lstDepartamentos;
    vector<string> lstApellidos;
    vector<string> lstCalles;
    vector<string> lstTipoCalle;
    vector<string> lstEstados;

public:
    GeneradorController();
    void loadMapNombres();
    void loadLstApellidos();
    void loadMapDepartamentos();
    string generarDni();
    string generarNombres();
    string generarApellidos();
    string generarNacionalidad();
    string generarLugarNacimiento();
    string generarDireccion();
    string generarTelefono();
    string generarCorreo(string &nombres, string &apellidos);
    string generarEstadoCivil();
    Ciudadano generarCiudadano();
};