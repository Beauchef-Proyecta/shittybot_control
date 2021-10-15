import serial
import time
import sys

ser = serial


def init_config(param):
    global ser
    try:
        ser = serial.Serial(param, 9600, timeout=1)  # ojito con la ruta
        serial_port = "Open"
        print("The port is available")

    except serial.serialutil.SerialException:
        print("The port is at use")
        ser.close()
        ser.open()


def stepper_go(pos):
    global ser
    pos_data = str(int(pos))
    ser.write(('&1:' + pos_data).encode())


def stepper_go_home():
    global ser
    pos_data = str("")
    ser.write(('&2:' + pos_data).encode())


def main():
    args = sys.argv[1:]
    init_config(args[0])
    while True:
        selector = input("home or X?: ")
        if selector == "X":
            step_per_mm = 57
            x_val = int(input("X: "))
            x_val_mm = int(x_val * step_per_mm)
            stepper_go(x_val_mm)
        elif selector == "home":
            stepper_go_home()


if __name__ == '__main__':
    main()
