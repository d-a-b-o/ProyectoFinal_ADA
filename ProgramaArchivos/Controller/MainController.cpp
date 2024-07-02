#pragma once
#include "MainController.h"

using namespace std;
using namespace std::chrono;

MainController::MainController()
{
    loadIndexTable();
}

void MainController::run()
{
    int opt;
    do
    {
        system("clear");
        cout << "=== MENU PRINCIPAL ===" << endl;
        cout << "[1] Ingresar ciudadano" << endl;
        cout << "[2] Buscar ciudadano" << endl;
        cout << "[3] Eliminar ciudadano" << endl;
        cout << "[0] Cerrar" << endl;
        cin >> opt;
        switch (opt)
        {
        case 1:
            addCiudadano();
            break;
        case 2:
            searchCiudadano();
            break;
        case 3:
            deleteCiudadano();
            break;
        case 4:
            viewMemoryUsage();
            break;
        default:
            break;
        }

    } while (opt != 0);
}

void MainController::addCiudadano()
{
    string dni, nombres, apellidos, nacionalidad, lugarNacimiento, direccion, telefono, correoElectronico, estadoCivil;

    system("clear");
    cin.ignore();
    cout << "=== AGREGAR CIUDADANO ===" << endl;
    cout << "Ingrese DNI: " << endl;
    getline(cin, dni);

    if (indexTable.search(stoi(dni)).num == stoi(dni))
    {
        cout << "Ciudadano ya registrado." << endl;
        cin.get();
        return;
    }

    cout << "Ingrese nombres: " << endl;
    getline(cin, nombres);
    cout << "Ingrese apellidos: " << endl;
    getline(cin, apellidos);
    cout << "Ingrese nacionalidad: " << endl;
    getline(cin, nacionalidad);
    cout << "Ingrese lugar de nacimiento: " << endl;
    getline(cin, lugarNacimiento);
    cout << "Ingrese dirección: " << endl;
    getline(cin, direccion);
    cout << "Ingrese teléfono: " << endl;
    getline(cin, telefono);
    cout << "Ingrese correo electrónico: " << endl;
    getline(cin, correoElectronico);
    cout << "Ingrese estado civil: " << endl;
    getline(cin, estadoCivil);

    auto start = high_resolution_clock::now();

    Ciudadano nuevoCiudadano(dni, nombres, apellidos, nacionalidad, lugarNacimiento, direccion, telefono, correoElectronico, estadoCivil);
    indexTable.insert(stoi(dni), indexTable.getCurrentSize());
    binarySave.save(nuevoCiudadano);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "El tiempo de insercion es de " << duration.count() << " microsegundos.\n";
    cin.get();
}

void MainController::searchCiudadano()
{
    string dni;

    system("clear");
    cin.ignore();
    cout << "=== BUSCAR CIUDADANO ===" << endl;
    cout << "Ingrese DNI: " << endl;
    getline(cin, dni);

    auto start = high_resolution_clock::now();

    Node busqueda = indexTable.search(stoi(dni));

    if (busqueda.num != stoi(dni))
    {
        cout << "Ciudadano no encontrado." << endl;
        cin.get();
        return;
    }

    Ciudadano ciudadano;
    ciudadano = binarySave.buscar(busqueda.pos);
    cout << "=== DETALLES DEL CIUDADANO ===" << endl;
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

    cout << "El tiempo de busqueda es de " << duration.count() << " microsegundos.\n";
    cin.get();
}

void MainController::deleteCiudadano()
{
    string dni;

    system("clear");
    cin.ignore();
    cout << "=== ELIMINAR CIUDADANO ===" << endl;
    cout << "Ingrese DNI: " << endl;
    getline(cin, dni);

    auto start = high_resolution_clock::now();

    Node busqueda = indexTable.search(stoi(dni));

    if (busqueda.num != stoi(dni))
    {
        cout << "Ciudadano no encontrado." << endl;
        cin.get();
        return;
    }

    binarySave.erase(busqueda.pos);
    indexTable.remove(busqueda.num);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "El tiempo de eliminacion es de " << duration.count() << " microsegundos.\n";
    cin.get();
}

void MainController::loadIndexTable()
{
    fstream file(RUTA_DATA, ios::in | ios::binary);
    if (!file.is_open())
    {
        cerr << "No se pudo abrir el archivo data.bin" << endl;
        return;
    }
    file.seekg(0, ios::end);
    streampos fileSize = file.tellg();
    int numRegistros = fileSize / SIZE_REGISTRO;
    file.seekg(0, ios::beg);

    for (int i = 0; i < numRegistros; ++i)
    {
        file.seekg(i * SIZE_REGISTRO);
        int tamanoStr;
        file.read(reinterpret_cast<char *>(&tamanoStr), sizeof(tamanoStr));

        vector<char> buffer(tamanoStr);
        file.read(buffer.data(), tamanoStr);

        string registro(buffer.begin(), buffer.end());
        vector<string> cut = Tools::splitString(registro, ';');
        try
        {
            if (!cut.empty())
            {
                indexTable.insert(stoi(cut[0]), i);
            }
        }
        catch(const std::exception& e){}
    }

    file.close();
}

void MainController::viewMemoryUsage()
{
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    cout << "Memory usage: " << usage.ru_maxrss << " kilobytes" << endl;
    cin.get();
}