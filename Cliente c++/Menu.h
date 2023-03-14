#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Menu{
public:
  string ControlManual(string coordenadas);
  vector <string> ControlAutomatico();
  void Reporte(string coordenadas, int cant_comandos,int cant_errores,vector <string> estados,vector <string> comandos_enviados);

  string Homing();
  string MovimientoEfector();
  string MovimientoLineal();
  void MostrarComandos();
  string MovimientoCircular(string coordenadas);

private:
  string comando ="none";
  vector <string> comandos;

};

#endif /* MENU_H */