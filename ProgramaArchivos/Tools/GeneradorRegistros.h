#pragma once
#include "../Model/Ciudadano.cpp"
#include <vector>
#include <string>
#include <map>

class GeneradorRegistros
{
public:
    static int generarDNIAleatorio();
    static std::map<std::string, std::vector<std::string>> cargarNombresCSV(const std::string& rutaArchivo);
    static std::vector<std::string> cargarApellidosCSV(const std::string& rutaArchivo);
    static std::string generarTelefono();
    static std::string generarCorreo(const std::string& nombre, const std::string& apellido);
    static std::string generarDireccion();
    static std::string generarEstadoCivil();
    static Ciudadano generarCiudadanoAleatorio(const std::map<std::string, std::vector<std::string>>& nombres, const std::vector<std::string>& apellidos, const std::vector<std::string>& lugares);

private:
    static std::string getRandomElement(const std::vector<std::string>& elements);

};

