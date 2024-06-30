#include <iostream>
#include "../Controller/GeneradorController.cpp"
#include "../Model/Ciudadano.cpp"
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{
    auto start = high_resolution_clock::now();

    GeneradorController temp;
    Ciudadano ciudadano = temp.generarCiudadano();

    for (int i = 0; i < 10; i++)
    {
        ciudadano = temp.generarCiudadano();
    }

    cout << "DNI: " << ciudadano.getDNI() << " | " << ciudadano.getDNI().length() << endl;
    cout << "Nombres: " << ciudadano.getNombres() << " | " << ciudadano.getNombres().length() << endl;
    cout << "Apellidos: " << ciudadano.getApellidos() << " | " << ciudadano.getApellidos().length() << endl;
    cout << "Nacionalidad: " << ciudadano.getNacionalidad() << " | " << ciudadano.getNacionalidad().length() << endl;
    cout << "Lugar de Nacimiento: " << ciudadano.getLugarNacimiento() << " | " << ciudadano.getLugarNacimiento().length() << endl;
    cout << "Direccion: " << ciudadano.getDireccion() << " | " << ciudadano.getDireccion().length() << endl;
    cout << "Telefono: " << ciudadano.getTelefono() << " | " << ciudadano.getTelefono().length() << endl;
    cout << "Correo Electronico: " << ciudadano.getCorreoElectronico() << " | " << ciudadano.getCorreoElectronico().length() << endl;
    cout << "Estado Civil: " << ciudadano.getEstadoCivil() << " | " << ciudadano.getEstadoCivil().length() << endl;

    string linea = ciudadano.getDNI() + ";" +
                   ciudadano.getNombres() + ";" +
                   ciudadano.getApellidos() + ";" +
                   ciudadano.getNacionalidad() + ";" +
                   ciudadano.getLugarNacimiento() + ";" +
                   ciudadano.getDireccion() + ";" +
                   ciudadano.getTelefono() + ";" +
                   ciudadano.getCorreoElectronico() + ";" +
                   ciudadano.getEstadoCivil() + ";";

    cout << "Tamano registro: " <<  linea.size() << endl;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    cout << "El tiempo de ejecucion es de " << duration.count() << " microsegundos.\n";
    cin.get();

    return 0;
}