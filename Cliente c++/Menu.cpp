//Clases diseñadas
#include "Leer.h"
#include "Menu.h"

#include <cstring> // for strlen
#include <cmath>
#include <cctype>
#include <algorithm>
#include <string>
#include <cstdlib>

//Generar Objetos Dinamicos
Leer *lectura = new Leer();

string Menu::ControlManual(string coordenadas){
  int ej; //Numero de la Opcion que se va a realizar
    bool band = true; //Condicional para continuación de comandos
    while (band) {
        std::cout <<"==========================================="<<std::endl;
        std::cout << "                 MODO MANUAL              " << std::endl <<
        "1 - Movimiento Circular" << std::endl <<
        "2 - Movimiento Lineal" << std::endl <<
        "3 - Accionar Efector" << std::endl <<  
        "4 - Homing" << std::endl <<
        "5 - Modo Aprendizaje" << std::endl <<
        "6 - Mostrar Comandos" << std::endl <<
        "0 - Volver al Menu de Inicio"<< std::endl;

        std::cout <<"==========================================="<<std::endl;
        std::cout << "Ingrese el número de orden a realizar: ";
            std::cin >> ej;
        switch (ej) {
        case (0): //Terminamos el bucle de solicitudes
                band = false;
                break;

        case (1): //Movimiento Circular
                std::cout<< "MovimientoCircular();\n" <<std::endl;
         
                comando = MovimientoCircular(coordenadas);
                band = false;
                break;
    
        case (2):  //Movimiento Lineal
                //std::cout<< MovimientoLineal() <<std::endl;
                //MovimientoLineal();
                comando = MovimientoLineal();
                band = false;
                break;
        case (3):  //Movimiento del Efector
                //std::cout<< MovimientoEfector() <<std::endl;
                comando = MovimientoEfector();
                band = false;
                break;
        case (4): //Homing
                //std::cout<< Homing() <<std::endl;
                comando = Homing();
                band = false;
                break;
                
        case (5): //Modo Aprendizaje
                std::cout<< "ModoAprendizaje()\n" <<std::endl;
                lectura->crear_rutina();
                band = false;
                break;
        case (6): //Mostrar Comandos
                //std::cout<< "MostrarComandos();\n" <<std::endl;
                MostrarComandos();
                break;
        default: std::cout << "Orden NO válida, vuelva a intentarlo." << std::endl;
          break;
        }
    } 
  return comando;
}




vector <string> Menu::ControlAutomatico(){
  vector <string> comandos;
  int ej; //Numero de la Opcion que se va a realizar
  string archivo; //Nombre del archivo
  string orden; //Comando que se envia
    bool band = true; //Condicional para continuación de comandos
    while (band) {
        std::cout <<"==========================================="<<std::endl;
        std::cout << "             MODO AUTOMATICO              " << std::endl <<
        "1 - Cargar rutina" << std::endl <<
        "0 - Volver al Menu de Inicio"<< std::endl;

        std::cout <<"==========================================="<<std::endl;
        std::cout << "Ingrese el número de orden a realizar: ";
            std::cin >> ej;
        switch (ej) {
        case (0): //Terminamos el bucle de solicitudes
                band = false;
                break;
  
        case (1): //Cargar rutina
                std::cout<< "CargarRutina();\n" <<std::endl;
                std::cout << "Ingrese archivo para leer: " << std::endl;
                std::cin >> archivo;
                comandos=lectura->read(archivo);
                band = false;
                break;
     
        default: std::cout << "Orden NO válida, vuelva a intentarlo.\n" << std::endl;
        break;
        }
    } 
  return comandos;
}



string Menu::Homing(){
  comando = "G28";
  return comando;
}


string Menu::MovimientoEfector(){
  int ej;
  bool band = true; //Condicional para continuación de comandos
    while (band) {
        std::cout <<"==========================================="<<std::endl;
        std::cout << "      Movimiento del Efector              " << std::endl <<
        "1 - Abrir Gripper" << std::endl <<
        "2 - Cerrar Gripper" << std::endl <<
        "0 - Volver al Menu de Inicio"<< std::endl;

        std::cout <<"==========================================="<<std::endl;
        std::cout << "Ingrese el número de orden a realizar: ";
            std::cin >> ej;
        switch (ej) {
        case (0): //Terminamos el bucle de solicitudes
                comando = "none";      
                band = false;
                std::cout << "\n"<<std::endl;
                break;
         
        case (1): //Abrir Gripper
                comando = "M3";
                band = false;
                break;
         
        case (2):  //Cerrar Gripper
                comando = "M5";
                band = false;
                break;       
        default: std::cout << "Orden NO válida, vuelva a intentarlo.\n" << std::endl;
          break;
        }
    }
return comando;
}

string Menu::MovimientoLineal(){
  int X,Y,Z; //Posicion del brazo 
  int v=0; //Velocidad de ejecución
  
  std::cout <<"==========================================="<<std::endl;
  std::cout <<"              Movimiento Lineal            " << std::endl;
  std::cout<<"\nIngrese las coordenadas de la posición Final [mm]\n"<<std::endl;
  std::cout << "X: "; 
  std::cin >> X;
  std::cout << "Y: "; 
  std::cin >> Y;
  std::cout << "Z: "; 
  std::cin >> Z;
  while(v<=0){ //Verificamos que la velocidad sea positiva
    std::cout<<"\nIngrese la velocidad de desplazamiento [mm/s]\n";
    std::cin >> v;
  }
  //Convertimos los datos al string de comando
  comando = "G0X"+to_string(X)+"Y"+to_string(Y)+"Z"+to_string(Z)+"F"+to_string(v);
  return comando;
}

void Menu::MostrarComandos(){
  std::cout <<"==========================================="<<std::endl;
  std::cout <<"              Lista de Comandos            " << std::endl;
  std::cout << "M3 : Activar Gripper" << std::endl;
  std::cout << "M5 : Desactivar Gripper" << std::endl;
  std::cout << "G28 : Homing" << std::endl;
  std::cout << "G0XaYbZcFv : Posición (a,b,c) a una velocidad v" << std::endl;
  std::cout << "G4Sb : Esperar b segundos" << std::endl;
  std::cout << "M114: Posicion actual" << std::endl;
  std::cout << "M119 Estado de los endstops" << std::endl;
  std::cout << "M17 Activa los motores" << std::endl;
  std::cout << "M18 Desactiva los motores" << std::endl;
  std::cout << "M999 Reanuda el movimiento" << std::endl;
  std::cout << "G90 Movimiento absoluto" << std::endl;
  std::cout << "G91 Movimiento relativo" << std::endl;
  std::cout << "G92 Establece la posicion actual como (0,0,0)" << std::endl;
  std::cout <<"==========================================="<<std::endl;
}


string Menu::MovimientoCircular(string coordenadas){
  int longitud = coordenadas.length()+1;
  vector<int> vect_posi;
  coordenadas.erase(remove_if(coordenadas.begin(), coordenadas.end(), ::isspace), coordenadas.end());

   //Convertimos el string a una cadena de char
  auto c_coordenadas = coordenadas.c_str();


    //Buscamos la posicion de los :
  for(int j=0; j<longitud; j++){
    if(c_coordenadas[j] ==':' || c_coordenadas[j] =='X' || c_coordenadas[j] =='Y' || c_coordenadas[j] =='Z'){
      vect_posi.push_back(j);
      //cout<<j<<endl;
    }
  }

  //Posicion x,y actual del brazo en string
  string var_x = coordenadas.substr(vect_posi[4]+1, vect_posi[5]-vect_posi[4]-1);
  string var_y = coordenadas.substr(vect_posi[6]+1, vect_posi[7]-vect_posi[6]-1);
  
  //Convierto la posicion del brazo string a char
  auto c_coordenadas_x = var_x.c_str();
  auto c_coordenadas_y = var_y.c_str();

  //Convierto la posicion del brazo char a float
  float x = atof(c_coordenadas_x);
  float y = atof(c_coordenadas_y);

  //parametros que se piden al usuario
    int angulo = 0;
    string sentido ;
    int velocidad = 0;
    bool fin=true;

  //Pedimos los parametros faltantes al usuario
  std::cout <<"==========================================="<<std::endl;
  std::cout <<"            Movimiento Circular            " << std::endl;
  std::cout<<"Ingrese el ángulo de rotación: ";
  std::cin >> angulo;
  while (fin==true){
  std::cout<<"Ingrese el sentido de rotación: (HORARIO/ANTIHORARIO): ";
  std::cin >> sentido;
  if(sentido!="HORARIO" && sentido!="ANTIHORARIO" ){
    std::cout<<"Parametro Invalido"<<std::endl;
  }else{
    fin = false;
  }
  }
  std::cout<<"Ingrese la velocidad de rotación: ";
  std::cin >> velocidad;

  float radio= sqrt((x*x)+(y*y));
  float angulo_nuevo;
  if(sentido =="ANTIHORARIO"){
    angulo_nuevo = angulo; 
  }
  else if(sentido=="HORARIO"){
    angulo_nuevo = -angulo; 
  }
  int x_nuevo = radio*cos(angulo_nuevo);
  int y_nuevo = radio*sin(angulo_nuevo);
  comando = "G0X"+ to_string(x_nuevo) + "Y" + to_string(y_nuevo) + "F" + to_string(velocidad);
  std::cout << comando<<"\n"<<std::endl; 
  return comando;
}



void Menu::Reporte(string coordenadas, int cant_comandos,int cant_errores,
vector <string> estados,
vector <string> comandos_enviados){
  int longitud = coordenadas.length()+1;
  vector<int> vect_posi;

  coordenadas.erase(remove_if(coordenadas.begin(), coordenadas.end(), ::isspace), coordenadas.end());

   //Convertimos el string a una cadena de char
  auto c_coordenadas = coordenadas.c_str();
        //Buscamos la posicion de los []
  for(int j=0; j<longitud; j++){
    if(c_coordenadas[j] =='[' || c_coordenadas[j] ==']'){
      vect_posi.push_back(j);
    }
  }

string coor = coordenadas.substr(vect_posi[0]+1, vect_posi[1]-vect_posi[0]-1-6);
    std::cout <<"\n==========================================="<<std::endl;
    std::cout << "                   REPORTE                  " << std::endl;
    std::cout <<"Coordenadas Actuales: "<<coor<<std::endl;
    std::cout<<"Cantidad de Comandos Enviados: "<< cant_comandos + cant_errores <<std::endl;
    std::cout<<"Cantidad de Comandos Exitosos: "<< cant_comandos<<std::endl;
    std::cout<<"Cantidad de Comandos con Errores: "<< cant_errores<<std::endl;

    if(comandos_enviados.empty()==false){ //Verificamos que el vector no este vacío
        longitud = cant_comandos + cant_errores-1;
        std::cout<<"Ultimo comando enviado: "<< comandos_enviados[longitud]<<std::endl;
        std::cout<<"Estado de la última operación: "<<estados[longitud]<<std::endl;
    }else{
        std::cout<<"Aun no se envía ningún comando"<<std::endl;
    }
}