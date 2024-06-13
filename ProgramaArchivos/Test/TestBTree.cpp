#include <iostream>
#include "../Model/BTree.cpp"
#include "../Tools/GeneradorRegistros.cpp"
#include <chrono>

using namespace std;
using namespace std::chrono;

void test(BTree t, int num)
{
    cout << "Existe el " << num << " dentro del arbol?\n";

    if (t.search(num))
    {
        cout << "Si existe";
    }
    else
    {
        cout << "No existe";
    }

    cout << " \n";

    cout << "Retirando: " << num << "\n";

    t.remove(num);

    cout << "Existe el " << num << " dentro del arbol?\n";

    if (t.search(num))
    {
        cout << "Si existe";
    }
    else
    {
        cout << "No existe";
    }

    cout << " \n";
}

int main()
{
    int objetivoRand1;
    int objetivoRand2;
    int dni;
    int count = 0;
    int i = 0;
    BTree t(25);

    auto start = high_resolution_clock::now();

    while (i < 3300000)
    {
        dni = GeneradorRegistros::generarDNIAleatorio();

        if (!t.search(dni) && dni > 9999999)
        {
            t.insert(dni);
            i++;
            if (i == 2371993)
                objetivoRand1 = dni;
            if (i == 2692013)
                objetivoRand2 = dni;
        }
        else
            count++;
    }
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    
    cout << "El tiempo de ejecucion es de " << duration.count() << " segundos.\n";
    cout << "Repetidos: " << count << "\n";

    if (!t.search(72804236))
        t.insert(72804236);
    
    test(t, 72804236);

    test(t, objetivoRand1);

    test(t, objetivoRand2);
    return 0;
}