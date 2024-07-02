#include <iostream>
#include "../Controller/GeneradorController.cpp"
#include "../Model/CuckooHashTable.cpp"
#include "../Model/BinarySave.cpp"

using namespace std;

GeneradorController genController;
BinarySave binarySave;
CuckooHashTable indexTable;

void loadIndexTable()
{
    fstream file(RUTA_DATA, ios::in | ios::binary);
    if (!file.is_open())
    {
        cerr << "No se pudo abrir el archivo data.bin" << endl;
        return;
    }
    file.seekg(0, ios::end);
    streampos fileSize = file.tellg();
    cout << fileSize << endl;
    int numRegistros = fileSize / SIZE_REGISTRO;
    file.seekg(0, ios::beg);

    for (int i = 0; i < numRegistros; ++i)
    {
        file.seekg(i * SIZE_REGISTRO);
        int tamanoStr;
        file.read(reinterpret_cast<char *>(&tamanoStr), sizeof(tamanoStr));

        tamanoStr = 196;

        if (file.gcount() != sizeof(tamanoStr))
        {
            cerr << "Error reading tamanoStr at index " << i << " " << file.gcount() << endl;
            cin.get();
            continue;
        }

        vector<char> buffer(tamanoStr);
        file.read(buffer.data(), tamanoStr);

        if (file.gcount() != tamanoStr)
        {
            cerr << "Error reading registro at index " << i << " with expected size " << tamanoStr << endl;
            cin.get();
            continue;
        }

        string registro(buffer.begin(), buffer.end());
        vector<string> cut = Tools::splitString(registro, ';');
        int key = stoi(cut[0]);
        indexTable.insert(key, i);
    }

    file.close();
}

void generar(int numGenerar)
{
    fstream file(RUTA_DATA, ios::out | ios::app | ios::binary);
    if (!file.is_open())
    {
        cerr << "Fallo al abrir ../Data/data.bin \n";
        cin.get();
    }
    
    for (int i = 0; i < numGenerar; i++)
    {
        Ciudadano ciudadano = genController.generarCiudadano();
        try {
            int dni = stoi(ciudadano.getDNI());

            if (indexTable.search(dni).num != dni)
            {
                cout << i << "-" << dni << ": " << ciudadano.getNombres() << endl;
                binarySave.insert(ciudadano, file);
                indexTable.insert(dni, binarySave.getNumRegistros()-1);
                binarySave.addNumRegistros();
            }
            else
            {
                i--;
            }
        }
        catch (const invalid_argument &e) {
            cerr << "Error: invalid argument for stoi with value " << ciudadano.getDNI() << endl;
        }
        catch (const out_of_range &e) {
            cerr << "Error: out of range for stoi with value " << ciudadano.getDNI() << endl;
        }
    }
    
    file.close();
    cin.get();
}


int main()
{
    loadIndexTable();

    int opt;

    do
    {
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