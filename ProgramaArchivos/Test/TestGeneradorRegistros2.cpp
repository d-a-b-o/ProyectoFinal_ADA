#include <iostream>
#include <map>
#include <vector>
#include "../Tools/GeneradorRegistros.cpp"

using namespace std;

int main() {
    try {
        map<string, vector<string>> nombres = GeneradorRegistros::cargarNombresCSV("nombres.csv");
        vector<string> apellidos = GeneradorRegistros::cargarApellidosCSV("apellidos.csv");
        vector<string> lugares = {"Amazonas", "Áncash", "Apurímac", "Arequipa", "Ayacucho", "Cajamarca", "Cusco", "Huancavelica", "Huánuco", "Ica", "Junín", "La Libertad", "Lambayeque", "Lima", "Loreto", "Madre de Dios", "Moquegua", "Pasco", "Piura", "Puno", "San Martín", "Tacna", "Tumbes", "Ucayali"
};

        Ciudadano ciudadano = GeneradorRegistros::generarCiudadanoAleatorio(nombres, apellidos, lugares);

        cout << "DNI: " << ciudadano.getDNI() << endl;
        cout << "Nombres: " << ciudadano.getNombres() << endl;
        cout << "Apellidos: " << ciudadano.getApellidos() << endl;
        cout << "Nacionalidad: " << ciudadano.getNacionalidad() << endl;
        cout << "Lugar de Nacimiento: " << ciudadano.getLugarNacimiento() << endl;
        cout << "Direccion: " << ciudadano.getDireccion() << endl;
        cout << "Telefono: " << ciudadano.getTelefono() << endl;
        cout << "Correo Electronico: " << ciudadano.getCorreoElectronico() << endl;
        cout << "Estado Civil: " << ciudadano.getEstadoCivil() << endl;
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}
