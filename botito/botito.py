import serial
import time

#BLOQUE SERIAL
ser = serial
try:
    ser = serial.Serial("COM3", 9600, timeout=1) #ojito con la ruta
    serial_port = "Open"
    print("The port is available")

except serial.serialutil.SerialException:
    print("The port is at use")
    ser.close()
    ser.open()
#BLOQUE SERIAL


def stepper_go(pos):
    posData = str(int(pos))
    ser.write(('&1:' + posData).encode())

def stepper_go_home():
    posData = str("")
    ser.write(('&2:' + posData).encode())



while True:
    selector= input("home or X?: ")
    if selector=="X":
        Xval = int(input("X: "))
        stepper_go(Xval)
    elif selector == "home":
        stepper_go_home()
