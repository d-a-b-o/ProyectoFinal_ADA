#include <iostream>
#include "../Controller/MainController.cpp"
#include "../Model/BinarySave.cpp"

using namespace std;
BinarySave bin;

int main()
{
    MainController mainController;
    mainController.run();
    return 0;
}