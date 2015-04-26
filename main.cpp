#include <iostream>
#include <string>
#include "MarkovChain.h"
using namespace std;

void printMenu()
{

}

int main()
{
    MarkovChain mC;
    mC.generateFromFile("testFile1.txt");

    return 0;
}
