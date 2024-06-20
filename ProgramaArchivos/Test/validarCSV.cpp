#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

bool validarFormatoCSV(const string& rutaArchivo) {
    ifstream archivo(rutaArchivo);
    string linea;
    int lineaNumero = 0;
    int lineasIncorrectas = 0;

    while (getline(archivo, linea)) {
        lineaNumero++;
        stringstream ss(linea);
        string nombre, genero;

        getline(ss, nombre, ',');
        getline(ss, genero, ',');

        if (nombre.empty() || genero.empty()) {
            cout << "Formato incorrecto en la línea " << lineaNumero << ": " << linea << endl;
            lineasIncorrectas++;
        } else if (genero != "MASCULINO" && genero != "FEMENINO") {
            cout << "Género incorrecto en la línea " << lineaNumero << ": " << linea << endl;
            lineasIncorrectas++;
        }
    }

    if (lineasIncorrectas == 0) {
        cout << "Todos los datos están en el formato correcto." << endl;
        return true;
    } else {
        cout << "Número total de líneas incorrectas: " << lineasIncorrectas << endl;
        return false;
    }
}

int main() {
    string rutaArchivo = "nombres.csv";
    validarFormatoCSV(rutaArchivo);
    return 0;
}
