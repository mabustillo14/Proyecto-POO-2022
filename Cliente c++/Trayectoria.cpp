#include "Trayectoria.h"
#include <cstring> // for strlen

bool Trayectoria::esOrdenValida(string orden){

//Convertimos el string a una cadena de char
  auto c_orden = orden.c_str();


//Casos de orden invalida:
//no comienza con M o G
//hay caracteres invalidos
//el siguiente caracter de X,Y,Z es distinto de -
//el siguiente caracte de - es distinto de un nro
  

  //Cada comando G-CODE son minimo 2 caracteres y debe empezar con M o G
  if((orden.length()<2) //Minimo 2 caracteres
    ||(c_orden[0]!='M' && c_orden[0]!='G')){//Debe empezar con M o G
    return false; 
    } 
    else if(c_orden[orden.length()-1]=='M' || c_orden[orden.length()-1]=='G' || c_orden[orden.length()-1]=='X' || c_orden[orden.length()-1]=='Y' || c_orden[orden.length()-1]=='Z' || c_orden[orden.length()-1]=='F' || c_orden[orden.length()-1]=='-'
    ) //Ultimo caracter distinto de letra o  -
    {;
      return false; 
    }

    if(((c_orden[0]=='M') || (c_orden[0]=='G'))&&(c_orden[1]-'0'>9 ||c_orden[1]-'0'<0)){ //Despues de M o G debe haber un numero
    return false; 
    }  




  int longitud = orden.length()+1;
  for(int i=0;i<longitud;i++){
    if((c_orden[i]=='-')&&((c_orden[i-1]!='X')&&(c_orden[i-1]!='Y')&&(c_orden[i-1]!='Z'))){ //Antes del - debe haber un X, Y o Z
      return false; 
    }
     if((c_orden[i-1]=='-')&&(c_orden[i]-'0'>9 ||c_orden[i]-'0'<0)){ //Despues del - debe ir un numero
    return false; 
    }   
  
    for(int j=0; bool coincide=false; j++){ //Verificar caracteres
    int longitud = strlen(caracValidos);
      if(c_orden[i]==caracValidos[j]){
        coincide = true;
      }else if(j == longitud){
        return false;
      }
      }
  }
  return true;

}