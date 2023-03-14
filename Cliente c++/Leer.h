#ifndef LEER_H
#define LEER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Leer{
public:
    vector<string> read(string txt);
    void crear_rutina();
private:
    string orden;
    
};

#endif /* LEER_H */

