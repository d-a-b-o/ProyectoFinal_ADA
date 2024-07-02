#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <sys/resource.h>
#include "../Model/Ciudadano.cpp"
#include "../Model/CuckooHashTable.cpp"
#include "../Model/BinarySave.cpp"
#include "../Tools/Tools.cpp"

using namespace std;

class MainController
{
private:
    CuckooHashTable indexTable;
    BinarySave binarySave;
public:
    MainController();
    void run();
    void addCiudadano();
    void searchCiudadano();
    void deleteCiudadano();
    void loadIndexTable();
    void viewMemoryUsage();
};