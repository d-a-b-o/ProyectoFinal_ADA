#pragma once
#include <string>
#include "../Model/Ciudadano.cpp"

using namespace std;

class MainController
{
private:
public:
    MainController();
    void run();
    void addCiudadano(const Ciudadano& ciudadano);
    void searchCiudadano(const string& dni);
    void deleteCiudadano(const string& dni);
    void generateRandom();
};