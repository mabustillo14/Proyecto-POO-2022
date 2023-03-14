#ifndef TRAYECTORIA_H
#define TRAYECTORIA_H

#include <iostream>
#include <string>
using namespace std;

class Trayectoria{
public:
     bool esOrdenValida(string orden);
private:
  string orden;
    const char* caracValidos = "MG1234567890-XYZF.S";
};

#endif /* TRAYECTORIA_H */

