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



string GeneradorRegistros::getRandomElement(const vector<string>& elements) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, elements.size() - 1);
    return elements[dist(gen)];
}
string GeneradorRegistros::generarDireccion() {
    vector<string> nombreCalle = {"Azángaro ", "La Merced", "Ingenieros", "Javier Prado", "Huérfanos", "Emancipación", "Flora Tristán", "Sauce", "Velasco Astete", "Chacarilla", "Benavides" , "Carabaya"};
    vector<string> tipoCalle = {"Calle", "Avenida", "Jirón", "Pasaje"};
    vector<string> provincia = {"Springfield", "Rivertown", "Lakeside", "Hilltop", "Greenfield"};
    vector<string> departamento = {"Amazonas", "Ancash", "Apurímac", "Arequipa", "Ayacucho", "Cajamarca", "Callao", "Cusco", "Huancavelica", "Huánuco", "Ica", "Junin", "La Libertad", "Lambayeque", "Lima", "Loreto", "Madre de Dios", "Moquegua", "Pasco", "Piura", "Puno", "San Martin", "Tacna", "Tumbes", "Ucayali"};

   

    int numeroCalleAleatorio = rand() % 9999 + 1; // Número de calle aleatorio entre 1 y 9999
    string nombreCalleAleatorio = getRandomElement(nombreCalle);
    string tipoCalleAleatorio  = getRandomElement(tipoCalle);
    string provinciaAleatorio;
    string departamentoAleatorio  = getRandomElement(departamento);
     if (departamentoAleatorio =="Amazonas"){
        vector<string> provinciasEspecificas = {"Chachapoyas", "Bagua", "Bongará", "Condorcanqui", "Luya", "Rodríguez de Mendoza", "Utcubamba"};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="Ancash")
    {
        vector<string> provinciasEspecificas = {"Huaraz", "Ajia", "Antonio Raymondi", "Asuncion", "Bolognesi", "Rodríguez de Mendoza", "Huarmey"};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="Apurímac")
    {
        vector<string> provinciasEspecificas = {"Abancay", "Antabamba", "Aymares", "Cotabambas", "Grau", "Chincheros", "Andahuaylas"};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="Arequipa")
    {
        vector<string> provinciasEspecificas = {"Arequipa", "Camaná", "Caravelí", "Castilla", "Caylloma", "Condesuyos", "Islay", "La Unión"};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="Ayacucho")
    {
        vector<string> provinciasEspecificas = {"Cangallo", "Huanta", "Huamanga ", "Huanca Sancos", "La Mar ", "Lucanas", "Parinacochas", "Páucar del Sara Sara", "Sucre", "Víctor Fajardo", "Vilcashuamán"};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="Cajamarca")
    {
        vector<string> provinciasEspecificas = {"Cajamarca", "Cajabamba", "Celedín ", "Chota", "Contumazá", "Cutervo", "Hualgayoc", "Jaén", "San Ignacio", "San Marcos", "San Miguel", "San Pablo", "Santa Cruz"};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="Callao")
    {
        vector<string> provinciasEspecificas = {"Callao"};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="Cusco")
    {
        vector<string> provinciasEspecificas = {"Cusco", "Acomayo", "Anta ", "Calca", "Canas ", "Canchis", "Chumbivilcas", "Espinar", "La Convención", "Paruro", "Paucartambo", "Quispicanchi", "Urubamba"};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="Huancavelica")
    {
        vector<string> provinciasEspecificas = {"Huancavelica", "Acobamba", "Angaraes ", "Castrovirreyna", "Churcampa ", "Huaytará", "Tayacaja"};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="Huánuco")
    {
        vector<string> provinciasEspecificas = {"Huánuco", "Ambo", "Dos de Mayo ", "Huacaybamba", "Humalies ", "Leoncio Prado", "Marañón", "Pachitea", "Puerto Inca", "Lauricocha", "Yarowilca"};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="Ica")
    {
        vector<string> provinciasEspecificas = {"Ica", "Chincha", "Nazca ", "Palpa", "Pisco "};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="Junín")
    {
        vector<string> provinciasEspecificas = {"Chanchamayo", "Chupaca", "Concepción ", "Huancayo", "Jauja ", "Junín", "Satipo", "Tarma", "Yauli"};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="La Libertad")
    {
        vector<string> provinciasEspecificas = {"Trujillo", "Ascope", "Bolívar ", "Chepén", "Julcán ", "Otuzco", "Gran Chimú", "Pacasmayo", "Pataz", "Sánchez Carrión", "Santiago de Chuco", "Virú"};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="Lambayeque")
    {
        vector<string> provinciasEspecificas = {"Chiclayo", "Ferreñafe", "Lambayeque "};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="Lima")
    {
        vector<string> provinciasEspecificas = {"Barranca", "Cajatambo", "Canta ", "Cañete", "Huaral ", "Huarochirí", "Huaura", "Lima", "Oyón", "Yauyos"};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="Loreto")
    {
        vector<string> provinciasEspecificas = {"Maynas", "Putumayo", "Alto Amazonas ", "Loreto", "Mariscal Ramón Castilla ", "Requena", "Ucayali", "Datem del Marañón"};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="Madre de Dios")
    {
        vector<string> provinciasEspecificas = {"Tambopata", "Manu", "Tahuamanu "};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="Moquegua")
    {
        vector<string> provinciasEspecificas = {"Mariscal Nieto", "General Sánchez Cerro", "Ilo"};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="Pasco")
    {
        vector<string> provinciasEspecificas = {"Pasco", "Oxapampa", "Daniel A. Carrión"};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="Piura")
    {
        vector<string> provinciasEspecificas = {"Ayabaca", "Huancabamba", "Morropón ", "Piura", "Sechura ", "Paita", "Talara"};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="Puno")
    {
        vector<string> provinciasEspecificas = {"San Román", "Puno", "Azángaro ", "Chucuito", "El Collao ", "Melgar", "Carabaya", "Huancané", "Sandia", "San Antonio de Putina", "Lampa", "Yunguyo", "Moho"};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="San Martín")
    {
        vector<string> provinciasEspecificas = {"Bellavista", "El Dorado", "Huallaga", "Lamas", "Mariscal Cáceres ", "Moyobamba", "Picota", "Rioja", "San Martín", "Tocache"};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="Tacna")
    {
        vector<string> provinciasEspecificas = {"Tacna", "Candarave", "Jorge Basadre ", "Tarata"};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="Tumbes")
    {
        vector<string> provinciasEspecificas = {"Tumbes", "Zarumilla", "Contralmirante Villar"};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }else if (departamentoAleatorio =="Ucayali")
    {
        vector<string> provinciasEspecificas = {"Coronel Portillo", "Atalaya", "Padre Abad", "Purús"};
        provinciaAleatorio = getRandomElement(provinciasEspecificas);
    }
    
    
    
    int zipCode = rand() % 90000 + 10000; // Código postal aleatorio entre 10000 y 99999

    return tipoCalleAleatorio + " " + nombreCalleAleatorio + " " +  to_string(numeroCalleAleatorio)+ " " + provinciaAleatorio + ", "   + departamentoAleatorio + " " + to_string(zipCode);
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