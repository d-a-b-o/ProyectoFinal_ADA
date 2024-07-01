#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "../Model/Ciudadano.cpp"
#include "../Model/BTree.cpp"
#include "../Model/BinarySave.cpp"
#include "../Tools/Tools.cpp"

using namespace std;

class MainController
{
private:
    BTree dniTree;
    BinarySave binarySave;
public:
    MainController();
    void run();
    void addCiudadano();
    void searchCiudadano();
    void deleteCiudadano();
    void loadBTree();
};