from serial.tools.list_ports import comports
import serial
import re

class JoystickInput:
    def __init__(self):
        self.x = 0
        self.y = 0
        self.z = 0

class Inputs:
    def __init__(self):
        ports = comports(include_links=True)
        device = None
        for p in ports:
            if p.description is not None and "arduino" in p.description.lower():
                device = p.device

        if device is None:
            print("ERROR: No arduino found", len(ports), "ports seen")
        
        self.__ser = serial.Serial(device)

        self.joystick = JoystickInput()

    def update(self):
        lines = self.__ser.readlines()
        for line in lines:
            self.__read_command(line)
            print(line)

    def close(self):
        self.__ser.close()

    def __read_command(self, cmd:str):
        if cmd.startswith("JOYSTICK"):
            self.joystick.x = ("X+" in cmd) - ("X-" in cmd)
            self.joystick.y = ("Y+" in cmd) - ("Y-" in cmd)
            self.joystick.z = ("Z+" in cmd) - ("Z-" in cmd)
        

if __name__ == "__main__":
    inputs = Inputs()
    
    try:
        while True:
            inputs.update()
    except:
        inputs.close()