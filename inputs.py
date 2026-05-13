from serial.tools.list_ports import comports
import serial
from datetime import datetime

class JoystickInput:
    def __init__(self):
        self.x = 0
        self.y = 0
        self.z = 0
        self.timestamp:datetime = 0

class PlanetEncoderInput:
    def __init__(self):
        self.planet = 2
        self.update_flag = False

class AudioInput:
    def __init__(self):
        self.audio_cmds:list[str] = []

class Inputs:
    def __init__(self):
        ports = comports(include_links=True)
        device = None
        for p in ports:
            if p.description is not None and "arduino" in p.description.lower():
                device = p.device
            if p.manufacturer is not None and "arduino" in p.manufacturer.lower():
                device = p.device
            if p.product is not None and "arduino" in p.product.lower():
                device = p.device
            if p.name is not None and "arduino" in p.name.lower():
                device = p.device
            if p.hwid is not None and "arduino" in p.hwid.lower():
                device = p.device
            if p.interface is not None and "arduino" in p.interface.lower():
                device = p.device

        if device is None:
            print("ERROR: No arduino found", len(ports), "ports seen")
        
        self.__ser = serial.Serial(device)

        self.joystick = JoystickInput()
        self.planet_encoder = PlanetEncoderInput()
        self.audio = AudioInput()

    def update(self):       
        while self.__ser.in_waiting:
            line = self.__ser.readline()
            self.__read_command(line)
            print(line)

        self.audio.audio_cmds = []

        # Joystick timeout
        t_since_update = (datetime.now() - self.joystick.timestamp).total_seconds()
        if t_since_update > 1:
            self.joystick.x = 0
            self.joystick.y = 0
            self.joystick.z = 0

    def close(self):
        self.__ser.close()

    def __read_command(self, cmd:str):
        if cmd.startswith("JOYSTICK"):
            self.joystick.x = ("X+" in cmd) - ("X-" in cmd)
            self.joystick.y = ("Y+" in cmd) - ("Y-" in cmd)
            self.joystick.z = ("Z+" in cmd) - ("Z-" in cmd)
            self.joystick.timestamp = datetime.now()

        if cmd.startswith("PLANET"):
            planets = ["mercury", "venus", "earth", "mars", "jupiter", "saturn", "uranus", "neptune"]
            for i, p in enumerate(planets):
                if p in cmd.lower():
                    self.planet_encoder.planet = i
                    self.planet_encoder.update_flag = True
        
        if cmd.startswith("SFX"):
            self.audio.audio_cmds.append(cmd)