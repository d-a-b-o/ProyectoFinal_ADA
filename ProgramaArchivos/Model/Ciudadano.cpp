#pragma once
#include "Ciudadano.h"

Ciudadano::Ciudadano(string _dni = "", string _nombres = "", string _apellidos = "", string _nacionalidad = "", string _lugarNacimiento = "", string _direccion = "", string _telefono = "", string _correoElectronico = "", string _estadoCivil = "")
{
    DNI                 = _dni;
    nombres             = _nombres;
    apellidos           = _apellidos;
    nacionalidad        = _nacionalidad;
    lugarNacimiento     = _lugarNacimiento;
    direccion           = _direccion;
    telefono            = _telefono;
    correoElectronico   = _correoElectronico;
    estadoCivil         = _estadoCivil;
}

void Ciudadano::setDNI(string _dni)
{
    DNI = _dni;
}
void Ciudadano::setNombres(string _nombres)
{
    nombres = _nombres;
}
void Ciudadano::setApellidos(string _apellidos)
{
    apellidos = _apellidos;
}
void Ciudadano::setNacionalidad(string _nacionalidad)
{
    nacionalidad = _nacionalidad;
}
void Ciudadano::setLugarNacimiento(string _lugarNacimiento)
{
    lugarNacimiento = _lugarNacimiento;
}
void Ciudadano::setDireccion(string _direccion)
{
    direccion = _direccion;
}
void Ciudadano::setTelefono(string _telefono)
{
    telefono = _telefono;
}
void Ciudadano::setCorreoElectronico(string _correoElectronico)
{
    correoElectronico = _correoElectronico;
}
void Ciudadano::setEstadoCivil(string _estadoCivil)
{
    estadoCivil = _estadoCivil;
}

string Ciudadano::getDNI()
{
    return DNI;
}
string Ciudadano::getNombres()
{
    return nombres;
}
string Ciudadano::getApellidos()
{
    return apellidos;
}
string Ciudadano::getNacionalidad()
{
    return nacionalidad;
}
string Ciudadano::getLugarNacimiento()
{
    return lugarNacimiento;
}
string Ciudadano::getDireccion()
{
    return direccion;
}
string Ciudadano::getTelefono()
{
    return telefono;
}
string Ciudadano::getCorreoElectronico()
{
    return correoElectronico;
}
string Ciudadano::getEstadoCivil()
{
    return estadoCivil;
}