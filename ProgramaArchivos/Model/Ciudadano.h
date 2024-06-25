#pragma once
#include <string>

using namespace std;

class Ciudadano
{
private:
    string DNI;
    string nombres;
    string apellidos;
    string nacionalidad;
    string lugarNacimiento;
    string direccion;
    string telefono;
    string correoElectronico;
    string estadoCivil;

public:
    Ciudadano(string _dni, string _nombres, string _apellidos, string _nacionalidad, string _lugarNacimiento, string _direccion, string _telefono, string _correoElectronico, string _estadoCivil);

    void setDNI(string _dni);
    void setNombres(string _nombres);
    void setApellidos(string _apellidos);
    void setNacionalidad(string _nacionalidad);
    void setLugarNacimiento(string _lugarNacimiento);
    void setDireccion(string _direccion);
    void setTelefono(string _telefono);
    void setCorreoElectronico(string _correoElectronico);
    void setEstadoCivil(string _estadoCivil);

    string getDNI();
    string getNombres();
    string getApellidos();
    string getNacionalidad();
    string getLugarNacimiento();
    string getDireccion();
    string getTelefono();
    string getCorreoElectronico();
    string getEstadoCivil();
};