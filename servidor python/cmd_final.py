from cmd import Cmd

from rpc_server_test import XmlRpcEjemploServer

#from servidor_cmd import ServidorCmd
from rpc_objetoX import ObjetoX
import sys

class MyCmd(Cmd):
    def __init__(self):
        Cmd.__init__(self)
        self.servicios = ObjetoX()
        self.rpc_server = None
    def do_start(self, line):
        """secuencia para iniciar/terminar el servidor RPC\nConectar/Desconectar el arduino"""
        list=["rcp true","conectar","desconectar","dead"]
        for i in list:
            print(i)

    def do_rcp(self, value):
        """Inicia el servidor RPC según el valor de value true"""
        if value:
            if self.rpc_server is None:
                self.rpc_server = XmlRpcEjemploServer(self.servicios)
                
                 
    def do_dead(self, line):
        """Funcion/servicio: desconectar el servidor RPC"""
        self.rpc_server.shutdown()
        return print("El servidor RPC ya está apagado")
    
    def do_exit(self,line):
        '''Exit the console.'''
        sys.exit(0)
    
    def do_conectar(self, line):
        """Funcion/servicio: conectar el arduino"""
        return print(self.rpc_server.do_conectar())
    
    def do_desconectar(self, line):
        """Funcion/servicio: desconectar el arduino"""
        return print(self.rpc_server.do_desconectar())
    
    def do_robot(self, gcode):
        """Funcion/servicio: enviar datos al arduino
                Comandos gcode:
                    G0 X0 Y0 Z0 F1000
                    G1 X0 Y0 Z0 F1000 posicion (a,b,c) y velocidad de movimiento f
                    M3 Activa gripper
                    M5 Desactiva gripper
                    G28 Homing
                    M114 Posicion actual
                    M119 Estado de los endstops
                    M17 Activa los motores
                    M18 Desactiva los motores
                    M999 Reanuda el movimiento
                    G90 Movimiento absoluto
                    G91 Movimiento relativo
                    G92 Establece la posicion actual como (0,0,0)
                    G4 sb Espera b segundos


                Ejemplo:

                robot G0 X0 Y0 Z0 F1000
                robot G1 X0 Y0 Z0 F1000
                robot M3
                robot M5
                robot G28
                robot M114
                robot M119
                robot M17
                robot M18
                robot M999
                robot G90
                robot G91
                robot G92
                robot G4 s5"""
        self.rpc_server.do_robot(gcode)
        return print("Comando enviado")

