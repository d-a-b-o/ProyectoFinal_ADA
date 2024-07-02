#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "../Tools/Tools.cpp"

using namespace std;
using namespace std::chrono;

struct Node
{
    u_int32_t num = 0;
    u_int8_t numHash = 0;
    Node() : num(0), numHash(0) {}
};

const Node EMPTY_SPACE = Node();

class CuckooHashTable
{
private:
    static const int MAX_CYCLES = 500; // Máximo número de ciclos antes de duplicar el tamaño
    vector<vector<Node>> tables;
    hash<u_int32_t> hash_fn;
    size_t current_size;

    size_t calculateHash(const u_int32_t &key, int hash_number) const
    {
        return (hash_fn(key) + hash_number * hash_fn(key) / tables[0].size()) % tables[hash_number].size();
    }

    void rehash()
    {
        vector<vector<Node>> old_tables = tables;

        for (auto &table : tables)
        {
            int tableSize = table.size() * 2;
            table.clear();
            for (int i = 0; i < tableSize; i++)
                table.push_back(Node());
        }

        current_size = 0;

        for (const auto &table : old_tables)
        {
            for (const Node &node : table)
            {
                insert(node.num);
            }
        }
    }

public:
    CuckooHashTable(size_t initial_size = 11) 
        : tables(5, vector<Node>(initial_size, EMPTY_SPACE)), current_size(0) {}

    void insert(u_int32_t key)
    {
        Node nodo = search(key);
        int count = 0;

        // Verificar si la clave ya existe
        if (nodo.num == key)
        {
            return;
        }

        if (current_size >= tables[0].size()*2.5)
        {
            rehash();
        }

        nodo.num = key;
        do
        {
            size_t pos = calculateHash(nodo.num, nodo.numHash);
            Node temp = tables[nodo.numHash][pos];
            tables[nodo.numHash][pos] = nodo;
            nodo = temp;
            if (nodo.num == 0)
            {
                current_size++;
                return;
            }

            if (nodo.numHash == 4)
                nodo.numHash = 0;
            else
                nodo.numHash++;
            count++;
        } while (count < MAX_CYCLES);

        rehash();
        insert(nodo.num);
    }

    Node search(const u_int32_t &key) const
    {
        for (int i = 0; i < 5; ++i)
        {
            size_t pos = calculateHash(key, i);
            if (tables[i][pos].num == key)
            {
                return tables[i][pos];
            }
        }
        return Node();
    }

    void remove(const u_int32_t &key)
    {
        for (int i = 0; i < 5; i++)
        {
            size_t pos = calculateHash(key, i);
            if (tables[i][pos].num == key)
            {
                tables[i][pos] = Node();
                --current_size;
                return;
            }
        }

        cout << "Dni no registrado." << endl;
        cin.get();
    }

    void display() const
    {
        for (int i = 0; i < 5; i++)
        {
            cout << "Table " << i + 1 << ": ";
            for (const Node &node : tables[i])
            {
                cout << (node.num == 0 ? "-" : to_string(node.num)) << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    CuckooHashTable hashTable = CuckooHashTable();
    int num1 = Tools::getRandomNumber(0, 33000000);
    int num2 = Tools::getRandomNumber(0, 33000000);
    int num3 = Tools::getRandomNumber(0, 33000000);
    int num4 = Tools::getRandomNumber(0, 33000000);
    int num5 = Tools::getRandomNumber(0, 33000000);

    auto start = high_resolution_clock::now();

    for (int i = 0; i < 33000000; i++)
    {
        u_int32_t num = Tools::getRandomNumber(1000000, 99999999);
        hashTable.insert(num);
        if (i == num1)
            num1 = num;
        if (i == num2)
            num2 = num;
        if (i == num3)
            num3 = num;
        if (i == num4)
            num4 = num;
        if (i == num5)
            num5 = num;
    }
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "El tiempo de insercion de 33 millones es de " << duration.count() << " microsegundos.\n";

     start = high_resolution_clock::now();

    cout << "Buscando " << num1 << ": " << (hashTable.search(num1).num == num1 ? "Encontrado" : "No encontrado") << endl;
    
     stop = high_resolution_clock::now();
     duration = duration_cast<microseconds>(stop - start);

    cout << "El tiempo de busqueda es de " << duration.count() << " microsegundos.\n";

    cout << "Buscando " << num2 << ": " << (hashTable.search(num2).num == num2 ? "Encontrado" : "No encontrado") << endl;
    cout << "Buscando " << num3 << ": " << (hashTable.search(num3).num == num3 ? "Encontrado" : "No encontrado") << endl;
    cout << "Buscando " << num4 << ": " << (hashTable.search(num4).num == num4 ? "Encontrado" : "No encontrado") << endl;
    cout << "Buscando " << num5 << ": " << (hashTable.search(num5).num == num5 ? "Encontrado" : "No encontrado") << endl;

     start = high_resolution_clock::now();

    hashTable.remove(num2);

     stop = high_resolution_clock::now();
     duration = duration_cast<microseconds>(stop - start);

    cout << "El tiempo de eliminacion es de " << duration.count() << " microsegundos.\n";

    hashTable.remove(num4);
    hashTable.remove(num1);

    cout << "Eliminados: " << num2 << ", " << num4 << " y " << num1 << endl;

    cout << "Buscando " << num1 << ": " << (hashTable.search(num1).num == num1 ? "Encontrado" : "No encontrado") << endl;
    cout << "Buscando " << num2 << ": " << (hashTable.search(num2).num == num2 ? "Encontrado" : "No encontrado") << endl;
    cout << "Buscando " << num3 << ": " << (hashTable.search(num3).num == num3 ? "Encontrado" : "No encontrado") << endl;
    cout << "Buscando " << num4 << ": " << (hashTable.search(num4).num == num4 ? "Encontrado" : "No encontrado") << endl;
    cout << "Buscando " << num5 << ": " << (hashTable.search(num5).num == num5 ? "Encontrado" : "No encontrado") << endl;

    cin.get();

    return 0;
}
