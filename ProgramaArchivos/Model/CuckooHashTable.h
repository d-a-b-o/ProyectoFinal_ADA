#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node
{
    u_int32_t num = 0;
    u_int32_t pos = 0;
    u_int8_t numHash = 0;
    Node() : num(0), numHash(0) {}
};

class CuckooHashTable
{
private:
    static const int MAX_CYCLES = 500;
    vector<vector<Node>> tables;
    hash<u_int32_t> hash_fn;
    size_t current_size;
    size_t calculateHash(const u_int32_t &key, 
                        int hash_number)const;
    void rehash();
public:
    CuckooHashTable(size_t initial_size);
    int getCurrentSize();
    void insert(u_int32_t key, u_int32_t _pos);
    Node search(const u_int32_t &key)const;
    void remove(const u_int32_t &key);
};