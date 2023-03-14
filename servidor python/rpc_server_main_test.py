#!/usr/bin/python 
# -*- coding: utf-8 -*-

from rpc_server_test import XmlRpcEjemploServer
from rpc_objetoX import ObjetoX
from cmd_final import MyCmd
#from servidor_cmd import ServidorCmd
objeto_vinculado = ObjetoX()
work=input("Trabjo local o remoto? (l/r): ")
if work=="l":
    if __name__ == "__main__":
        consola = MyCmd()
        consola.prompt = '>> '
        consola.cmdloop("CLI-Servidor\nConsultar ayuda con 'help'")
        
else:
    if __name__ == "__main__":
        servidor = XmlRpcEjemploServer(objeto_vinculado)
        try:
            var=input("Ingrese 'salir' para terminar: \n")
            if var == "salir":
                servidor.shutdown()
            
        except KeyboardInterrupt:
            print("Servidor RPC finalizado")
            servidor.shutdown()
            exit(0)
