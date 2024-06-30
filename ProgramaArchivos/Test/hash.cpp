#include <iostream>
using namespace std;
int main()
{
    int keys[] = {72804236, 72104237, 72304236, 92824236, 86804236};
    int tableSize = 70000000;

    for (int key : keys)
    {
        int index1 = key % tableSize;
        int index2 = key % (tableSize/2);
        cout << "Key: " << key << "-> Index: 1-" << index1 << " 2-" << index2 << endl;
    }

    return 0;
}
