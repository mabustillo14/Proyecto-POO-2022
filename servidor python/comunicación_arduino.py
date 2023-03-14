#comunicar el serial de un arduino con python
import serial

class Arduino:
    def __init__(self, port, baudrate):
        self.port =port
        self.baudrate = baudrate
        self.timeout = 1
        self.serialport = serial.Serial(port=self.port, baudrate=self.baudrate, timeout=self.timeout)
    def send(self, data):
        
        self.serialport.flushInput()
        self.serialport.write(bytes(data+"\n\r",'utf-8'))
        respuesta=self.serialport.read_until(b'ok').decode('utf-8')
        return respuesta

    def recive(self):
        self.serialport.flushInput()
        respuesta=self.serialport.read_until(b'ok').decode('utf-8')
        print(f"respuesta={respuesta}")
        return respuesta


    def close(self):
        self.serialport.close()