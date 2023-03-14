#!/usr/bin/python 
# -*- coding: utf-8 -*-

from cmd import Cmd
from xmlrpc.server import SimpleXMLRPCServer
from threading import Thread
import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect(("8.8.8.8", 80))

class XmlRpcEjemploServer(Cmd):
    server = None
    RPC_PORT = 8891

    def __init__(self, objeto_vinculado, port = RPC_PORT):
        self.objeto_vinculado = objeto_vinculado
        self.puerto_usado = port
        self.server_forever = self.run_server
        while True:
            try:
                #Creacion del servidor indicando el puerto deseado
                self.server = SimpleXMLRPCServer((s.getsockname()[0], self.puerto_usado), allow_none = True, logRequests = False)
                if self.puerto_usado != port:
                    print("Servidor RPC ubicado en puerto no estándar [%d]" % self.puerto_usado)
                break
            except socket.error as e:
                if e.errno == 98:
                    self.puerto_usado += 1
                    continue
                else:
                    print("El servidor RPC no puede ser iniciado")
                    raise

        #Se registra cada funcion
        self.server.register_function(self.do_robot, 'robot')
        self.server.register_function(self.do_conectar, 'conectar')
        self.server.register_function(self.do_desconectar, 'desconectar')

        
        #Se lanza el servidor
        self.thread = Thread(target = self.run_server)
        self.thread.start()
        print("Servidor RPC iniciado en el puerto [%s]" % str(self.server.server_address))

    def run_server(self):
        self.server.serve_forever()

    def shutdown(self):
        self.server.shutdown()
        self.thread.join()

    def do_conectar(self):
        # Funcion/servicio: conectar el arduino
        return self.objeto_vinculado.conectar()

    def do_desconectar(self):
        # Funcion/servicio: desconectar el arduino
        return self.objeto_vinculado.desconectar()

    def do_robot(self, gcode):
        # Funcion/servicio: enviar datos al arduino
        return self.objeto_vinculado.robot(gcode)
    