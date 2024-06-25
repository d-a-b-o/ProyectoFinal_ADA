#include <iostream>
#include <fstream>
#include <vector>
#include "../Model/BinarySave.cpp"
#include "../Controller/GeneradorController.cpp"
#include <chrono>

GeneradorController gen;
BinarySave dat;

using namespace std;
using namespace std::chrono;

int main()
{
    Ciudadano busqueda;
    auto start = high_resolution_clock::now();

    dat.generateRandom('0');

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    
    cout << "El tiempo de ejecucion es de " << duration.count() << " segundos.\n";

    int num;

    cout << "Ingrese la posicion a buscar: ";
    cin >> num;

    busqueda = dat.buscar(num);

    cout << busqueda.getDNI() << endl;
    cout << busqueda.getNombres() << endl;
    cout << busqueda.getApellidos() << endl;
    cout << busqueda.getNacionalidad() << endl;
    cout << busqueda.getLugarNacimiento() << endl;
    cout << busqueda.getDireccion() << endl;
    cout << busqueda.getTelefono() << endl;
    cout << busqueda.getCorreoElectronico() << endl;
    cout << busqueda.getEstadoCivil() << endl;

    return 0;
}