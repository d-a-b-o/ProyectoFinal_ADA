#pragma once
#include "CuckooHashTable.h"

using namespace std;

const Node EMPTY_SPACE = Node();

size_t CuckooHashTable::calculateHash(const u_int32_t &key, int hash_number) const
{
    return (hash_fn(key) + hash_number * hash_fn(key) / tables[0].size()) % tables[hash_number].size();
}

void CuckooHashTable::rehash()
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
            insert(node.num, node.pos);
        }
    }
}

CuckooHashTable::CuckooHashTable(size_t initial_size = 1000)
{
    tables = vector(10, vector<Node>(initial_size, EMPTY_SPACE));
    current_size = 0;
}

int CuckooHashTable::getCurrentSize()
{
    return current_size;
}

void CuckooHashTable::insert(u_int32_t key, u_int32_t _pos)
{
    Node nodo = search(key);
    int count = 0;

    // Verificar si la clave ya existe
    if (nodo.num == key)
    {
        return;
    }

    if (current_size == tables[0].size() * 5)
    {
        rehash();
    }

    nodo.num = key;
    nodo.pos = _pos;
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

        if (nodo.numHash == 9)
            nodo.numHash = 0;
        else
            nodo.numHash++;
        count++;
    } while (count < MAX_CYCLES);

    rehash();
    insert(nodo.num, nodo.pos);
}

Node CuckooHashTable::search(const u_int32_t &key) const
{
    for (int i = 0; i < 10; ++i)
    {
        size_t pos = calculateHash(key, i);
        if (tables[i][pos].num == key)
        {
            return tables[i][pos];
        }
    }
    return Node();
}

void CuckooHashTable::remove(const u_int32_t &key)
{
    for (int i = 0; i < 10; i++)
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

void CuckooHashTable::replace(const u_int32_t &key, u_int32_t _pos)
{
    for (int i = 0; i < 10; i++)
    {
        size_t pos = calculateHash(key, i);
        if (tables[i][pos].num == key)
        {
            tables[i][pos].pos = _pos;
            return;
        }
    }
}