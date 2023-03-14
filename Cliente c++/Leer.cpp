#include "Leer.h"
#include "Trayectoria.h"
#include <chrono> //Para poner la fecha y hora
#include <vector>
#include <fstream>
 Trayectoria * trayectoria = new Trayectoria;
//Leer el txt que contiene la secuencia


vector<string> Leer::read(string archivo){
    string line;
    string orden;  
    int contador = 0;
    vector<string> comandos;    
    ifstream myfile (archivo);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            //Por ahora orden es un string y no una lista.
            orden = line;
            contador +=1; 
            //Verifico si son correctos los comandos
          if(contador!=1 && orden!="none"){ //Asi no considero la linea con la fecha y la ultima linea
          if(trayectoria->esOrdenValida(orden)==true){
            comandos.push_back(orden);
            }
          else{
            std::cout<<"Comando G-Code invalido en la línea "<<contador<<std::endl;
          }
            }   
        }
        myfile.close();
    }

    else 
    {
        cout << "\nNo se pudo abrir el archivo..." << endl;
        cout << "Vuelva a intentarlo..." << endl;
        orden = "ERROR";
    }
  return comandos;
}

void Leer::crear_rutina(){
    ofstream fout;
    ifstream fin;
    string archivo, orden;
    cout << "Ingrese nombre del archivo a crear: " <<endl;
    cin >> archivo;
    
    int op=1;
    cout << endl << "Escriba GUARDAR una vez terminado de cargar de ordenes" << endl;
    cout << "Ingrese orden nueva: " << endl;

    //Para extraer la fecha y hora actual
    auto now = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(now);
 
    //Poner la fecha de creación al inicio del txt
    fin.open(archivo);
    fout.open(archivo,ios::app);
    fout << "Fecha de creación: " << ctime(&end_time);
    fin.close();
    fout.close();
    
    while (op==1){
        fin.open(archivo);
        fout.open(archivo,ios::app);
        cin >> orden;
    
        if ((orden != "GUARDAR")and(orden!="guardar")and(fin.is_open())){

            //Verificar que sea un comando valido
          if(trayectoria->esOrdenValida(orden)==true){
            fout << orden <<"\n";}
          else{
            std::cout<<"Comando invalido"<<std::endl;
          }
        }
        if ((orden == "GUARDAR")or(orden == "guardar")){
            op=0;
            fout <<"none";
            cout << "Rutina guardada exitosamente\n" <<endl;
        }
        fin.close();
        fout.close();
    }
}
