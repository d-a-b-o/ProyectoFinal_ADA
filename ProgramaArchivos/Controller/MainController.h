#pragma once

#include <string>
#include "../Model/Ciudadano.cpp"
#include "../Model/BTree.cpp"
#include "../Model/BinarySave.cpp"
#include "GeneradorController.cpp"

using namespace std;

class MainController
{
private:
    BTree dniTree;
    BinarySave binarySave;
    GeneradorController genController;
public:
    MainController();
    void run();
    void addCiudadano();
    void searchCiudadano();
    void deleteCiudadano();
    void generateRandom();
    void loadBTree();
};