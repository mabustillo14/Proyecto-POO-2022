from comunicación_arduino import Arduino
from rpc_server_test import XmlRpcEjemploServer
class ObjetoX():

    def __init__(self):
        
        self.arduino=None
        
    def conectar(self):
        self.arduino=Arduino("/dev/ttyUSB0",115200)
        #print("Arduino Conectado")
        return "Arduino conectado"    

    def robot(self, gcode):
       print
       print(self.arduino.send(gcode))
       return "\n"+self.arduino.send(gcode)+"\n"
    
    def desconectar(self):
        self.arduino.close()
        #print("Arduino desconectado")
        return "Arduino desconectado"
    

    