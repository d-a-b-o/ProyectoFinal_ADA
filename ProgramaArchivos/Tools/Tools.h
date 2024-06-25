#pragma once

#include <string>
#include <vector>

// Herramientas de uso general
class Tools
{
public:
    static int getRandomNumber(int desde, int hasta);
    static string selectRandomElement(const vector<string> &elements);
    static vector<string> splitString(string &str, char delimiter);
};