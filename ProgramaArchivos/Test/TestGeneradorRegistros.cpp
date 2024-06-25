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
    Ciudadano ciudadano = temp.generarCiudadano('0');

    cout << "DNI: " << ciudadano.getDNI() << endl;
    cout << "Nombres: " << ciudadano.getNombres() << endl;
    cout << "Apellidos: " << ciudadano.getApellidos() << endl;
    cout << "Nacionalidad: " << ciudadano.getNacionalidad() << endl;
    cout << "Lugar de Nacimiento: " << ciudadano.getLugarNacimiento() << endl;
    cout << "Direccion: " << ciudadano.getDireccion() << endl;
    cout << "Telefono: " << ciudadano.getTelefono() << endl;
    cout << "Correo Electronico: " << ciudadano.getCorreoElectronico() << endl;
    cout << "Estado Civil: " << ciudadano.getEstadoCivil() << endl;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    cout << "El tiempo de ejecucion es de " << duration.count() << " microsegundos.\n";

    return 0;
}