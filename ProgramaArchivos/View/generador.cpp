#include <iostream>
#include "../Controller/GeneradorController.cpp"
#include "../Model/BinarySave.cpp"
#include "../Model/BTree.cpp"

using namespace std;

GeneradorController genController;
BinarySave binarySave;
BTree dniTree(25);

void loadBTree()
{
    fstream indexFile("../Data/index.csv", ios::in);
    if (!indexFile.is_open())
    {
        cerr << "Fallo al abrir ../Data/index.csv \n";
        cin.get();
    }

    string linea;

    while (getline(indexFile, linea))
    {
        stringstream ss(linea);
        string dniStr;
        getline(ss, dniStr, ',');
        dniTree.insert(stoi(dniStr));
        binarySave.addNumRegistros();
    }
    indexFile.close();
}

void generar(int numGenerar)
{
    fstream file("../Data/data.bin", ios::out | ios::app | ios::binary);
    if (!file.is_open())
    {
        cerr << "Fallo al abrir ../Data/data.bin \n";
        cin.get();
    }
    
    fstream indexFile("../Data/index.csv", ios::in | ios::out | ios::app);
    if (!indexFile.is_open())
    {
        cerr << "Fallo al abrir ../Data/index.csv \n";
        cin.get();
    }
    
    for (int i = 0; i < numGenerar; i++)
    {
        Ciudadano ciudadano = genController.generarCiudadano();
        int dni = stoi(ciudadano.getDNI());

        if (!dniTree.search(dni))
        {
            dniTree.insert(dni);
            binarySave.insert(ciudadano, file, indexFile);
            binarySave.addNumRegistros();
        }
    }
    
    file.close();
    indexFile.close();
    cin.get();
}

int main()
{
    loadBTree();

    int opt;

    do
    {
        system("clear");
        cout << "======= MENU GENERADOR =======" << endl;
        cout << " [1] Generar 1000" << endl;
        cout << " [2] Generar 10000" << endl;
        cout << " [3] Generar 100000" << endl;
        cout << " [4] Generar 1000000" << endl;
        cout << " [5] Generar 10000000" << endl;
        cout << " [6] Generar 33000000" << endl;
        cout << " [0] Cerrar" << endl;
        cout << "           >";
        cin >> opt;

        switch (opt)
        {
        case 1:
            generar(1000);
            break;
        case 2:
            generar(10000);
            break;
        case 3:
            generar(100000);
            break;
        case 4:
            generar(1000000);
            break;
        case 5:
            generar(10000000);
            break;
        case 6:
            generar(33000000);
            break;
        default:
            break;
        }
    } while (opt != 0);

    cin.get();
}