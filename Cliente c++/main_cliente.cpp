//Librerias importadas
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <chrono> //Para poner la fecha y hora
#include <cctype>
#include <algorithm>
#include <cstring>
using namespace std;
#include "XmlRpc.h"
using namespace XmlRpc;

//Clases diseñadas
#include "Leer.h"
#include "Trayectoria.h"
#include "Menu.h"

//Variables globales para el reporte
const char* ip_host;
int port;
int cant_comandos=0;
int cant_errores=0;
vector <string> estados;
vector <string> comandos_enviados;



int main(int argc, char* argv[])
{   //Generar Objetos dinamicos
    Trayectoria *trayecto = new Trayectoria();
    Menu *menu = new Menu;
    //Parametros
    string comando;
    string coordenadas;
    vector <string> vect_comando;


    //Variables Auxiliares
    int ej; //Numero de la Opcion que se va a realizar
    bool band = true; //Condicional para continuación de comandos
    int longitud;
    string comand;
    
    try{
        if(argc > 2){
            ip_host=argv[1];
            port = atoi(argv[2]);
            //XmlRpc::XmlRpcClient c(ip_host, port);
    }
    else{
      cout << "No se ha ingresado la ip del servidor y el puerto" << endl;
      return 0;
    }
        //Conexión de Cliente-Servidor
        XmlRpc::XmlRpcClient c(ip_host, port);
        XmlRpc::XmlRpcValue sinArgs, unArg, dosArgs, tresArg, resultado;

        while (band) {
        std::cout <<"\n==========================================="<<std::endl;
        std::cout << "                   ORDENES                  " << std::endl <<
        "1 - Control Automatico" << std::endl <<
        "2 - Control Manual" << std::endl <<
        "3 - Generar reporte" << std::endl <<
        "4 - Mostrar Comandos" << std::endl <<
        "5 - Verificar Comando" << std::endl <<  
        "6 - Conexión/Desconexión Arduino" << std::endl <<  
        "0 - Salir"<< std::endl;
        std::cout <<"==========================================="<<std::endl;
        std::cout << "Ingrese el número de orden a realizar: ";
            std::cin >> ej;
        switch (ej) {
        case (0): //Terminamos el bucle de solicitudes
                //Desconexión Arduino
                std::cout<<"\nDesconexión Arduino"<<endl;
                c.execute("desconectar", sinArgs, resultado);
                std::cout << resultado << "\n\n";
                //Desconexión con el Servidor
                std::cout<<"\nDesconexión con el Servidor"<<endl;
                std::cout<<"\nCliente desconectado"<<endl;
                band = false;
                break;
        
        case (1): //Control Automatico
                std::cout<< "ControlAutomatico();\n" <<std::endl;
                //Devuelve un vector
                vect_comando=menu->ControlAutomatico();
                longitud = vect_comando.size();         
                for(int j=0; j<longitud; j++){
                  cout<<"Ejecutando "<< vect_comando[j]<<endl;
                  comandos_enviados.push_back(vect_comando[j]);
                  c.execute("robot", vect_comando[j], resultado);
                  cout<<"\nRespuesta del Servidor:"<<endl;
                  std::cout << resultado << "\n\n";
                  if(resultado != "ERROR: POINT IS OUTSIDE OF WORKSPACE" || resultado!="ERROR: COMMAND NOT RECOGNIZED"){
                    cant_comandos +=1;
                    estados.push_back("Comando exitoso");
                 }else{
                    cant_errores +=1;
                    estados.push_back("Comando fallido");
                 }
                }      
                break;       
        case (2):  //Control Manual
                std::cout<< "ControlManual();\n" <<std::endl;
                //Devuelve un string
                comando = "M114"; //Saber las coordenadas actuales
                c.execute("robot", comando, resultado);
                 comando = menu->ControlManual(resultado);
                 c.execute("robot", comando, resultado);
                 comandos_enviados.push_back(comando);
                 cout<<"\nRespuesta del Servidor:"<<endl;
                 std::cout << resultado << "\n";
                 if(resultado != "ERROR: POINT IS OUTSIDE OF WORKSPACE" || resultado!="ERROR: COMMAND NOT RECOGNIZED"){
                    cant_comandos +=1;
                    estados.push_back("Comando exitoso");
                 }else{
                    cant_errores +=1;
                    estados.push_back("Comando fallido");
                 }
                break;              
        case (3): //Generar reporte actual
                std::cout<< "GenerarReporte();\n" <<std::endl;
                comando = "M114";
                c.execute("robot", comando, resultado);
                menu->Reporte(resultado, cant_comandos,cant_errores,estados, comandos_enviados);
                break;            
        case (4): //Mostrar Comandos
                std::cout<< "MostrarComandos();\n" <<std::endl;
                menu->MostrarComandos();
                break;           
        case (5): //Verificar Comandos
                std::cout <<"\n==========================================="<<std::endl;
                std::cout <<"                  Verificar Comando          "<<std::endl;
                std::cout<< "Ingrese el comando G-Code que quiere verificar: ";
                std::cin >> comando;
                trayecto->esOrdenValida(comando);
                break;
        case (6): //Conexión y Desconexión de Arduino
                int it;
                bool cond = true; //Condicional para continuación de comandos
                while (cond) {
                std::cout <<"==========================================="<<std::endl;
                std::cout << "      Movimiento del Efector              " << std::endl <<
                "1 - Conectarse al Arduino" << std::endl <<
                "2 - Desconectarse del Arduino" << std::endl <<
                "0 - Volver al Menu de Inicio"<< std::endl;
                std::cout <<"==========================================="<<std::endl;
                std::cout << "Ingrese el número de orden a realizar: ";
                 std::cin >> it;
                switch (it) {
                case (0): //Terminamos el bucle de solicitudes
                    cond = false;
                    std::cout << "\n"<<std::endl;
                break;
         
                case (1): //Conectarse al Arduino
                    c.execute("conectar", sinArgs, resultado);
                    std::cout << resultado << "\n";
                    cond = false;
                    break;
                case (2):  //Desconectarse del Arduino
                    c.execute("desconectar", sinArgs, resultado);
                    std::cout << resultado << "\n";
                    cond = false;
                break;   
                default: std::cout << "Orden NO válida, vuelva a intentarlo.\n" << std::endl;
                break;
    
                }
            }
        }
    } 
    std::cout << "Fin del programa - Funciona!\n";
    return 0;              
        }
        catch (XmlRpc::XmlRpcException& e) {
            std::cout << "Error: " << e.getMessage() << "\n";
        }
}



